#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    struct timeval current;
    pid_t id = fork();
    char *commands[argc];
    for (int i = 1; i < argc; i++)
    {
        commands[i - 1] = argv[i];
    }
    commands[argc - 1] = NULL;
    if (id == 0)
    {
        execvp(commands[0], commands);
    }
    else if (id > 0)
    {
        struct timeval startTime;
        struct timeval endTime;
        gettimeofday(&startTime, NULL);
        int status;
        wait(&status);
        gettimeofday(&endTime, NULL);
        long long unsigned int difference = (endTime.tv_sec - startTime.tv_sec) * 1000 + (endTime.tv_usec - startTime.tv_usec)/1000;
        printf("Elapsed time: %.3f sec\n", (float)(difference)/1000.0);
    }
    return 0;
}