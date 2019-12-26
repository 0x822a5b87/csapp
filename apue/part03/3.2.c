#include "../apue.h"

struct Node
{
    int         fd;
    struct Node *next;
};

void free_fd(struct Node *head)
{
    if (head == NULL)
        return;

    struct Node *cur;
    while (head->next != NULL)
    {
        close(head->next->fd);
        printf("close fd %d\n", head->next->fd);
        cur = head->next;
        free(head);
        head = cur;
    }
}

int my_dup2(int fd, int fd2)
{
    if (fd == fd2)
        return fd2;

    close(fd2);

    struct Node *head = (struct Node *) malloc(sizeof(struct Node));
    struct Node *cur  = head;
    int         tmp_fd;
    while ((tmp_fd = dup(fd)) < fd2)
    {
        if (tmp_fd == -1)
        {
            printf("error dup fd\n");
            free_fd(head);
            return fd;
        }

        printf("create fd = [%d]\n", tmp_fd);
        struct Node *tmp_node = (struct Node *) malloc(sizeof(struct Node));
        tmp_node->fd   = tmp_fd;
        tmp_node->next = NULL;
        cur->next = tmp_node;
        cur = cur->next;
    }

    free_fd(head);
    return fd2;
}

int main()
{
    int fd = my_dup2(STDOUT_FILENO, 15);
    printf("after dup : fd = [%d]\n", fd);
    write(15, "Hello World!\n", 13);
    return 0;
}