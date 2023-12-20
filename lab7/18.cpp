#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
#include<pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
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
    long long int test = 0;
#pragma omp parallel for
    for (int i = 0; i < NUM; i++)
    {

        float x = RandomFloat();
        float y = RandomFloat();
            // pthread_mutex_lock(&mutex);
        if (x * x + y * y <= 1)
        {
            currentNum++;
        }
        #pragma omp critical
        test ++;
            // pthread_mutex_unlock(&mutex);
    }
    printf("%f\n", 4.0 * currentNum / NUM);
    printf("%lld\n", test);
    return 0;
}