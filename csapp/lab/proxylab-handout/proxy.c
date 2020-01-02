#include <stdio.h>
#include "csapp.h"

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

#define HTTP_RESPONSE_TEXT 1
#define HTTP_RESPONSE_BIN 2

typedef struct
{
    char header_name[1024];
    char header_value[1024];
} http_header;

typedef struct
{
    char     data[MAX_OBJECT_SIZE];
    char     *cur_p;
    unsigned type;
    ssize_t  content_len;
} http_body;

typedef struct
{
    char        method[MAXLINE];
    char        ip[MAXLINE];
    char        port[MAXLINE];
    char        url[MAXLINE];
    char        version[MAXLINE];
    http_header headers[20];
    size_t      cur_header;
    char        raw_data[MAXLINE];
    char        *cur_raw;
    size_t      n;
} http_request;

typedef struct
{
    char        version[10];
    char        status[10];
    char        desc[20];
    size_t      cur_header;
    http_header headers[20];

    http_body body;

    char   raw_data[MAX_OBJECT_SIZE];
    size_t n;
    char   *cur_raw;
} http_response;

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";

static const char *log_file_name = "test.txt";

static char log_buf[MAXLINE];

void log_file(const char *str);

void init();

void init_log_fil();

void init_http_request(http_request *request);

void init_http_response(http_response *response);

void init_http_body(http_body *body);

ssize_t parse_request(rio_t *rio, http_request *request);

void parse_request_line(http_request *request, const char *reqstr);

void parse_header(http_header *header, const char *headerstr);

void parse_body_type(http_response *rp, const char *content_type, const char *header_value);

void parse_url(const char *url, char *ip, char *port, char *page);

static void copy2rawdata(http_request *request, const char *reqstr);

static void copy2response(http_response *response, const char *str);

static void copyn2response(http_response *response, const char *str, size_t n);

ssize_t forward_request(http_request *request, http_response *response);

ssize_t parse_response(rio_t *riop, http_response *response);

void parse_response_line(http_response *rp, char *usrbuf);

ssize_t parse_response_body(rio_t *riop, http_response *response, char *usrbuf);

int main(int argc, char **argv)
{
    init();
    int listenfd = Open_listenfd(argv[1]);
    sprintf(log_buf, "listenfd = [%d]\n", listenfd);
    log_file(log_buf);
    while (1)
    {
        struct sockaddr_storage sockaddr;

        socklen_t len = sizeof(sockaddr);

        int   connfd = Accept(listenfd, (SA *) &sockaddr, &len);
        rio_t rio;
        Rio_readinitb(&rio, connfd);
        http_request request;
        init_http_request(&request);
        ssize_t n = parse_request(&rio, &request);
        if (n <= 0)
        {
            continue;
        }

        http_response response;
        init_http_response(&response);
        forward_request(&request, &response);
        Rio_writen(connfd, response.raw_data, response.n);
    }
}

void init()
{
    init_log_fil();
}

void init_http_request(http_request *request)
{
    request->cur_header = 0;
    request->n          = 0;
    request->cur_raw    = request->raw_data;
}

void init_http_response(http_response *response)
{
    response->cur_raw    = response->raw_data;
    response->n          = 0;
    response->cur_header = 0;
    init_http_body(&response->body);
}

void init_http_body(http_body *body)
{
    body->cur_p       = body->data;
    body->content_len = 0;
}

ssize_t forward_request(http_request *request, http_response *response)
{
    // TODO 可以在本地缓存一份
    int   realfd = Open_clientfd(request->ip, request->port);
    rio_t rio;
    Rio_readinitb(&rio, realfd);
    Rio_writen(realfd, request->raw_data, request->n);
    ssize_t response_sz = parse_response(&rio, response);
    Close(realfd);
    return response_sz;
}

ssize_t parse_response(rio_t *riop, http_response *response)
{
    ssize_t resp_sz = 0, line_cnt = 0;
    char    buf[MAX_OBJECT_SIZE];
    if ((line_cnt = Rio_readlineb(riop, buf, MAXLINE)) == 0)
    {
        return 0;
    }
    resp_sz += line_cnt;
    parse_response_line(response, buf);
    while ((line_cnt = Rio_readlineb(riop, buf, MAXLINE)))
    {
        copy2response(response, buf);
        if (!strcasecmp(buf, "\r\n"))
        {
            break;
        }
        resp_sz += line_cnt;
        parse_header(&response->headers[response->cur_header++], buf);
    }

    ssize_t body_size = parse_response_body(riop, response, buf);
    resp_sz += body_size;

    return resp_sz;
}

