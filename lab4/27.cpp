#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

const double fibo = (1 + pow(5, 0.5)) / 2;

double CalculateFibonacci(int num, double fibo)
{
    return (pow(fibo, num) - pow(1 - fibo, num)) / pow(5, 0.5);
}


void *Calc(void* arg)
{
    printf("%.0lf, %d\n", CalculateFibonacci(*(int*)(arg), fibo), (*(int*)(arg)));
    return NULL;
}

int main()
{
    int num;
    scanf("%d", &num);
    pthread_t th[num];
    int nums[num];
    for (int i = 0; i < num; i++)
    {
        nums[i] = i+1;
        pthread_create(&th[i], NULL, Calc, &nums[i]);
    }
    for(int i = 0; i < num; i++){
        pthread_join(th[i], NULL);
    }
    return 0;
}