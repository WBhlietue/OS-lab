#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct StackNode
{
    struct StackNode *pre;
    int value;
};

void Push(int value, struct StackNode **node)
{
    struct StackNode *n = (StackNode *)malloc(sizeof(struct StackNode));
    if (n == NULL)
    {
        return;
    }
    pthread_mutex_lock(&mutex);
    n->value = value;
    n->pre = *node;
    *node = n;
    pthread_mutex_unlock(&mutex);
}

int Pop(struct StackNode **node)
{
    if (*node == NULL)
    {
        return -1;
    }
    pthread_mutex_lock(&mutex);
    int value = (*node)->value;
    struct StackNode *temp = *node;
    *node = (*node)->pre;
    free(temp);
    pthread_mutex_unlock(&mutex);
    return value;
}