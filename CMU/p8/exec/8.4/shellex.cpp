//
// Created by 杜航宇 on 2019-11-28.
//
// 这个简单的 shell 是有缺陷的，因为他并不回收它的后台进程

#include "iostream"

#include "../../../csapp.hpp"

#define MAX_ARGS 128

void eval(char *cmdline);

int parseline(char *buf, char **argv);

int builtin_command(char **argv);

void eval(char *cmdline)
{
    char  *argv[MAX_ARGS];
    char  buf[MAXLINE];
    int   bg;                       /* should the job run in bg or fg? */
    pid_t pid;

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    if (argv[0] == NULL)
    {
        return;
    }
    if (!builtin_command(argv))
    {
        // Child runs user job
        if ((pid = Fork()) == 0)
        {
            if (execve(argv[0], argv, environ) < 0)
            {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }

        // 如果没有设置后台执行那么需要等待命令执行完毕
        if (!bg)
        {
            int status;
            if (waitpid(pid, &status, 0) < 0)
            {
                unix_error("waitfg: waitpid error");
            }
        }
        else
        {
            printf("%d %s", pid, cmdline);
        }
    }
}

int builtin_command(char **argv)
{
    if (!strcmp(argv[0], "quit"))
    {
        exit(0);
    }
    if (!strcmp(argv[0], "&"))
    {
        return 1;
    }

    return 0;
}

int parseline(char *buf, char **argv)
{
    char *delim;
    int argc;
    int bg;

    // 替换最后的 \n 为 空格
    buf[strlen(buf) - 1] = ' ';
    while (*buf && (*buf == ' '))
    {
        buf++;
    }
    argc = 0;
    while((delim = strchr(buf, ' ')))
    {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while(*buf && (*buf == ' '))
        {
            buf++;
        }
    }
    argv[argc] = NULL;

    if (argc == 0)
    {
        return 1;
    }

    if ((bg = (*argv[argc- 1] == '&')) != 0)
    {
        argv[--argc] = NULL;
    }

    return bg;
}

int main()
{
    char cmdline[MAXLINE];

    while (true)
    {
        printf("> ");
        Fgets(cmdline, MAXLINE, stdin);
        if (feof(stdin))
        {
            exit(0);
        }
        eval(cmdline);
    }
}
