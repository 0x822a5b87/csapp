#include "../apue.h"
#include "sys/utsname.h"

int main(int argc, char **argv)
{
    struct utsname name;
    if (uname(&name) < 0)
        err_sys("uname error");
    printf("%s\n%s\n%s\n%s\n%s\n",
           name.machine, name.nodename,
           name.release, name.sysname,
           name.version);

    // x86_64
    //HANGYUDU-MB0
    //18.7.0
    //Darwin
    //Darwin Kernel Version 18.7.0: Tue Aug 20 16:57:14 PDT 2019; root:xnu-4903.271.2~2/RELEASE_X86_64
}