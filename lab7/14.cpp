#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <pthread.h>

#define MIN_PID 100
#define MAX_PID 201

bool *pidManager;
int size = MAX_PID - MIN_PID + 1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int AllocatedMap()
{
    pidManager = (bool *)malloc(size * sizeof(bool));
    if (pidManager != NULL)
    {
        for (int i = 0; i < size; i++)
        {
            pidManager[i] = false;
        }
        return 1;
    }
    return -1;
}

int AllocatedPid()
{
    if (pidManager == NULL)
    {
        return -1;
    }
    for (int i = 0; i < size; i++)
    {
        pthread_mutex_lock(&mutex);
        if (!pidManager[i])
        {
            pidManager[i] = true;
            pthread_mutex_unlock(&mutex);
            return i + MIN_PID;
        }
        pthread_mutex_unlock(&mutex);
    }
    return -1;
}

void ReleasePid(int pid)
{
    pthread_mutex_lock(&mutex);
    if (pid < MIN_PID || pid > MAX_PID)
    {
        return;
    }
    pidManager[pid - MIN_PID] = false;
    pthread_mutex_unlock(&mutex);
}

void Print()
{
    for (int i = 0; i < size; i++)
    {
        printf("%d: -> %d\n", i + MIN_PID, pidManager[i]);
    }
}

void *Thread(void *args)
{
    int nums[5];
    for (int i = 0; i < 5; i++)
    {
        nums[i] = AllocatedPid();
    }
    sleep(2);
    for (int i = 0; i < 5; i++)
    {
        ReleasePid(nums[i]);
    }
    return NULL;
}

int main()
{
    AllocatedMap();
    pthread_t p1;
    pthread_t p2;
    pthread_t p3;
    pthread_t p4;
    pthread_t p5;
    pthread_create(&p1, NULL, Thread, NULL);
    pthread_create(&p2, NULL, Thread, NULL);
    pthread_create(&p3, NULL, Thread, NULL);
    pthread_create(&p4, NULL, Thread, NULL);
    pthread_create(&p5, NULL, Thread, NULL);
    sleep(1);
    Print();
    sleep(1);
    Print();
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    pthread_join(p5, NULL);
    return 0;
}