void init_body_by_header(http_response *rp)
{
    for (size_t i = 0; i < rp->cur_header; ++i)
    {
        http_header *cur_header = &rp->headers[i];
        parse_body_type(rp, cur_header->header_name, cur_header->header_value);
    }
}

ssize_t parse_response_body(rio_t *riop, http_response *response, char *usrbuf)
{
    init_body_by_header(response);
    if (response->body.type == HTTP_RESPONSE_BIN)
    {
        Rio_readnb(riop, usrbuf, response->body.content_len);
        memcpy(response->body.cur_p, usrbuf, response->body.content_len);
        response->body.cur_p += response->body.content_len;
        copyn2response(response, usrbuf, response->body.content_len);
        return response->body.content_len;
    }
    else
    {
        ssize_t body_size = 0, line_size = 0;
        while ((line_size = Rio_readlineb(riop, usrbuf, MAXLINE)) > 0)
        {
            body_size += line_size;
            strcpy(response->body.cur_p, usrbuf);
            response->body.cur_p += line_size;
            copy2response(response, usrbuf);
        }
        return body_size;
    }
}

void parse_response_line(http_response *rp, char *usrbuf)
{
    sscanf(usrbuf, "%s %s %s", rp->version, rp->status, rp->desc);
    copy2response(rp, usrbuf);
}

void parse_url(const char *url, char *ip, char *port, char *page)
{
    sscanf(url, "http://%99[^:]:%99[^/]%99[^\n]", ip, port, page);
}

ssize_t parse_request(rio_t *rio, http_request *request)
{
    ssize_t n, cnt;
    char    usrbuf[MAXLINE];
    if ((n = Rio_readlineb(rio, usrbuf, MAXLINE)) == 0)
    {
        return 0;
    }
    parse_request_line(request, usrbuf);
    while ((cnt = Rio_readlineb(rio, usrbuf, MAXLINE)))
    {
        copy2rawdata(request, usrbuf);
        if (!strcasecmp(usrbuf, "\r\n"))
        {
            break;
        }
        n += cnt;
        parse_header(&request->headers[request->cur_header++], usrbuf);
    }

    return n;
}

void parse_request_line(http_request *request, const char *reqstr)
{
    sscanf(reqstr, "%s %s %s", request->method, request->url, request->version);
    char page[MAXLINE];
    parse_url(request->url, request->ip, request->port, page);
    strcpy(request->url, page);
    copy2rawdata(request, request->method);
    copy2rawdata(request, " ");
    copy2rawdata(request, page);
    copy2rawdata(request, " ");
    copy2rawdata(request, request->version);
    copy2rawdata(request, "\r\n");
}

static void copy2rawdata(http_request *request, const char *reqstr)
{
    ssize_t req_size = strlen(reqstr);
    strcpy(request->cur_raw, reqstr);
    request->cur_raw += req_size;
    request->n += req_size;
}

static void copy2response(http_response *response, const char *str)
{
    ssize_t sz = strlen(str);
    strcpy(response->cur_raw, str);
    response->cur_raw += sz;
    response->n += sz;
}

static void copyn2response(http_response *response, const char *str, size_t n)
{
    memcpy(response->cur_raw, str, n);
    response->cur_raw += n;
    response->n += n;
}

void parse_header(http_header *header, const char *headerstr)
{
    char *ptr = index(headerstr, ':');
    if (ptr)
    {
        strncpy(header->header_name, headerstr, (ptr - headerstr));
        strcpy(header->header_value, ptr + 2);
    }
}

void parse_body_type(http_response *rp, const char *header_name, const char *header_value)
{

    if (!strcasecmp(header_name, "Content-type"))
    {
        if (strstr(header_value, "image/jpeg")
            || strstr(header_value, "text/plain"))
        {
            rp->body.type = HTTP_RESPONSE_BIN;
        }
        else
        {
            rp->body.type = HTTP_RESPONSE_TEXT;
        }
    }
    else if (!strcasecmp(header_name, "Content-length"))
    {
        rp->body.content_len = atoi(header_value);
    }
}

void init_log_fil()
{
//    FILE *fp = fopen(log_file_name, "w");
//    fprintf(fp, "%s", "");
//    fclose.c(fp);
}

void log_file(const char *str)
{
    printf("%s\n", str);
    FILE *fp = fopen(log_file_name, "a");
    fprintf(fp, "%s", str);
    fclose(fp);
}
