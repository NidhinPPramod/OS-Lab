#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int isPrime(int n) {
    int flag = 1;
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return n;
}

int main() {
    int fd[2];
    int n;
    printf("Enter the limit of numbers passed from parent to child\n");
    scanf("%d", &n);
    if (pipe(fd) == -1) {
        exit(0);
    }
    pid_t pid = fork();
    if (pid == 0) {
        close(fd[1]);
        int rec_buff[20];
        for (int i = 0; i < n; i++) {
            read(fd[0], &rec_buff[i], sizeof(int));
        }
        close(fd[0]);
        for (int i = 0; i < n; i++) {
            if (isPrime(rec_buff[i]) != 0) {
                printf("%d\n", rec_buff[i]);
            }
        }
        printf("Are the Prime numbers\n");
    } else {
        close(fd[0]);
        int num;
        for (int i = 0; i < n; i++) {
            scanf("%d", &num);
            write(fd[1], &num, sizeof(int));
        }
        printf("Generating Prime numbers....\n");
        close(fd[1]);
    }
    wait(NULL);
    return 0;
}

