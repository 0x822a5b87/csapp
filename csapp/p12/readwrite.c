#include "stdio.h"
#include "../csapp.hpp"

// 读者优先

int   readcnt;
sem_t mutex, w;

void init()
{
    mutex = *sem_open("mutex", O_CREAT, S_IRUSR, 1);
    w     = *sem_open("w", O_CREAT, S_IRUSR, 1);
}

void reader(void)
{
    while(1)
    {
        // 互斥锁，我们在互斥锁中判断是否为第一个读者，如果是第一个读者，那么读者也上锁
        // 如果之后进来的也是读者，那么它将不会调用 P(&w)
        sem_wait(&mutex);
        readcnt++;
        if (readcnt == 1)
            sem_wait(&w);
        sem_post(&mutex);

        printf("read cnt = [%d]\n", readcnt);

        sem_wait(&mutex);
        readcnt--;
        if (readcnt == 0)
            sem_post(&w);
        sem_post(&mutex);
    }
}

void writer(void)
{
    sem_wait(&w);
    printf("write\n");
    sem_post(&w);
}

int main(int argc, char **argv)
{
    reader();
    writer();
}