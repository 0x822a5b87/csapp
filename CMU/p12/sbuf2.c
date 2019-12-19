/* $begin sbufc */
#include "../csapp.h"
#include "sbuf.h"

/* Create an empty, bounded, shared FIFO buffer with n slots */
/* $begin sbuf_init */
void sbuf_init(sbuf_t *sp, int n)
{
    sp->buf   = (int *) Calloc(n, sizeof(int));
    sp->n     = n;
    sp->front = sp->rear = 0;

    sp->mutex = sem_open("sbuf_sem", O_EXCL, S_IRUSR | S_IWUSR, 1);
    if (sp->mutex == SEM_FAILED)
    {
        printf("error init mutex [%p]\n", sp->mutex);
    }
    sp->slots = sem_open("sbuf_slots", O_EXCL, S_IRUSR | S_IWUSR, n);
    if (sp->slots == SEM_FAILED)
    {
        printf("error init slots [%p]\n", sp->mutex);
    }
    sp->items = sem_open("sbuf_items", O_EXCL, S_IRUSR | S_IWUSR, 0);
    if (sp->items == SEM_FAILED)
    {
        printf("error init items [%p]\n", sp->mutex);
    }
}
/* $end sbuf_init */

/* Clean up buffer sp */
/* $begin sbuf_deinit */
void sbuf_deinit(sbuf_t *sp)
{
    Free(sp->buf);
}
/* $end sbuf_deinit */

/* Insert item onto the rear of shared buffer sp */
/* $begin sbuf_insert */
void sbuf_insert(sbuf_t *sp, int item)
{
    printf("insert item = [%d]\n", item);
    printf("1\n");
    sem_wait(sp->slots);                          /* Wait for available slot */
    printf("1\n");
    sem_wait(sp->mutex);                          /* Lock the buffer */
    printf("1\n");
    sp->buf[(++sp->rear)%(sp->n)] = item;   /* Insert the item */
    printf("1\n");
    sem_post(sp->mutex);                          /* Unlock the buffer */
    printf("1\n");
    sem_post(sp->items);                          /* Announce available item */
    printf("1\n");
}
/* $end sbuf_insert */

/* Remove and return the first item from buffer sp */
/* $begin sbuf_remove */
int sbuf_remove(sbuf_t *sp)
{
    int item;
    sem_wait(sp->items);                          /* Wait for available item */
    sem_wait(sp->mutex);                          /* Lock the buffer */
    item = sp->buf[(++sp->front)%(sp->n)];  /* Remove the item */
    sem_post(sp->mutex);                          /* Unlock the buffer */
    sem_post(sp->slots);                          /* Announce available slot */
    return item;
}
/* $end sbuf_remove */
/* $end sbufc */
