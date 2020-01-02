#include <pwd.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    struct passwd *pwent;
    while ((pwent = getpwent()) != NULL)
        printf("%s, %s\n", pwent->pw_name, pwent->pw_shell);

    struct passwd *pwd = getpwnam(argv[1]);
    printf("%s\n", pwd->pw_shell);
    struct passwd *uid = getpwuid(pwd->pw_uid);
    printf("%s\n", uid->pw_shell);
}