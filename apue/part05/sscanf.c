#include "../apue.h"

int main(int argc, char **argv)
{
    const char *buf = "2020-01-01 17";

    unsigned y, m, d, h, s;

    int scann = 0;
    if ((scann = sscanf(buf, "%d-%d-%d %d:%d", &y, &m, &d, &h, &s)) != 5)
    {
        printf("scann = %d\n", scann);
        // scann = 4
    }
}