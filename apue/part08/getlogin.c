#include <pwd.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    char *login_name = getlogin();
    if (login_name == NULL)
        err_sys("error getlogin");

    printf("login name = %s\n", login_name);

    uid_t         uid  = getuid();
    struct passwd *pwd  = getpwuid(uid);

    printf("name = %s\n", pwd->pw_name);
}