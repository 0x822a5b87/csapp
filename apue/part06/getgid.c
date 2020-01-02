#include <grp.h>
#include "../apue.h"

int main(int argc, char **argv)
{
    int gcnt = getgroups(0, NULL);
    printf("gcnt = %d\n", gcnt);
    gid_t gids[gcnt];
    gcnt = getgroups(gcnt, gids);
    printf("gcnt = %d\n", gcnt);

    for (int i = 0; i < gcnt; ++i)
    {
        struct group *gp = getgrgid(gids[i]);
        printf("%s\n", gp->gr_name);
    }
}