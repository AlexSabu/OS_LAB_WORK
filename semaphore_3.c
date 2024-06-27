//producer - consumer problem

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

#define BUFFER_SIZE 5
#define NUM 10

typedef int buffer_item;
buffer_item buffer[BUFFER_SIZE];
int in=0, out=0;

sem_t empty,full;
pthread_mutex_t mutex;

void *producer(void *arg){
    int i=0;
    do{
        //produce item
        buffer_item item=i;

        //wait on empty
        sem_wait(&empty);
        //lock mutex
        pthread_mutex_lock(&mutex);
        //place item in buffer
        buffer[in]=item;
        in=(in+1)%BUFFER_SIZE;
        printf("producer has produced: %d\n",item);
        //release mutex
        pthread_mutex_unlock(&mutex);
        //signal full
        sem_post(&full);

        sleep(rand()%3);

        i++;
    } while(i<NUM);

    return NULL;
}

void *consumer(void *arg){
    int i=0;
    do{
        //wait on full
        sem_wait(&full);
        //lock mutex
        pthread_mutex_lock(&mutex);
        //consume item
        buffer_item item=buffer[out];
        out=(out+1)%BUFFER_SIZE;
        printf("consumer has consumed : %d\n",item);
        //unlock mutex
        pthread_mutex_unlock(&mutex);
        //signal empty
        sem_post(&empty);

        sleep(rand()%3);

        i++;
    }while(i<NUM);

    return NULL;
}

int main(){
    pthread_t consumer_thread,producer_thread;

    sem_init(&empty,0,BUFFER_SIZE);
    sem_init(&full,0,0);
    pthread_mutex_init(&mutex,NULL);

    pthread_create(&producer_thread,NULL,producer,NULL);
    pthread_create(&consumer_thread,NULL,consumer,NULL);

    pthread_join(producer_thread,NULL);
    pthread_join(consumer_thread,NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}