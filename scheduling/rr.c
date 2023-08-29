#include <stdio.h>
#include <stdlib.h>

struct Process
{
    int pid;
    int arvt;
    int wtt;
    int tat;
    int ct;
    int brstt;
    int rem_time;
};

int Minimum(int a, int b)
{
    return (a < b) ? a : b;
}

int main()
{
    struct Process Processes[20];
    float avgwt, avgtt;
    float tot_wt = 0, tot_tt = 0;
    int n;
    int qnt;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Accept process parameters
    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time for process %d: ", i+1);
        scanf("%d", &Processes[i].arvt);
        printf("Enter Burst time for process %d: ", i+1);
        scanf("%d", &Processes[i].brstt);
        Processes[i].pid = i + 1;
        Processes[i].rem_time = Processes[i].brstt;
    }

    printf("Enter the quantum size: ");
    scanf("%d", &qnt);

    // Sort the processes based on arrival time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (Processes[j].arvt > Processes[j + 1].arvt)
            {
                struct Process temp = Processes[j];
                Processes[j] = Processes[j + 1];
                Processes[j + 1] = temp;
            }
        }
    }

    // ROUND ROBIN
    int remaining = n;
    int current_time = 0;
    while (remaining)
    {
        for (int i = 0; i < n; i++)
        {
            if (Processes[i].arvt > current_time || Processes[i].rem_time <= 0)
            {
                continue;
            }
            current_time += Minimum(qnt, Processes[i].rem_time);
            Processes[i].rem_time -= Minimum(qnt, Processes[i].rem_time);

            if (Processes[i].rem_time == 0)
            {
                remaining--;
                Processes[i].ct = current_time;
            }
        }
    }


    for (int i = 0; i < n; i++)
    {
        Processes[i].tat = Processes[i].ct - Processes[i].arvt;
        Processes[i].wtt = Processes[i].tat - Processes[i].brstt;
        tot_tt += Processes[i].tat;
        tot_wt += Processes[i].wtt;
    }

    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tWait Time\tTurnaround Time\n");
    // Print the table rows
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", Processes[i].pid, Processes[i].arvt, Processes[i].brstt, Processes[i].ct, Processes[i].wtt, Processes[i].tat);
    }

    printf("Average Waiting Time: %f\n", tot_wt / n);
    printf("Average Turnaround Time: %f\n", tot_tt / n);

    return 0;
}
