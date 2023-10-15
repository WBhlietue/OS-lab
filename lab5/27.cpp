#include<math.h>
#include<stdio.h>
#include <unistd.h>
#include <sys/wait.h>

double CalculateFibonacci(int num, double fibo){
    return (pow(fibo, num) - pow(1-fibo, num))/pow(5, 0.5);
}

void Recurse(int total, int current, double fibo){
    if(current > total){
        return;
    }
    pid_t pid = fork();
    if(pid == 0){
        printf("%.0lf\n", CalculateFibonacci(current, fibo));
    }else if(pid > 0){
        Recurse(total, current+1, fibo);
    }
}

int main(){
    const double fibo = (1 + pow(5, 0.5)) / 2;
    int num;
    scanf("%d", &num);
    Recurse(num, 1, fibo);
    return 0;
}