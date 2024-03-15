#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    pid_t pid,pid1;
    pid=fork();
    if(pid<0){
        perror("fork");
        exit(1);
        }
    else if(pid==0){
        pid1=getpid();
        printf("child: %d and pid1= %d\n",pid,pid1);
    }
    else{
        pid1=getpid();
        printf("parent: %d and pid= %d\n",pid1,pid);
    }
}