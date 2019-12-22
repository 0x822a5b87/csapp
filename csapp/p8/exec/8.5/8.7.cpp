//
// Created by 杜航宇 on 2019/11/29.
//

#include "../8.4/snooze.cpp"
#include "../../../csapp.hpp"

// 我们不需要在函数中做任何事情，普通的 SIGINT 信号会直接结束进程
// 修改默认行为之后，不会做任何事情，但是 sleep 函数会因为收到这个信号而激活
void interrupt_signal_handler(int sig)
{

}

int main(int argc, char *argv[])
{
    if (signal(SIGINT, interrupt_signal_handler) == SIG_ERR)
    {
        unix_error("signal error");
    }
    const char   *sec_text = argv[1];
    unsigned int sec       = atoi(sec_text);

    snooze(sec);
}
