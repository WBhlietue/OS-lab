#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 80

void setup(char inputBuffer[], char *args[], int *background)
{
    printf("COMMAND->");
    if (fgets(inputBuffer, 100000, stdin) == NULL)
    {
        printf("\n");
        exit(0);
    }

    inputBuffer[strlen(inputBuffer) - 1] = '\0';
    // char tmpStr[strlen(inputBuffer) - 1];
    // for(int i = 0; i < strlen(inputBuffer) - 1; i++){
    //     tmpStr[i] = inputBuffer[i];
    // }
    // strcpy(inputBuffer, tmpStr);
    char *token = strtok(inputBuffer, " ");
    int a = 0;
    *background = 0;
    while (token != NULL)
    {
        if (token[0] == '&')
        {
            *background = 1;
        }
        else
        {
            args[a] = token;
            a++;
        }
        token = strtok(NULL, " ");
    }
    if (a > 40)
    {
        printf("\n Too many arguments\n");
        exit(0);
    }
    // else
    // {
    //     *background = (args[a - 1][0] == '&');
    // }
}

int main()
{
    char inputBuffer[MAX_LINE];
    int background;
    char *args[MAX_LINE + 1];
    while (1)
    {
        background = 0;

        setup(inputBuffer, args, &background);
        pid_t pid = fork();
        if (pid == 0)
        {
            printf("%d parent  %4d %4d\n", getppid(), getpid(), pid);
            if (background == 0)
            {
            }
            else
            {
                setup(inputBuffer, args, &background);
            }
        }
        else if (pid > 0)
        {
            printf("%d child  %4d %4d \n", getppid(), getpid(), pid);
            execvp(args[0], args);
            return 0;
        }
    }
    return 0;
}

// int main(void)
// {
//     int i = 0;
//     for (i = 0; i < 3; i++)
//     {
//         pid_t fpid = fork();
//         if (fpid == 0)
//             printf("son %d\n", i);
//         else
//             printf("father %d\n", i);
//     }
//     return 0;
// }