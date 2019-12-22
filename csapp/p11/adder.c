#include "../csapp.hpp"

int main(void)
{
    char *buf, *p;
    char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
    int n1 = 0, n2 = 0;

    if ((buf = getenv("QUERY_STRING")) != NULL)
    {
        p = strchr(buf, '&');
        *p = '\0';
        strcpy(arg1, p);
        strcpy(arg2, p + 1);
        n1 = atoi(arg1);
        n2 = atoi(arg2);
    }

    sprintf(content, "QUERY_STRING = %s\n", buf);
    sprintf(content, "n1 = [%d], n2 = [%d], ret = [%d]\n", n1, n2, n1 + n2);
}