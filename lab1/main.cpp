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
};

CommandHistory history[10];

void ToHistory(char **args)
{
    static int typedHistory = 0;
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
        typedHistory++;
    }
}
char *GetHistory(int num)
{
    char *str = (char *)malloc(sizeof(char) * MAX_LINE);
    for (int i = 0; i <= MAX_LINE; i++)
    {
        if (strlen(history[num].args[i]) == 0)
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
void HistoryInput()
{
    char c;
    do
    {
        printf("DON'T PRESS CTRL+D !!!!!!!!!!\n");
        printf("Input X to call command\n");
        printf("Input R to call last command\n");
        printf("Input O to exit history\n");
        printf("Input P to exit program\n");
        c = getchar();
        // scanf("%c", &c);
        switch (c)
        {
        case 'x':
            break;
        case 'r':
        for(int i = 9; i >= 0; i--){
            if(strlen( GetHistory(i)) > 0){
                // ToHistory(history[i].args);
            }
        }
            break;
        case 'o':
            return;
        case 'p':
            exit(0);
            break;

        default:
            break;
        }
    } while (c != 'O');
}
void handle_SIGINT(int sig)
{
    printf("\nCaught SIGINT, exiting now\n");
    PrintHistory();
    HistoryInput();
    printf("Enter enter to continue\n");
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
            // if (typedHistory == 9)
            // {
            //     for (int i = 0; i < 9; i++)
            //     {
            //         history[i] = history[i + 1];
            //     }
            //     for (int i = 0; i <= MAX_LINE; i++)
            //     {
            //         if (args[i] == NULL)
            //         {
            //             break;
            //         }
            //         strcpy(history[typedHistory].args[i], args[i]);
            //     }
            // }
            // else
            // {
            //     for (int i = 0; i <= MAX_LINE; i++)
            //     {

            //         if (args[i] == NULL)
            //         {
            //             break;
            //         }
            //         else
            //         {
            //             strcpy(history[typedHistory].args[i], args[i]);
            //         }
            //     }
            // }
            ToHistory(args);
            if (background == 0)
            {
                int status = 0;
                wait(&status);
                // typedHistory++;
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