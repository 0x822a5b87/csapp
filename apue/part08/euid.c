#include <grp.h>
#include <pwd.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    uid_t uid  = getuid();
    uid_t euid = geteuid();

    printf("uid = %d, euid = %d\n", uid, euid);

    struct passwd *up  = getpwuid(uid);
    struct passwd *eup = getpwuid(euid);
    printf("u name = %s, eu name = %s\n", up->pw_name, eup->pw_name);

    gid_t gid  = getgid();
    gid_t egid = getegid();

    printf("gid = %d, egid = %d\n", gid, egid);

    struct group *g  = getgrgid(gid);
    struct group *eg = getgrgid(egid);
    printf("g name = %s, eg name = %s\n", g->gr_name, eg->gr_name);
}