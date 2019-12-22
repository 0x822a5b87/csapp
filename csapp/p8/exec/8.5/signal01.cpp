//
// Created by 杜航宇 on 2019/12/1.
//

#include "iostream"
#include "../../../csapp.hpp"

int main()
{
    pid_t pid;

    sigset_t parent_mask;
    Sigaddset(&parent_mask, SIGCHLD);
    Sigprocmask(SIG_SETMASK, &parent_mask, NULL);

    sigset_t pprev_mask;
    Sigprocmask(SIG_SETMASK, &parent_mask, &pprev_mask);

    if ((pid = Fork()) == 0)
    {
        sigset_t no_mask, prev_mask;
        Sigemptyset(&no_mask);
        Sigemptyset(&prev_mask);
        printf("no mask = [%d]\n", no_mask);
        Sigprocmask(SIG_SETMASK, &no_mask, &prev_mask);
        Sigprocmask(SIG_SETMASK, &no_mask, &prev_mask);
        printf("sub process set mask = [%d]\n", prev_mask);
        sleep(2);
    }
    else
    {
        sleep(1);
        sigset_t cur_mask;
        Sigprocmask(SIG_SETMASK, NULL, &cur_mask);
        printf("parent current mask = [%d]\n", cur_mask);
    }
    int status;
    // 这里会抛出 no child processes 的异常，因为子进程自己退出了
    pid_t wpid = Waitpid(pid, &status, WUNTRACED);
    printf("wpid = [%d]\n", wpid);
}