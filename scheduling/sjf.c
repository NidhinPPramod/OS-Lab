#include<stdio.h>
#include<stdlib.h>

struct Process{
int pid;
int at;
int bt;
int ct;
int tat;
int wt;
int flag;
};

int main(){
struct Process P[10];
int n;
float tot_tat=0,tot_wt=0;
printf("Enter the number of process?\n");
scanf("%d",&n);
int remain;

for(int i=0;i<n;i++){
printf("Enter the Arrival and Burst Time of Process %d",i+1);
P[i].pid=i+1;
P[i].flag=0;
scanf("%d%d",&P[i].at,&P[i].bt);
}

for(int i=0;i<n-1;i++){
  for(int j=0;j<n-i-1;j++){
       if(P[j].bt>P[j+1].bt){
       struct Process temp=P[j];
       P[j]=P[j+1];
       P[j+1]=temp;
    }
  }
}

int cur_time=100;
for(int i=0;i<n;i++){
if(P[i].at<cur_time){
cur_time=P[i].at;
}
}

remain=n;

while(remain!=0){
for(int i=0;i<n;i++){
if(P[i].at<=cur_time && P[i].flag!=1){
printf("Process in order %d\n",P[i].pid);
P[i].ct=cur_time+P[i].bt;
cur_time=P[i].ct;
P[i].tat=P[i].ct-P[i].at;
P[i].wt=P[i].tat-P[i].bt;
P[i].flag=1;
remain--;
break;
}
}
}



printf("PID\tArv_T\t\tBrst_T\t\tComp_T\t\tTAT\t\tWT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",P[i].pid,P[i].at,P[i].bt,P[i].ct,P[i].tat,P[i].wt);
tot_tat+=P[i].tat;
tot_wt+=P[i].wt;
}

printf("Average Waiting Time is %f\n Average TurnAround Time is %f\n",tot_wt/n,tot_tat/n);

return 0;
}
