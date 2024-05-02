#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<sys/types.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {
    int shmid;
    key_t key;
    char* shmaddr;

    // Generate key
    key = ftok(".", 's');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create shared memory
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach shm to addr space of process
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char*)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Create child process
    pid_t pid;
    pid= fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) { // Child process
        printf("Child process is writing...\n");
        strcpy(shmaddr, "Child process has written this\n");
    } else { // Parent process
        printf("Parent process is executing...\n");
        sleep(1);
        printf("Parent accessed shm: %s\n", shmaddr);

        // Detach shm
        if (shmdt(shmaddr) == -1) {
            perror("shmdt");
            exit(1);
        } 

        // Remove shm
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }
    }
    return 0;
}
