//
// Created by 杜航宇 on 2019-08-15.
//

#include "iostream"

void iptoa(char *s, long *p)
{
    long val = *p;
    sprintf(s, "%ld", val);
}

void test(long x)
{
    x = 8 * x + 22;
    x &= -16;
    std::cout << x << std::endl;
}

int main()
{
    char s[100];
    long l = 1000L, *p = &l;
    iptoa(s, p);
    
    std::cout << s << std::endl;

    test(0x5);
    test(0x6);
}
