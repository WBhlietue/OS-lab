#include <stdio.h>
#include <omp.h>
int main()
{
    int a = 0;
#pragma omp parallel for
    for (int i = 0; i < 10; i++)
    {
        a += i;
        printf("%i\n", i);
    }
    printf("%d", a);
    return 0;
}