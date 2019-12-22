#include <arpa/inet.h>
#include "stdio.h"
#include "../csapp.hpp"

int main(int argc, char **argv)
{
    struct in_addr in_addr;
    const char *iphex = argv[1];
    char ip[MAXBUF];
    uint32_t  addr;

    // decimal char to unsigned int
    sscanf(argv[1], "%x", &addr);

    // host byte order to network byte order
    in_addr.s_addr = htonl(addr);

    inet_ntop(AF_INET, &in_addr, ip, MAXBUF);

    printf("iphex = [%s]\n", iphex);
    printf("ip = [%s]\n", ip);
}