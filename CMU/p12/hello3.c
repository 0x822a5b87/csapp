#include "stdio.h"
#include "../csapp.hpp"

void *thread(void *vargp);
void *thread2(void *vargp);

int main()
{
    pthread_t tid;
    Pthread_create(&tid, NULL, thread, NULL);
    sleep(5);
}

void *thread(void *vargp)
{
    // 这个将不会打印，因为主线程退出了
    printf("thread run\n");

    pthread_t tid;
    Pthread_create(&tid, NULL, thread2, NULL);

    printf("thread end\n");
    return NULL;
}


void *thread2(void *vargp)
{
    sleep(3);
    printf("thread2 run!\n");
    return NULL;
}
