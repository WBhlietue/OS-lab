#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h>

int main()
{
    pid_t s = fork();

    if (s == 0)
    {
        printf("%d\n", s);
        _exit(0);
    }
    else
    { 
        printf("%d\n", s);
        sleep(30);
        // return 0;
    }
    return 0;
}