#include "stdio.h"
#include "../csapp.hpp"

#define voidp2type(type, voidp) (*((type*) voidp))

volatile long cnt = 0;
sem_t *mutex;


void *thread(void *);


int main(int argc, char **argv)
{
    // 最早由于使用了 int 类型，导致数据传递到 thread 后异常
    // int niters;
    long niters;
    mutex = sem_open("/mysem", O_CREAT, S_IRUSR | S_IWUSR, 1);
    printf("mutex = [%p]\n", mutex);
    pthread_t tid1, tid2;
    if (argc != 2)
    {
        printf("usage: %s <niters>\n", argv[0]);
        exit(1);
    }
    niters = atoi(argv[1]);
    pthread_create(&tid1, NULL, thread, &niters);
    pthread_create(&tid2, NULL, thread, &niters);
    Pthread_join(tid1, NULL);
    Pthread_join(tid2, NULL);

    printf("cnt = [%ld], cnt = 2 * %ld ? [%d]", cnt, niters, (cnt == 2 * niters));

    sem_close(mutex);
    sem_unlink("/mysem");
}

void *thread(void *args)
{
    long      n = voidp2type(long, args);
    for (long i = 0; i < n; ++i)
    {
        sem_wait(mutex);
        ++cnt;
        sem_post(mutex);
    }
    return NULL;
}
