#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

int inCircleNum = 0;
const int NUM = 10000000;

float RandomFloat()
{
    return (float)rand() / (float)RAND_MAX;
}

int main()
{
    srand(time(0));
    int currentNum = 0;
#pragma omp parallel for
    for (int i = 0; i < NUM; i++)
    {
        float x = RandomFloat();
        float y = RandomFloat();
        if (x * x + y * y <= 1)
        {
            currentNum++;
        }
    }
    printf("%f\n", 4.0 * currentNum / NUM);
    return 0;
}