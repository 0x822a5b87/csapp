#include "stdio.h"
#include "../csapp.hpp"

#define N 2

void *thread(void *arg);

char **ptr;

int main(int argc, char **argv)
{
    long i;
    pthread_t tid;
    char *msgs[N] = {
            "Hello from foo",
            "Hello from bar"
    };

    ptr = msgs;
    for (i = 0; i < N; i++)
    {
        Pthread_create(&tid, NULL, thread, (void *)i);
        Pthread_exit(NULL);
    }
}

void *thread(void *arg)
{
    long myid = (long) arg;
    static int cnt = 0;
    printf("[%ld]: %s (cnt = %d)\n", myid, ptr[myid], ++cnt);
    return NULL;
}