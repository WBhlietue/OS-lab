#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

int GetNum(int a)
{
    if (a % 2 == 0)
    {
        return a / 2;
    }
    return (3 * a) + 1;
}

int main()
{
    const int SIZE = 4096;
    int a;
    scanf("%d", &a);
    if (a < 1)
    {
        printf("Enter a number greater than 1\n");
        return 0;
    }
    int shmFile = shm_open("file22Share", O_CREAT | O_RDWR, 0666);
    ftruncate(shmFile, SIZE);
    char *shmPointer = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmFile, 0);
    char numToString[10];
    pid_t id = fork();
    if (id == 0)
    {
        int num = a;
        do
        {
            num = GetNum(num);
            sprintf(numToString, ", %d", num);
            sprintf(shmPointer, "%s", numToString);
            shmPointer += strlen(numToString);
        } while (num > 1);
    }
    else if (id > 0)
    {
        int status;
        wait(&status);
        char *data = (char *)shmPointer;
        printf("%d%s\n", a, data);
        return 0;
    }
    return 0;
}