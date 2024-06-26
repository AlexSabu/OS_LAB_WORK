#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

#define SHM_SIZE 1024

int main(){
    int shmid;
    key_t key;
    char* pointer;

    key = ftok(".",'s');
    if(key==-1){
        perror("ftok");
        exit(1);
    }

    shmid=shmget(key,SHM_SIZE,IPC_CREAT | 0666);
    if(shmid==-1){
        perror("shmget");
        exit(1);
    }

    pointer=shmat(shmid,NULL,0);
    if(pointer==(char*)(-1)){
        perror("shmat");
        exit(1);
    }

    //writing
    printf("checking...\n");
    strcpy(pointer,"parent process");
    printf("shared memory_1: %s\n",pointer);

    pid_t pid;
    pid=fork();
    if(pid==0){
        printf("shared memory_2: %s\n",pointer);
        strcat(pointer,"\nchild process");
        printf("shared memory_3: %s\n",pointer);
        exit(0);
    }
    else if (pid>0) {
        sleep(1);
        printf("shared memory_4: %s\n",pointer);
        strcat(pointer,"\nback to parent process");
        printf("shared memory_5: %s\n",pointer);
    }
    else{
        perror("fork");
        exit(1);
    }

    if(shmdt(pointer)==-1){
        perror("shmdt");
        exit(1);
    }

    if(shmctl(shmid,IPC_RMID,NULL)==-1){
        perror("shmctl");
        exit(1);
    }

    return 0;
}