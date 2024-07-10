#include<stdio.h>

#define MEMORY_SIZE 1000
#define NUM_PARTIOTNS 5

typedef struct{
    int start;
    int size;
    int is_allocated;
} Partition;

Partition memory[NUM_PARTIOTNS];

void initialize(){
    int temp[5]={160,200,500,250,100};
    int offset=0;
    for(int i=0;i<NUM_PARTIOTNS;i++){
        //memory[i].size=MEMORY_SIZE/NUM_PARTIOTNS;
        memory[i].size=temp[i];
        memory[i].start=offset;
        offset+=memory[i].size;
        memory[i].is_allocated=0;
    }
}

int firstFit(int process_size){
    for(int i=0;i<NUM_PARTIOTNS;i++){
        if(!memory[i].is_allocated && memory[i].size >= process_size){
            memory[i].is_allocated=1;
            return memory[i].start;
        }
    }
    return -1;
}

int worstFit(int process_size){
    int max_size=-1, max_index=-1;
    for(int i=0;i<NUM_PARTIOTNS;i++){
        if(!memory[i].is_allocated && memory[i].size >= process_size && memory[i].size > max_size){
            max_size=memory[i].size;
            max_index=i;
        }
    }
    if(max_index!=-1){
        memory[max_index].is_allocated=1;
        return memory[max_index].start;
    }
    return -1;
}

int bestFit(int process_size){
    int min_size=MEMORY_SIZE+1, min_index=-1;
    for(int i=0;i<NUM_PARTIOTNS;i++){
        if(!memory[i].is_allocated && memory[i].size >= process_size && memory[i].size < min_size){
            min_size=memory[i].size;
            min_index=i;
        }
    }
    if(min_index!=-1){
        memory[min_index].is_allocated=1;
        return memory[min_index].start;
    }
    return -1;
}


int main() {
    initialize();
    
    // Example allocation requests
    int process_size[] = {200, 150, 300, 100, 400};
    
    printf("First Fit:\n");
    for (int i = 0; i < 5; i++) {
        int start = firstFit(process_size[i]);
        if (start != -1) {
            printf("Process of size %d allocated at position %d\n", process_size[i], start);
        } else {
            printf("Unable to allocate process of size %d\n", process_size[i]);
        }
    }
    
    initialize();

    printf("\nWorst Fit:\n");
    for (int i = 0; i < 5; i++) {
        int start = worstFit(process_size[i]);
        if (start != -1) {
            printf("Process of size %d allocated at position %d\n", process_size[i], start);
        } else {
            printf("Unable to allocate process of size %d\n", process_size[i]);
        }
    }
    
    initialize();

    printf("\nBest Fit:\n");
    for (int i = 0; i < 5; i++) {
        int start = bestFit(process_size[i]);
        if (start != -1) {
            printf("Process of size %d allocated at position %d\n", process_size[i], start);
        } else {
            printf("Unable to allocate process of size %d\n", process_size[i]);
        }
    }
    
    return 0;
}
