//
// Created by 杜航宇 on 2019/11/30.
//

// 测试信号的运行
#include "../../../csapp.hpp"

unsigned int global_var = 0;

volatile sig_atomic_t flag;

void sig_int_handler(int sig)
{
    ++global_var;
}

int main()
{
    flag = 1;
    Signal(SIGINT, sig_int_handler);
    for (int i = 0; i != 100; ++i)
    {
        printf("global_var = [%d]\n", global_var);
        sleep(1);
    }
}
