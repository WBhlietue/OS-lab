#include <stdio.h>
#include <pthread.h>

#define MAX_RESOURCE 5000000

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int resources = MAX_RESOURCE;

int DecreaseCount(int count)
{
    if (resources < count)
    {
        return -1;
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

int main()
{
    pthread_t p1;
    pthread_t p2;
    pthread_create(&p1, NULL, Thread, NULL);
    pthread_create(&p2, NULL, Thread, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("%d\n", resources);
}