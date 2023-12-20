#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int avarageNum = 0;
int maximiumNum = 0;
int minimiumNum = 0;

int main() {
    int array[100];
    int size = 0;
    char c;
    int status;

    for (int i = 0; c != '\n' && i < 100; i++) {
        scanf("%d%c", &array[i], &c);
        size++;
    }

    pid_t avarage = vfork();

    if (avarage == 0) {
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += array[i];
        }
        avarageNum = sum / size;
        _exit(0);
    } else if (avarage > 0) {
        pid_t min = vfork();

        if (min == 0) {
            int m = array[0];
            for (int i = 1; i < size; i++) {
                if (array[i] < m) {
                    m = array[i];
                }
            }
            minimiumNum = m;
            _exit(0);
        } else if (min > 0) {
            pid_t max = vfork();

            if (max == 0) {
                int m = array[0];
                for (int i = 1; i < size; i++) {
                    if (array[i] > m) {
                        m = array[i];
                    }
                }
                maximiumNum = m;
                _exit(0);
            } else if (max > 0) {
                while ((wait(&status)) > 0) {
                    
                }
                printf("Avarage: %d\n", avarageNum);
                printf("Minimium: %d\n", minimiumNum);
                printf("Maximium: %d\n", maximiumNum);
            }
        }
    }
    return 0;
}
