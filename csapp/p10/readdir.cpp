//
// Created by 杜航宇 on 2019/12/10.
//

#include <dirent.h>
#include "../csapp.hpp"

int main(int argc, char **argv)
{
    DIR *streamp;
    struct dirent *dep;

    streamp = opendir(argv[1]);
    if (streamp == NULL)
    {
        printf("error open file :[%s]\n", argv[1]);
        return -1;
    }

    errno = 0;
    while ((dep = readdir(streamp)) != NULL)
    {
        printf("Found file: [%s]\n", dep->d_name);
    }
    if (errno != 0)
    {
        unix_error("readdir error");
    }

    closedir(streamp);

    exit(0);
}
