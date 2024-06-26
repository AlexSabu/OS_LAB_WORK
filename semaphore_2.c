//counter variable updation using sem

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t sem;
int counter;

void* increment(void *arg){
    sem_wait(&sem); //entry section
    counter++;      //critical secton
    sem_post(&sem); //exit section

    return NULL; 
}

int main(){
    pthread_t thread[10];

    if(sem_init(&sem,0,5)!=0){
        perror("sem_init");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<10;i++){
        if(pthread_create(&thread[i],NULL,increment,NULL)!=0){
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i <10; i++){
        if(pthread_join(thread[i],NULL)!=0){
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }
    sem_destroy(&sem);
    printf("counter: %d",counter);
    return 0;
}


//user defined sem usage


// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <semaphore.h>
// #include <fcntl.h>   // For O_CREAT
// #include <errno.h>   // For errno
// #include <string.h>  // For strerror

// #define SEM_NAME "/my_semaphore"

// int main() {
//     sem_t *sem;
//     pid_t pid;
//     int shmem = 0;

//     // Initialize the semaphore
//     sem = sem_open(SEM_NAME, O_CREAT, 0644, 1);  // Initial value: 1
//     if (sem == SEM_FAILED) {
//         perror("sem_open");
//         exit(EXIT_FAILURE);
//     }

//     // Create a child process
//     pid = fork();
//     if (pid < 0) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     } else if (pid == 0) {
//         // Child process
//         printf("Child process attempting to lock the semaphore...\n");
//         if (sem_wait(sem) == -1) {
//             perror("sem_wait");
//             exit(EXIT_FAILURE);
//         }

//         printf("Child process locked the semaphore.\n");

//         // Access shared resource
//         printf("Child process incrementing shared variable.\n");
//         shmem++;
//         printf("Child process updated shared variable: %d\n", shmem);

//         // Release the semaphore
//         if (sem_post(sem) == -1) {
//             perror("sem_post");
//             exit(EXIT_FAILURE);
//         }

//         printf("Child process released the semaphore.\n");
//         exit(EXIT_SUCCESS);
//     } else {
//         // Parent process

//         // Wait for child process to finish
//         wait(NULL);

//         printf("Parent process attempting to lock the semaphore...\n");
//         if (sem_wait(sem) == -1) {
//             perror("sem_wait");
//             exit(EXIT_FAILURE);
//         }

//         printf("Parent process locked the semaphore.\n");

//         // Access shared resource
//         printf("Parent process incrementing shared variable.\n");
//         shmem++;
//         printf("Parent process updated shared variable: %d\n", shmem);

//         // Release the semaphore
//         if (sem_post(sem) == -1) {
//             perror("sem_post");
//             exit(EXIT_FAILURE);
//         }

//         printf("Parent process released the semaphore.\n");
//     }

//     // Close and unlink the semaphore
//     if (sem_close(sem) == -1) {
//         perror("sem_close");
//         exit(EXIT_FAILURE);
//     }

//     if (sem_unlink(SEM_NAME) == -1) {
//         perror("sem_unlink");
//         exit(EXIT_FAILURE);
//     }

//     return 0;
// }
