#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include<time.h>
#include<stdlib.h>
#include<omp.h>

int inCircleNum = 0;
const int MAX_THREADNUM = 1000;
const int NUM_IN_THREAD = 20000;

float RandomFloat(){
    return (float)rand()/(float)RAND_MAX;
}

void CreateThread(int num){
    if(num == 0){
        return;
    }
    pid_t pid = vfork();
    if(pid == 0){
        int currentNum = 0;
        for(int i = 0; i < NUM_IN_THREAD; i++){
            float x = RandomFloat();
            float y = RandomFloat();
            if(x*x + y*y <= 1){
                currentNum++;
            }
            // printf("%d", NUM_IN_THREAD);
        }
        inCircleNum += currentNum;
        _exit(0);
    }else if(pid > 0){
        CreateThread(num-1);
    }
}

int main(){
    srand(time(0));
    int threadNum = rand() % MAX_THREADNUM + 1;
    CreateThread(threadNum);
    printf("%f\n", 4.0 * inCircleNum / (threadNum * NUM_IN_THREAD));
    return 0;
}