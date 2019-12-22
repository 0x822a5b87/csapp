#include <arpa/inet.h>
#include "stdio.h"
#include "../csapp.hpp"

int main(int argc, char **argv)
{
    struct in_addr addr;
    int            rc = inet_pton(AF_INET, argv[1], &addr);
    if (rc == 0)
    {
        app_error("inet_pton error: invalid dotted-dcimal address");
    }
    else if (rc < 0)
    {
        unix_error("inet_pton error");
    }
    printf("addr = [%x]\n", addr.s_addr);
}