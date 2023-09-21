#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_LINE 80

struct CommandHistory
{
    char args[MAX_LINE + 1][MAX_LINE];
    char firstLetter;
};

CommandHistory history[10];
char *GetHistory(int num)
{
    char *str = (char *)malloc(sizeof(char) * MAX_LINE);
    for (int i = 0; i <= MAX_LINE; i++)
    {
        if (strlen( history[num].args[i]) == 0)
        {
            break;
        }
        strcat(str, " ");
        strcat(str, history[num].args[i]);
    }
    return str;
}
void PrintHistory()
{
    // system("clear");
    printf("\nHistory:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d. %s\n", (i + 1), GetHistory(i));
    }
}
void handle_SIGINT(int sig)
{
    write(STDOUT_FILENO, "\nCaught SIGINT, exiting now\n", sizeof("\nCaught SIGINT, exiting now\n"));
    PrintHistory();
    exit(0);
}

void setup(char inputBuffer[], char *args[], int *background)
{
    printf("COMMAND->");
    if (fgets(inputBuffer, 100000, stdin) == NULL)
    {
        printf("\n");
        exit(0);
    }

    inputBuffer[strlen(inputBuffer) - 1] = '\0';
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
            *background = 0;
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
}

int main()
{
    signal(SIGINT, &handle_SIGINT);
    int background;
    char *args[MAX_LINE + 1];
    int typedHistory = 0;

    while (1)
    {
        background = 0;
        char inputBuffer[MAX_LINE];
        for (int i = 0; i < MAX_LINE + 1; i++)
        {
            args[i] = NULL;
        }
        setup(inputBuffer, args, &background);
        pid_t pid = fork();
        if (pid > 0)
        {
            if (typedHistory == 9)
            {
                for (int i = 0; i < 9; i++)
                {
                    history[i] = history[i + 1];
                }
                for (int i = 0; i <= MAX_LINE; i++)
                {
                    if (args[i] == NULL)
                    {
                        break;
                    }
                    strcpy(history[typedHistory].args[i], args[i]);
                }
            }
            else
            {
                for (int i = 0; i <= MAX_LINE; i++)
                {

                    if (args[i] == NULL)
                    {
                        break;
                    }
                    else
                    {
                        strcpy(history[typedHistory].args[i], args[i]);
                    }
                }
            }
            if (background == 0)
            {
                int status = 0;
                wait(&status);
                typedHistory++;
            }
            else
            {
                setup(inputBuffer, args, &background);
            }
        }
        else if (pid == 0)
        {

            execvp(args[0], args);
            return 0;
        }
    }
    return 0;
}

// int main()
// {
//     strcpy(history[0].args[0], "ls");
//     // history[0].args[1] = (char*)"-l";
//     // history[0].args[2] = NULL;
//     history[0].firstLetter = 'g';
//     PrintHistory();
//     return 0;
// }