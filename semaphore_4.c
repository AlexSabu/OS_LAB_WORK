//reader - writer problem

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

sem_t rw_mutex;     //for reader-writer murual exclusion
sem_t mutex;        //for updating read_count 
int read_count=0;   //number of readers

void* writer(void *arg){
    int writer_id= *((int*)arg);
    //wait for rw_mutex
    sem_wait(&rw_mutex);
    //write item
    printf("writer %d is writing \n",writer_id);
    sleep(1);
    printf("writer %d has completed\n",writer_id);
    //signal rw_mutex
    sem_post(&rw_mutex);

    return NULL;
}

void* reader(void *arg){
    int reader_id=*((int*)arg);

    //entry secton
    sem_wait(&mutex);
    read_count++;
    if(read_count==1){
        sem_wait(&rw_mutex);
    }
    sem_post(&mutex);
    //read
    printf("reader %d is reading \n",reader_id);
    sleep(1);
    printf("reader %d has completed\n",reader_id);
    //exit section
    sem_wait(&mutex);
    read_count--;
    if(read_count==0){
        sem_post(&rw_mutex);
    }
    sem_post(&mutex);

    return NULL;
}

int main(){
    pthread_t readers[5],writers[5];
    int reader_ids[5],writer_ids[5];

    sem_init(&rw_mutex,0,1);
    sem_init(&mutex,0,1);

    for(int i=0;i<5;i++){
        reader_ids[i]=i+1;
        writer_ids[i]=i+1;

        pthread_create(&writers[i],NULL,writer,&writer_ids[i]);
        pthread_create(&readers[i],NULL,reader,&reader_ids[i]);
    }

    for(int i=0;i<5;i++){
        pthread_join(readers[i],NULL);
        pthread_join(writers[i],NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}