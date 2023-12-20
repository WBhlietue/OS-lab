#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Only 2 arguments required.\n");
        printf("./main source destination.\n");
        return 0;
    }

    if (access(argv[1], F_OK) != 0)
    {
        printf("%s file not exist.\n", argv[1]);
        return 0;
    }
    int p[2];
    pid_t pid = fork();
    if (pid == 0)
    {
        close(p[1]);
        char str[100];
        ssize_t bytesRead;

        while ((bytesRead = read(p[0], str, sizeof(str))) > 0)
        {
            str[bytesRead] = '\0';
            printf("%s\n", str);
            close(p[0]);
            FILE *from = fopen(argv[1], "r");
            if (access(argv[2], F_OK) != 0)
            {
                char a[20] = "a";
                do
                {
                    printf("%s file not found, do you wanna create it Y/N?\n", argv[2]);
                    fgets(a, 20, stdin);
                } while (a[0] != 'Y' && a[0] != 'y' && a[0] != 'N' && a[0] != 'n');

                if (a[0] == 'n' || a[0] == 'N')
                {
                    return 0;
                }
            }

            FILE *to = fopen(argv[2], "w");
            if (to == NULL)
            {
                printf("Failed to create files\n");
                return 0;
            }

            char *line = NULL;
            size_t len = 0;
            ssize_t read;

            while ((read = getline(&line, &len, from)) != -1)
            {
                fputs(line, to);
            }
        }
    }
    else if (pid > 0)
    {
        // close(p[0]);
        write(p[1], argv[1], strlen(argv[1]));
        close(p[1]);
        int status;
        wait(&status);
    }

    return 0;
}