#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n;
    int counter = 0;
    printf("Enter the number upto which fibonacci is to be printed:\n");
    scanf("%d", &n);

    // two pipes C=>P and P=>C
    int p1[2];
    int p2[2];

    if (pipe(p1) == -1 || pipe(p2) == -1) {
        exit(0);
    }

    // fork child process
    pid_t pid = fork();

    if (pid == 0) { // child process
        // child reading fibonacci from parent
        close(p2[1]);
        int rec_fib[n];
        read(p2[0], rec_fib, n * sizeof(int));

        for (int i = 0; i < n; i++) {
            printf("%d\t", rec_fib[i]);
        }
        printf("\nAre the fibonacci numbers received from parent:\n");
        close(p2[0]);
        // child generating non-fibonacci numbers
        int not_fib[n * n];

        if (n >= 6) {
            for (int i = 4; i < n - 1; i++) {
                int l = rec_fib[i];
                int h = rec_fib[i + 1];
                while (l < (h - 1)) {
                    not_fib[counter] = l + 1;
                    counter++;
                    l++;
                }
            }
        } else {
            printf("No non-fibonacci numbers found..\n");
        }
     
        close(p1[0]);
        //write count to pipe
        write(p1[1],&counter,sizeof(int));
        //write non fibonacci to pipe
        write(p1[1],not_fib,counter*sizeof(int));

        
        

    } else { // Parent Process
        int num[n];
        close(p2[0]);
        num[0] = 0;
        num[1] = 1;
        // writing fibonacci from P=>C
        for (int i = 2; i <= n; i++) {
            num[i] = num[i - 1] + num[i - 2];
        }
        write(p2[1], num, n * sizeof(int));

        close(p2[1]);
        //pipe 1 for C=>P
        int not_fib[7];
        int count;
        close(p1[1]);
        //read count of non fibonacci
        read(p1[0],&count,sizeof(int));
        //read non-fibonacci array
        read(p1[0],not_fib,count*sizeof(int));

        printf("Non fibonnaci at parent side\n");
        for(int i=0;i<count;i++){
            printf("%d\t",not_fib[i]);
        }
        printf("\n");
        wait(NULL);

    }

    return 0;
}

