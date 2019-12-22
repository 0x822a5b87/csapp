#include <netinet/in.h>
#include "stdio.h"

int main()
{
    struct sockaddr_in sa;
    
    printf("sizeof(sockaddr_in) = %lu\n", sizeof(struct sockaddr_in));

    unsigned char sin_zero[8];
    size_t st = sizeof(uint16_t) + sizeof(uint16_t) + sizeof(struct in_addr) + sizeof(sin_zero);
    printf("st = %lu\n", st);
    st = sizeof(uint16_t) + sizeof(uint16_t) + sizeof(struct in_addr);
    printf("st = %lu\n", st);

    printf("sockaddr = %lu\n", sizeof(struct sockaddr));
}