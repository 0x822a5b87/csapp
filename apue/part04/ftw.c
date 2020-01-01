#include "../apue.h"
#include <dirent.h>
#include <limits.h>

typedef int Myfunc(const char *, const struct stat *, int);

static Myfunc myfunc;

static int myftw(char *, Myfunc *);

static int dopath(Myfunc *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char **argv)
{
    int ret;
    if (argc != 2)
        err_quit("usage: ftw <starting-pathname>");

    ret = myftw(argv[1], myfunc);
    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
    if (ntot == 0)
        ntot = 1;
    printf("ntot = %d\n", ntot);
    printf("regular file = %7ld, %5.2f %%\n", nreg, nreg * 100.0 / ntot);
    printf("dir file = %7ld, %5.2f %%\n", nreg, ndir * 100.0 / ntot);
    printf("block file = %7ld, %5.2f %%\n", nblk, nreg * 100.0 / ntot);
    printf("char file = %7ld, %5.2f %%\n", nchr, nreg * 100.0 / ntot);
    printf("FIFO file = %7ld, %5.2f %%\n", nfifo, nreg * 100.0 / ntot);
}

#define FTW_F 1
#define FTW_D 2
#define FTW_DNR 3
#define FTW_NS 4

static char *fullpath;
static int  pathlen;

static int myftw(char *pathname, Myfunc *func)
{
    fullpath = (char *)path_alloc(&pathlen);
    if (pathlen <= strlen(pathname))
    {
        pathlen       = strlen(pathname) * 2;
        if ((fullpath = (char*)realloc(fullpath, pathlen)) == NULL)
            err_sys("realloc failed");
    }
    strcpy(fullpath, pathname);
    return (dopath(func));
}

static int dopath(Myfunc *func)
{
    struct stat   statbuf;
    struct dirent *dirp;
    DIR           *dp;
    size_t        ret, n;
    if (lstat(fullpath, &statbuf) < 0)
        return (func(fullpath, &statbuf, FTW_NS));
    if (S_ISDIR(statbuf.st_mode) == 0)
        return (func(fullpath, &statbuf, FTW_F));
    if ((ret = func(fullpath, &statbuf, FTW_D)) != 0)
        return (ret);

    n = strlen(fullpath);
    if (n + NAME_MAX + 2 > pathlen)
    {
        pathlen *= 2;
        if ((fullpath = ((char*)realloc(fullpath, pathlen))) == NULL)
            err_sys("realloc failed");
    }
    fullpath[n++] = '/';
    fullpath[n]   = 0;
    if ((dp = opendir(fullpath)) == NULL)
        return (func(fullpath, &statbuf, FTW_DNR));

    while ((dirp = readdir(dp)) != NULL)
    {
        if (strcmp(dirp->d_name, ".") == 0
            || strcmp(dirp->d_name, "..") == 0)
            continue;

        strcpy(&fullpath[n], dirp->d_name);
        if ((ret = dopath(func)) != 0)
            break;
    }
    fullpath[n - 1] = 0;
    if (closedir(dp) < 0)
        err_ret("can't close dir %s", fullpath);
    return (ret);
}

static int myfunc(const char *pathname, const struct stat *statptr, int type)
{
    switch (type)
    {
        // 判断文件类型，有两种方法：
        // 1. 通过 S_ISDIR 之类的宏
        // 2. 像下面这样通过 switch case 来实现
        // #define S_ISBLK(m)      (((m) & S_IFMT) == S_IFBLK)     /* block special */
        case FTW_F:
            switch (statptr->st_mode & S_IFMT)
            {
                case S_IFREG:
                    nreg++;
                    break;
                case S_IFBLK:
                    nblk++;
                    break;
                case S_IFCHR:
                    nchr++;
                    break;
                case S_IFIFO:
                    nfifo++;
                    break;
                case S_IFLNK:
                    nslink++;
                    break;
                case S_IFSOCK:
                    nsock++;
                    break;
                case S_IFDIR:
                    // dir should have type = FTW_D
                    err_dump("for S_IFDIR for %s", pathname);
            }
        case FTW_D:
            ndir++;
            break;
        case FTW_DNR:
            err_ret("can't read directory %s", pathname);
        case FTW_NS:
            err_ret("stat error for %s", pathname);
        default:
            err_dump("unknown type %d for pathname %s", type, pathname);
    }

    return (0);
}
