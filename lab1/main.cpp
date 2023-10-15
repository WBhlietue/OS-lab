#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>

#define MAX_LINE 80

struct CommandHistory
{
    char args[MAX_LINE + 1][MAX_LINE];
};

CommandHistory history[10];
char *tmpArgs[MAX_LINE];

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
        if (i != 0)
        {
            strcat(str, " ");
        }
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

bool isSelectedCommand = false;

void HistoryInput()
{
    char c[3];
    do
    {
        if (!isSelectedCommand)
        {
            printf("Input X to call command\n");
            printf("Input R to call last command\n");
            printf("Input O to exit history\n");
            printf("Input P or Ctrl+D to exit program\n");
        }
        if (fgets(c, sizeof(char) * 3, stdin) == NULL)
        {
            printf("\n");
            exit(0);
        }
        if (isSelectedCommand)
        {
            if (c[0] != ' ')
            {
                for (int i = 9; i >= 0; i--)
                {
                    if (strlen(GetHistory(i)) > 0 && GetHistory(i)[0] == c[0])
                    {
                        for (int j = 0; j < MAX_LINE; j++)
                        {
                            if (strlen(history[i].args[j]) > 0)
                            {
                                strcpy(tmpArgs[j], history[i].args[j]);
                            }
                            else
                            {
                                tmpArgs[j] = NULL;
                                // strcpy(tmpArgs[j], NULL);
                            }
                        }
                        pid_t pid = fork();
                        if (pid == 0)
                        {
                            printf("%s\n", tmpArgs[0]);
                            execvp(tmpArgs[0], tmpArgs);
                            // for(int k = 0; k < MAX_LINE; k++){
                            //     printf("%s\n", tmpArgs[k]);
                            // }
                            return;
                        }
                        else
                        {
                            int s = 0;
                            wait(&s);
                            isSelectedCommand = false;
                            return;
                        }
                        break;
                    }
                }
            }
        }
        else
        {
            switch (c[0])
            {
            case 'x':
                isSelectedCommand = true;
                break;
            case 'r':
                for (int i = 9; i >= 0; i--)
                {
                    if (strlen(GetHistory(i)) > 0)
                    {
                        pid_t pid = fork();
                        if (pid == 0)
                        {
                            for (int j = 0; j < MAX_LINE; j++)
                            {
                                if (strlen(history[i].args[j]) > 0)
                                {
                                    strcpy(tmpArgs[j], history[i].args[j]);
                                }
                                else
                                {
                                    strcpy(tmpArgs[j], "");
                                }
                            }
                            execvp(tmpArgs[0], tmpArgs);
                            printf("%s\n", tmpArgs[0]);
                            return;
                        }
                        else
                        {
                            int s = 0;
                            wait(&s);
                            return;
                        }
                        break;
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
        }
    } while (c[0] != 'O');
}

jmp_buf jump_buffer;

void handle_SIGINT(int sig)
{
    isSelectedCommand = false;
    PrintHistory();
    HistoryInput();
    siglongjmp(jump_buffer, 1);
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
    for (int i = 0; i < MAX_LINE; i++)
    {
        tmpArgs[i] = (char *)malloc(sizeof(char) * MAX_LINE);
    }
    while (1)
    {
        background = 0;
        char inputBuffer[MAX_LINE];
        for (int i = 0; i < MAX_LINE + 1; i++)
        {
            args[i] = NULL;
        }
        if (sigsetjmp(jump_buffer, 1) == 0)
        {
            setup(inputBuffer, args, &background);
            pid_t pid = fork();
            if (pid > 0)
            {

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
    }
    return 0;
}

