#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define N 10

pthread_barrier_t barrier;

int barrier_point(){
    return pthread_barrier_wait(&barrier);
}

int init(int n){
    return pthread_barrier_init(&barrier, NULL, n);
}

void *Thread(void *args){
    sleep(*(int*)(args));
    printf("%d\n", *(int*)(args));
    int a = barrier_point();
    printf("Thread Complete %d | %d\n", *(int*)(args), a);
    return NULL;
}
int main()
{
    pthread_barrier_init(&barrier, NULL, N);
    pthread_t threads[N];
    int nums[N];
    init(N);
    for(int i= 0; i < N; i++){
        nums[i] = i;
        pthread_create(&threads[i], NULL, Thread, &nums[i]);
    }
    for(int i = 0; i < N; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_barrier_destroy(&barrier);
    printf("Program Over");
    return 0;
}