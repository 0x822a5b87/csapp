#include <pthread.h>
#include "../apue.h"

void thread(void *);


int main(int argc, char **argv)
{
    pthread_t id;
    int       num = 10;
    int       ret = pthread_create(&id, NULL, (void *) thread, (void *) &num);
    if (ret != 0)
    {
        printf("Create pthread error = [%d]!\n", ret);
        exit(ret);
    }

    return 0;
}

void thread(void *args)
{
    sleep(1);
    int pid = *((int *) args);
    printf("hello world from thread %d\n", pid);
}