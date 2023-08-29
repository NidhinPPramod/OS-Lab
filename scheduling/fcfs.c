#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int ct;
    int at;
    int bt;
    int tat;
    int wt;
};

int main() {
    struct Process P[20];
    int n;
    float tot_tat = 0, tot_wt = 0;
    printf("Enter the number of processes?\n");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time and burst time for Process %d\n", i + 1);
        scanf("%d %d", &P[i].at, &P[i].bt);
        P[i].pid = i + 1;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (P[j].at > P[j + 1].at) {
                struct Process temp = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp;
            }
        }
    }

    int curr_time = 0;
    for (int i = 0; i < n; i++) {
        if (P[i].at > curr_time) {
            curr_time = P[i].at;
        }
        P[i].ct = curr_time + P[i].bt;
        curr_time = P[i].ct;
        P[i].tat = P[i].ct - P[i].at;
        P[i].wt = P[i].tat - P[i].bt;
    }

    printf("PID\tArr_T\t\tBrst_T\t\tComp_T\t\tTAT\t\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", P[i].pid, P[i].at, P[i].bt, P[i].ct, P[i].tat, P[i].wt);
        tot_tat += P[i].tat;
        tot_wt += P[i].wt;
    }

    printf("Average TurnAroundTime: %f\nAverage Wait Time: %f\n", tot_tat / n, tot_wt / n);

    return 0;
}

