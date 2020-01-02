#include "../apue.h"

int main(int argc, char **argv)
{
    FILE *fp = fopen(__FILE__, "r");
    if (fp == NULL)
        err_sys("error open %s", __FILE__);
    FILE *rfp = freopen(__FILE__, "r+", fp);
    if (rfp == NULL)
        err_sys("error reopen %s", __FILE__);
}