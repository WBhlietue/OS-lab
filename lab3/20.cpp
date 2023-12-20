#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MIN_PID 100
#define MAX_PID 150

bool *pidManager;
int size = MAX_PID - MIN_PID + 1;

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

void Print(){
    for(int i = 0; i < size; i++){
        printf("%d: -> %d\n", i + MIN_PID, pidManager[i]);
    }
}

int main()
{
    int a = AllocatedMap();
    int b[10];
    printf("Init:\n");
    Print();
    for(int i = 0; i < 10; i++){
        b[i] = AllocatedPid();
    }
    printf("\nUse:\n");
    Print();
    for(int i = 0; i < 10; i++){
        ReleasePid(b[i]);
    }
    printf("\nRelease:\n");
    Print();
    
    return 0;
}