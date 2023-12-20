#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define SIZE 20

char* ChangeChar(char ch[]){
    for(int i = 0; i < SIZE; i++){
        if(ch[i] >= 65 && ch[i] <= 90){
            ch[i] += 32;
        }else if(ch[i] >= 97 && ch[i] <= 122){
            ch[i] -= 32;
        }
    }
    return ch;
}

int main()
{
    int p[2];
    pid_t pid = fork();
    if (pid == 0)
    {
        char str[SIZE];
        while (1)
        {
            fgets(str, sizeof(char) * SIZE, stdin);
            write(p[1], str, SIZE);
        }
    }
    else if (pid > 0)
    {
        char str[SIZE];
        while(1){
            while ((read(p[0], str, SIZE)) > 0) {
                
                printf("%s\n", ChangeChar(str)); 
            }
        }
    }
    return 0;
}