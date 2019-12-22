//
// Created by 杜航宇 on 2019/11/30.
//

// 测试信号的运行
#include <zconf.h>
#include "../../../csapp.hpp"

const unsigned int N = 10;

void sig_int_handler(int sig)
{
    for (unsigned int cnt = 0; cnt != N; ++cnt)
    {
        sleep(1);
        printf("sig int cnt = [%d]\n", cnt);
    }
}

void sig_sys_handler(int sig)
{
    for (unsigned int cnt = 0; cnt != N; ++cnt)
    {
        sleep(1);
        printf("sig sys cnt = [%d]\n", cnt);
    }
}

int main()
{
    if ((signal(SIGINT, sig_int_handler)) == SIG_ERR
        || signal(SIGSYS, sig_sys_handler) == SIG_ERR)
    {
        unix_error("signal error!");
    }
    Kill(getpid(), SIGSYS);
    for (unsigned int cnt = 0; cnt != N; ++cnt)
    {
        sleep(1);
        printf("pid = [%d], cnt = [%d]\n", getpid(), cnt);
    }
}
