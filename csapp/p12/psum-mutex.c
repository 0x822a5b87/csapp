#include "stdio.h"
#include "../csapp.hpp"

#define MAX_THREADS 32

void *sum_mutex(void *args);
void *sum_array(void *args);

long  gsum = 0;
long  nelems_per_thread;
long nelemns;
sem_t mutex;

int main(int argc, char **argv)
{
    long      i, log_nelemns, nthreads, myid[MAX_THREADS];
    pthread_t tid[MAX_THREADS];

    if (argc != 3)
    {
        printf("usage: %s <nthreads> <log_nelemns>\n", argv[0]);
        exit(0);
    }

    nthreads = atoi(argv[1]);
    if (nthreads > MAX_THREADS)
    {
        printf("max thread cnt = [%d]\n", MAX_THREADS);
    }
    log_nelemns       = atoi(argv[2]);
    nelemns           = (1u << log_nelemns);
    nelems_per_thread = nelemns / nthreads + 1;

    sem_init(&mutex, 0, 1);
    for (i = 0; i < nthreads; ++i)
    {
        myid[i] = i;
        Pthread_create(&tid[i], NULL, sum_array, &myid[i]);
    }
    for (i = 0; i < nthreads; ++i)
    {
        Pthread_join(tid[i], NULL);
    }
    long expected = (nelemns * (nelemns - 1)) / 2;
    if (gsum != expected)
    {
        printf("error : result = %ld, expected = %ld\n", gsum, expected);
    }
    return 0;
}

void *sum_mutex(void *args)
{
    long myid  = voidp2type(int, args);
    long start = nelems_per_thread * myid;
    long end   = start + nelems_per_thread;
    if (end > nelemns)
        end = nelemns;
    for (; start < end; ++start)
    {
        P(&mutex);
        gsum += start;
        V(&mutex);
    }
    return NULL;
}

void *sum_array(void *args)
{
    long myid  = voidp2type(int, args);
    long start = nelems_per_thread * myid;
    long end   = start + nelems_per_thread;
    if (end > nelemns)
        end = nelemns;
    long sum = 0;
    for (; start < end; ++start)
    {
        sum += start;
    }
    P(&mutex);
    gsum += sum;
    V(&mutex);
    return NULL;
}