//usage of semaphores

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include<unistd.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum+4)%N
#define RIGHT (phnum+1)%N

int state[N];
int phil[N]={0,1,2,3,4};

sem_t mutex;
sem_t S[N];

void test(int phnum){
    if(state[phnum]== HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING){
        state[phnum]=EATING;

        sleep(2);
        printf("philosopher %d picked chopsticks: %d & %d\n",phnum+1,LEFT+1,phnum+1);
        printf("philosopher %d is eating\n",phnum+1);
    
        sem_post(&S[phnum]);
    }
}

void take_fork(int phnum){
    sem_wait(&mutex); //wait
    state[phnum]=HUNGRY;
    printf("hilosopher %d is hungry\n",phnum+1);
    test(phnum);
    sem_post(&mutex); //signal
    sem_wait(&S[phnum]); //if unable to eat
    sleep(1);
}

void put_fork(int phnum){
    sem_wait(&mutex);
    state[phnum]=THINKING;
    printf("philosopher %d put down chopsticks: %d & %d\n",phnum+1,LEFT+1,phnum+1); 
    printf("philosopher %d is thinking\n",phnum+1);

    test(LEFT);
    test(RIGHT);

    sem_post(&mutex);
}

void* philosopher(void* num) {
    int *pnum = (int*)num;
    int num_val = *pnum;
    while (1) {
        sleep(1);
        take_fork(num_val);
        sleep(0);
        put_fork(num_val);
    }
    return NULL;
}


int main(){
    int i;
    pthread_t thread[N];

    //initialize semaphores
    sem_init(&mutex,0,1);
    for(i=0;i<N;i++){
        sem_init(&S[i],0,0);
    }
    
    for(i=0;i<N;i++){
        //create philosophers
        pthread_create(&thread[i],NULL,philosopher,&phil[i]);
        printf("philosopher %d is thinking\n",i+1);
    }
    for(i=0;i<N;i++){
        pthread_join(thread[i],NULL);
    }
}
