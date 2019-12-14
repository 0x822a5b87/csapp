#include <netdb.h>
#include "stdio.h"
#include "../csapp.hpp"

int main()
{
    struct addrinfo *addrs;
    int             ret = getaddrinfo("127.0.0.1", "8080", NULL, &addrs);
    if (ret < 0)
    {
        unix_error("error get addr info\n");
        exit(0);
    }

    for (struct addrinfo *start = addrs;
         start != NULL;
         start = start->ai_next)
    {
        char host[20] = {};
        char port[20] = {};
        ret = getnameinfo(start->ai_addr, sizeof(*start), host, 20, port, 20, NI_NUMERICSERV);
        if (ret == 0)
        {
            printf("host = [%s], port = [%s]\n", host, port);
            break;
        }
    }
}
