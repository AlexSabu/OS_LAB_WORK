#include<stdio.h>

#define NUM_BLOCKS 20
#define BLOCK_SIZE 1000

struct File{
    int size;
    int blocks[10];
};

void initialize(struct File files[],int num){
    for(int i=0;i<num;i++){
        for(int j=0;j<10;j++){
            files[i].blocks[j]=0;
        }
    }
}


void sequential(struct File files[], int num_files) {
    int remaining_blocks = NUM_BLOCKS;

    for (int i = 0; i < num_files; i++) {
        int required_blocks = (files[i].size + BLOCK_SIZE - 1) / BLOCK_SIZE;
        if (required_blocks <= remaining_blocks) {
            printf("File %d allocated at blocks: ", i + 1);
            for (int j = 0; j < required_blocks; j++) {
                printf("%d ", NUM_BLOCKS - remaining_blocks + j);
            }
            printf("\n");
            remaining_blocks -= required_blocks;
        } else {
            printf("File %d cannot be allocated due to insufficient space.\n", i + 1);
        }
    }
}

void indexed(struct File files[], int num_files){
    int remaining_blocks=NUM_BLOCKS;
    for(int i=0;i<num_files;i++){
        int required_blocks=(files[i].size+BLOCK_SIZE-1) / BLOCK_SIZE;
        int total_required_blocks=required_blocks+1; //including index block
        if(total_required_blocks <= remaining_blocks){
            printf("file %d allocated at\n",i+1);
            int index_block=NUM_BLOCKS-remaining_blocks;
            printf("index block-%d \n",index_block);
            printf("blocks: ");
            for(int j=0;j<required_blocks;j++){
                printf("%d ",index_block+j+1);
            }
            printf("\n");
            remaining_blocks-=total_required_blocks;
        }
        else{
            printf("File %d cannot be allocated due to insufficient space.\n", i + 1);
        }
    }
}

int main(){
    int num_files;
    printf("input num_files: ");scanf("%d",&num_files);
    struct File files[num_files];
    printf("input file sizes:\n");
    for(int i=0;i<num_files;i++){
        printf("file %d: ",i+1);scanf("%d",&files[i].size);
    }
    initialize(files,num_files);
    printf("sequential:\n");
    sequential(files,num_files);
    initialize(files,num_files);
    printf("indexed:\n");
    indexed(files,num_files);
}