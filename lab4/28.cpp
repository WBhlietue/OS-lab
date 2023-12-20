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

int AllocatedMap()
{
    // pidManager = (bool *)malloc(size * sizeof(bool));
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
        if (!pidManager[i])
        {
            pidManager[i] = true;
            return i + MIN_PID;
        }
    }
    return -1;
}

void ReleasePid(int pid)
{
    if (pid < MIN_PID || pid > MAX_PID)
    {
        return;
    }
    pidManager[pid - MIN_PID] = false;
}

void Print()
{
    for (int i = 0; i < size; i++)
    {
        printf("%d: -> %d\n", i + MIN_PID, pidManager[i]);
    }
}

void Recurse(int num)
{
    if (num == 0)
    {
        return;
    }
    int b = rand() % 100000;
    pid_t pid = fork();
    if (pid == 0)
    {
        int c = AllocatedPid();
        usleep(b);
        ReleasePid(c);
        exit(0);
    }
    else if (pid > 0)
    {
        Recurse(num - 1);
    }
}

void *Thread(void *args)
{
    int b = rand() % 100000;
    int c = AllocatedPid();
    usleep(b);
    ReleasePid(c);
    return NULL;
}

void SpawnThread(int num)
{
    pthread_t p;
    for (int i = 0; i < num; i++)
    {
        pthread_create(&p, NULL, Thread, NULL);
    }
}

int main()
{
    srand(time(0));
    int shmFile = shm_open("fileShare", O_CREAT | O_RDWR, 0666);
    ftruncate(shmFile, 300);
    pidManager = (bool *)mmap(0, 300, PROT_READ | PROT_WRITE, MAP_SHARED, shmFile, 0);
    int a = AllocatedMap();
    // Recurse(100);
    SpawnThread(100);
    Print();
    usleep(500);
    printf("..................................\n");
    Print();
    usleep(1000);
    printf("..................................\n");
    Print();

    return 0;
}