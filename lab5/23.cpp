#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

bool CheckIsP(int num){
    int a = 0;
    for(int i = 2; i < num; i++){
        if(num % i == 0){
            return false;
        }
    }
    return true;
}

int main() {
    int num;
    scanf("%d", &num);
    pid_t printNum = fork();
    if(printNum == 0){
        for(int i = 2; i <= num; i++){
            if(CheckIsP(i)){
                printf("%d\n", i);
            }
        }
    }else if(printNum > 0){
        int status;
        wait(&status);
    }
    return 0;
}
