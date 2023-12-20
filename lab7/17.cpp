#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

int inCircleNum = 0;
long long int test = 0;
const int THREADNUM = 1000;
const int NUM_IN_THREAD = 20000;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

float RandomFloat()
{
    return (float)rand() / (float)RAND_MAX;
}

void *Thread(void *args)
{
    pthread_mutex_lock(&mutex);
    int currentNum = 0;
    for (int i = 0; i < NUM_IN_THREAD; i++)
    {
        float x = RandomFloat();
        float y = RandomFloat();
        if (x * x + y * y <= 1)
        {
            currentNum++;
        }
        test++;
    }
    inCircleNum += currentNum;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    pthread_t threads[THREADNUM];
    srand(time(0));

    for(int i = 0; i < THREADNUM; i++){
        pthread_create(&threads[i], NULL, Thread, NULL);
    }
    for(int i = 0; i < THREADNUM; i++){
        pthread_join(threads[i], NULL);
    }

    printf("%f\n", 4.0 * inCircleNum / (THREADNUM * NUM_IN_THREAD));
    printf("%lld\n", test);
    return 0;
}