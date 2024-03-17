//inter process communication
//shared memory implementation

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>

#define SIZE 1024

int main(){
    int shmid;
    key_t key;
    char* shmaddr;
    char* message="Hello World";

    key=ftok(".",'R'); //key creation
    if(key==-1){
        perror("ftok");
        exit(1);
    }

    shmid=shmget(key,SIZE,IPC_CREAT | 0666); //creation of shared memory
    if(shmid==-1){
        perror("shmget");
        exit(1);
    }

    shmaddr=shmat(shmid,NULL,0); //attach shared memory to address space
    if(shmaddr==(char*)-1){
        perror("shmaddr");
        exit(1);
    }

    strncpy(shmaddr,message,strlen(message)); //write data

    if(shmdt(shmaddr)==-1){ //detatch
        perror("shmdt");
        exit(1);
    }

    shmaddr=shmat(shmid,NULL,0); //attach
    if(shmaddr==(char*)-1){
        perror("shmat");
        exit(1);
    }

    printf("data in shared memory: %s\n",shmaddr); //reading data

    if(shmdt(shmaddr)==-1){ //detatch
        perror("shmdt");
        exit(1);
    }    

    if(shmctl(shmid,IPC_RMID, NULL)==-1){
        perror("shmctl");
        exit(1);
    }
}