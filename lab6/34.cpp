#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_RESOURCE 50

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int resources = MAX_RESOURCE;
bool test = true;

int DecreaseCount(int count)
{
    while (resources < count)
    {
        printf("Waiting...\n");
        // return -1;
    }
    pthread_mutex_lock(&mutex);
    resources -= count;
    pthread_mutex_unlock(&mutex);
    return 0;
}

int IncreaseCount(int count)
{
    if (resources + count > MAX_RESOURCE)
    {
        return -1;
    }
    pthread_mutex_lock(&mutex);
    resources += count;
    pthread_mutex_unlock(&mutex);
    return 0;
}
void *Thread(void *args)
{
    for (int i = 0; i < 1000000; i++)
    {
        DecreaseCount(1);
    }
    return NULL;
}
void *Thread2(void *args)
{
    DecreaseCount(45);
    printf("Over\n");
    test = false;
    return NULL;
}

void *Thread3(void *args)
{
    sleep(1);
    IncreaseCount(20);
    return NULL;
}

int main()
{
    pthread_t p1;
    pthread_t p2;
    pthread_t p3;
    DecreaseCount(20);
    pthread_create(&p1, NULL, Thread2, NULL);
    pthread_create(&p3, NULL, Thread3, NULL);
    pthread_join(p1, NULL);
    pthread_join(p3, NULL);
}