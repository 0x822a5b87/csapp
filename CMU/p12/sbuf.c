#include "../csapp.h"
#include "sbuf.h"

void sbuf_init(sbuf_t *sp, int n)
{
    sp->buf   = (int *) Calloc(n, sizeof(int));
    sp->n     = n;
    sp->front = sp->rear = 0;

    sp->mutex = sem_open("sbuf_sem", O_CREAT, 0777, 1);
    if (sp->mutex == SEM_FAILED)
    {
        printf("error init mutex [%p], errno = [%d]\n", sp->mutex, errno);
    }
    sp->slots = sem_open("sbuf_slots", O_CREAT, S_IRUSR | S_IWUSR, n);
    if (sp->slots == SEM_FAILED)
    {
        printf("error init slots [%p]\n", sp->mutex);
    }
    sp->items = sem_open("sbuf_items", O_CREAT, S_IRUSR | S_IWUSR, 0);
    if (sp->items == SEM_FAILED)
    {
        printf("error init items [%p]\n", sp->mutex);
    }
}

void sbuf_insert(sbuf_t *sp, int item)
{
    sem_wait(sp->slots);
    sem_wait(sp->mutex);
    sp->buf[(++sp->rear) % (sp->n)] = item;
    sem_post(sp->mutex);
    sem_post(sp->items);
}

int sbuf_remove(sbuf_t *sp)
{
    int item;
    sem_wait(sp->items);
    sem_wait(sp->mutex);
    item = sp->buf[(++sp->front) % (sp->n)];
    sem_post(sp->mutex);
    sem_post(sp->slots);

    printf("item = [%d]\n", item);
    return item;
}

void sbuf_deinit(sbuf_t *sp)
{
    Free(sp->buf);
    sem_close(sp->mutex);
    sem_close(sp->slots);
    sem_close(sp->items);
    sem_unlink("/mysem");
    sem_unlink("/myslots");
    sem_unlink("/myitems");
}

