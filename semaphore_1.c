//shared memory using semaphore

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

int main() {
    key_t key;
    int shmid;
    sem_t sem;
    char *pointer;
    pid_t pid;
    int sem_value;

    sem_init(&sem, 0, 1);

    key = ftok(".", 's');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    pointer = shmat(shmid, NULL, 0);
    if (pointer == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    pid = fork();
    if (pid == 0) {  // Child process
        sem_getvalue(&sem, &sem_value);
        printf("sem (before wait): %d\n", sem_value);

        sem_wait(&sem);

        sem_getvalue(&sem, &sem_value);
        printf("sem (after wait): %d\n", sem_value);

        strcat(pointer, "second_child ->");
        sem_post(&sem);

        sem_getvalue(&sem, &sem_value);
        printf("sem (after post): %d\n", sem_value);

        printf("\n%s\n", pointer);
        exit(0);
    } else if (pid > 0) {  // Parent process
        sem_getvalue(&sem, &sem_value);
        printf("sem (before wait): %d\n", sem_value);

        sem_wait(&sem);

        sem_getvalue(&sem, &sem_value);
        printf("sem (after wait): %d\n", sem_value);

        strcpy(pointer, "first_parent ->");
        sem_post(&sem);

        sem_getvalue(&sem, &sem_value);
        printf("sem (after post): %d\n", sem_value);

        printf("\nshm: %s\n", pointer);

        wait(NULL);  // Wait for child process to finish

        sem_getvalue(&sem, &sem_value);
        printf("sem (before wait): %d\n", sem_value);

        sem_wait(&sem);

        sem_getvalue(&sem, &sem_value);
        printf("sem (after wait): %d\n", sem_value);

        strcat(pointer, "third_parent ->");
        sem_post(&sem);

        sem_getvalue(&sem, &sem_value);
        printf("sem (after post): %d\n", sem_value);

        printf("\n%s\n", pointer);
    } else {
        perror("fork");
        exit(1);
    }

    if (shmdt(pointer) == -1) {
        perror("shmdt");
        exit(1);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    sem_destroy(&sem);

    return 0;
}

// #include<stdio.h>
// #include<stdlib.h>
// #include<unistd.h>
// #include<sys/ipc.h>
// #include<sys/shm.h>
// #include<sys/types.h>
// #include<sys/wait.h>
// #include<semaphore.h>
// #include<string.h>

// int main(){
//     key_t key;
//     int shmid;
//     char* pointer;
//     pid_t pid;
//     sem_t *sem;
//     int sem_val;

//     shmid=shmget(IPC_PRIVATE,sizeof(sem_t),IPC_CREAT | 0666);
//     sem=shmat(shmid,NULL,0);

//     sem_init(sem,1,0);

//     key=ftok(".",'s');

//     shmid=shmget(key,1024,IPC_CREAT | 0666);

//     pointer=shmat(shmid,NULL,0);

//     strcpy(pointer,"hello");
//     printf("shm: %s\n",pointer);

//     pid=fork();
//     if(pid==0){
//         strcat(pointer," child");
//         printf("%s\n",pointer);
//         sem_post(sem);
//     }
//     else if(pid>0){
//         sem_wait(sem);
//         strcat(pointer," parent");
//         printf("%s\n",pointer);
//     }
//     else{
//         perror("fork");
//         exit(1);
//     }

//     shmdt(pointer);
//     shmdt(sem);

//     shmctl(shmid,IPC_RMID,NULL);
// }

