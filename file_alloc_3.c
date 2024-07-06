#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<unistd.h>
#include<stdbool.h>

#define BLOCK_SIZE 500
#define NUM_BLOCKS 30

struct Block{
    bool is_allocated;
    struct Block* next;
};

void contiguous(int file_size){
    int remaining=file_size;
    int blocks[BLOCK_SIZE];
    for(int i=0;i<BLOCK_SIZE;i++){
        blocks[i]=-1;
    }
    int index=0;
    while(remaining>0){
        if(index<NUM_BLOCKS){
            blocks[index]=1;
            remaining-=BLOCK_SIZE;
            index++;
        }
        else{
            printf("blocks limit exceeded.");
            exit(1);
        }
    }
    printf("blocks:\n");
    for(int i=0;i<NUM_BLOCKS;i++){
        printf("%d  ",blocks[i]);
    }
    printf("\n");
}

void linked(int file_size){
    int remaining=file_size,index=0;
    int un_allocated=NUM_BLOCKS;
    struct Block *header=NULL;

    while(remaining>0){
        un_allocated--;
        struct Block *new=(struct Block*)malloc(sizeof(struct Block));
        new->is_allocated=true;
        new->next=NULL;
        remaining-=BLOCK_SIZE;
        index++;
        if(header==NULL){
            header=new;
        }
        else{
            struct Block *current=header;
            while(current->next!=NULL){
                current=current->next;
            }
            current->next=new;
            current=new;
        }
    }
    printf("linked: ");
    struct Block *current=header;
    int i=0;
    while(current!=NULL){
        printf("%d -> ",i+1);
        current=current->next;
        i++;
    }
    printf("end");
    printf("\nremaining: (%d):",un_allocated);
    for(int i=0;i<un_allocated;i++){
        printf("-1  ");
    }
    printf("\n");

}

void indexed(int file_size){
    int remaining=file_size;
    int blocks[NUM_BLOCKS];
    for(int i=0;i<NUM_BLOCKS;i++){
        blocks[i]=-1;
    }
    int index_block=0;
    while(blocks[index_block]!=-1){
        index_block++;
        if(index_block>=NUM_BLOCKS){
            printf("cannot find index block");
            exit(1);
        }
    }
    blocks[index_block]=1;

    int* list_of_blocks[10]={ NULL };
    int i=0;
    while(remaining>0 && i<10){
        int data_block=0;
        while(blocks[data_block]!=-1){
            data_block++;
            if(index_block>=NUM_BLOCKS){
                printf("cannot find index block");
                exit(1);
            }
        }
        blocks[data_block]=1;
        list_of_blocks[i]=&blocks[data_block];
        remaining-=BLOCK_SIZE;
        i++;
    }
    if(remaining>0){
        printf("file too large");
        exit(1);
    }

    printf("Indexed allocation:\nIndex block (%d): ",index_block);
    for(int j=0;j<10;j++){
        if(list_of_blocks[j]!= NULL){
            printf("%d  ", (int)(list_of_blocks[j] - blocks));
        }else{
            printf("NULL  ");
        }
    }
    printf("\n");
}

int main(){
    int file_size;
    printf("input file_size: ");scanf("%d",&file_size);
    //contiguous(file_size);
    //linked(file_size);
    indexed(file_size);
}