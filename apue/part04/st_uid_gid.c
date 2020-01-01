#include <fcntl.h>
#include "../apue.h"

void test(const char *path)
{
    struct stat s;
    lstat(path, &s);
    printf("%s isuid = %d, isgid = %d\n", path, S_ISUID & s.st_mode, S_ISGID & s.st_mode);
}

int main(int argc, char **argv)
{
    test(__FILE__);
    test("/etc/passwd");
}