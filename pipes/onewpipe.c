#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <sys/wait.h>

int main(){
int fd[2];
int n;
printf("Enter the number of elements to be passed from parent to child:\n");
scanf("%d",&n);
if(pipe(fd)==-1){
	printf("Pipe creation failed");
	exit(0);
}

pid_t pid=fork();

if(pid==0){
close(fd[1]);
int rec_buff;
for(int i=0;i<n;i++){
read(fd[0],&rec_buff,sizeof(int));
printf("%d",rec_buff);
}
printf("are the numbers received at child process\n");
close(fd[0]);

}else{
close(fd[0]);
int readbuff;
for(int i=0;i<n;i++){
scanf("%d",&readbuff);
write(fd[1],&readbuff,sizeof(int));
}
close(fd[1]);
wait(NULL);
}

return 0;

}
