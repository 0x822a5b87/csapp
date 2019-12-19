#include "stdio.h"
#include "../csapp.hpp"

void *thread(void *var)
{
    int *num = (int *) var;
    printf("num = [%p], num = [%d]\n", num, *num);
    *num = 200;

    return var;
}

int main()
{
    pthread_t tid;
    int num = 100;
    pthread_create(&tid, NULL, thread, (void *) &num);

    int thread_return, *p_thread_return = &thread_return;
    printf("p_thread_return = [%p]\n", p_thread_return);
    pthread_join(tid, (void **)&p_thread_return);
    printf("p_thread_return = [%p]\n", p_thread_return);
    printf("thread return = [%d]\n", *((int *)p_thread_return));
    //p_thread_return = [0x7ffee16690d0]
    //num = [100]
    //p_thread_return = [0x7ffee16690d4]
    //thread return = [200]
}
