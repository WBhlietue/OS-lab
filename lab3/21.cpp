#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

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
    int a;
    scanf("%d", &a);
    if (a < 1)
    {
        printf("Enter a number greater than 1\n");
        return 0;
    }
    pid_t id = fork();
    if (id == 0)
    {
        int num = a;
        printf("%d", num);
        do
        {
            num = GetNum(num);
            printf(", %d", num);
        } while (num > 1);
        printf("\n");
    }
    else 
    {
        int status;
        wait(&status);
        // return 0;
    }
    return 0;
}