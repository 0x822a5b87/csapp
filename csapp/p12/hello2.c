#include "stdio.h"
#include "../csapp.hpp"

void *thread(void *vargp);

int main()
{
    pthread_t tid;
    Pthread_create(&tid, NULL, thread, NULL);
}

void *thread(void *vargp)
{
    sleep(3);
    // 这个将不会打印，因为主线程退出了
    printf("Hello world\n");
    return NULL;
}
