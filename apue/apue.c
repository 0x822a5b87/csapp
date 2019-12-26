/*
 * =====================================================================================
 *
 *       Filename:  apue.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2009/06/23 16时31分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  jack.zh(toserver@gmail.com)
 *        Company:
 *
 * =====================================================================================
 */

#include "apue.h"
#include <errno.h>
#include <stdarg.h>
#include <fcntl.h>

static void err_doit(int, int, const char *, va_list);

void err_quit(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
    exit(1);
}

void err_sys(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    exit(1);
}

void err_msg(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
}

void err_ret(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
}

static
void
err_doit(
        int errnoflag,
        int error,
        const char *fmt,
        va_list ap
        )
{
    char buf[MAXLINE];
    vsnprintf(buf, MAXLINE, fmt, ap);

    if (errnoflag)
    {
        snprintf(buf+strlen(buf), MAXLINE-strlen(buf), ": %s", strerror(error));
    }

    strcat(buf, "\n");
    fflush(stdout);
    fputs(buf, stderr);
    fflush(NULL);
}

void
err_dump(const char *fmt, ...)
{
    va_list ap;
    va_start(ap,fmt);
    err_doit(1,errno,fmt,ap);
    va_end(ap);
    abort();
    exit(1);
}

void set_fl(int fd, int flags)
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
        err_sys("fcntl F_GETFL error");

    val |= flags;

    if (fcntl(fd, F_SETFL, val) < 0)
        err_sys("fcntl F_SETFL error");
}

void clr_fl(int fd, int flags)
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
        err_sys("fcntl F_GETFL error");

    val &= ~flags;

    if (fcntl(fd, F_SETFL, val) < 0)
        err_sys("fcntl F_SETFL error");
}
