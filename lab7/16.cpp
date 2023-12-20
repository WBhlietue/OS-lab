#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "stack-ptr.h"

struct StackNode *node = NULL;

void *Thread(void *args)
{
    Push(*(int *)(args), &node);
    sleep(1);
    int a = Pop(&node);
    printf("%d ", a);
    return NULL;
}

int main()
{
    int nums[10];
    pthread_t thread[10];
    for (int i = 0; i < 10; i++)
    {
        nums[i] = i;
        pthread_create(&thread[i], NULL, Thread, &nums[i]);
    }
    for (int i = 0; i < 10; i++)
    {
        pthread_join(thread[i], NULL);
    }

    return 0;
}