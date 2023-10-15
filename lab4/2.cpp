#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
int main()
{
    /* fork a child process */
    fork();
    /* fork another child process */
    fork();
    /* and fork another */
    fork();
    int a;
    scanf("%d", &a);
    return 0;
}