#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_PAGES 20
#define MAX_FRAMES 3

typedef struct{
    int page_number;
    int timestamp;
    int counter;
} Page;

void FIFO(Page page_list[],int num){
    Page frames[MAX_FRAMES];
    for(int i=0;i<MAX_FRAMES;i++){
        frames[i].page_number=-1;
        frames[i].timestamp=0;
        frames[i].counter=0;
    }
    int page_faults=0;
    int frame_pointer=0;

    for(int i=0;i<num;i++){
        bool page_fault=true;
        for(int j=0;j<MAX_FRAMES;j++){
            if(page_list[i].page_number == frames[j].page_number){
                page_fault=false;
                break;
            }
        }
        if(page_fault){
            page_faults++;
            if(frame_pointer < MAX_FRAMES){
                frames[frame_pointer]=page_list[i];
                printf("page %d loaded into frame %d\n",page_list[i].page_number,frame_pointer);
                frame_pointer++;
            }
            else{
                printf("page %d replaced page %d in frame %d\n",page_list[i].page_number,frames[frame_pointer%MAX_FRAMES].page_number,frame_pointer%MAX_FRAMES);
                frames[frame_pointer%MAX_FRAMES]=page_list[i];
                frame_pointer++;
            }
        }
    }
    printf("number of page faults:%d\n",page_faults);
}

void LRU(Page pages[],int page_size){
    Page frames[MAX_FRAMES];
    for(int i=0;i<MAX_FRAMES;i++){
        frames[i].page_number=-1;
        frames[i].timestamp=0;
        frames[i].counter=0;
    }
    int frame_pointer=0;
    int page_faults=0;
    for(int i=0;i<page_size;i++){
        bool page_fault=true;
        for(int j=0;j<MAX_FRAMES;j++){
            if(pages[i].page_number == frames[j].page_number){
                page_fault=false;
                frames[j].timestamp=i;
                break;
            }
        }
        if(page_fault){
            page_faults++;
            if(frame_pointer < MAX_FRAMES){
                frames[frame_pointer]=pages[i];
                printf("page %d loaded into frame %d\n",pages[i].page_number,frame_pointer);
                frame_pointer++;
            }
            else{
                int lru=0;
                for(int j=1;j<MAX_FRAMES;j++){
                    if(frames[j].timestamp < frames[lru].timestamp){
                        lru=j;
                    }
                }
                printf("page %d replaces page %d at frame %d\n",pages[i].page_number,frames[lru].page_number,lru);
                frames[lru]=pages[i];
                frames[lru].timestamp=i;
            }
        }
        printf("frames: ");
        for(int k=0;k<MAX_FRAMES;k++){
            printf("%d  ",frames[k].page_number);
        }
        printf("\n");
    }
        printf("number of page faults:%d\n",page_faults);
}

void LFU(Page pages[],int num){
    Page frames[MAX_FRAMES];
    for(int i=0;i<MAX_FRAMES;i++){
        frames[i].page_number=-1;
        frames[i].counter=frames[i].timestamp=0;
    }
    int frame_pointer=0;
    int page_faults=0;
    for(int i=0;i<num;i++){
        bool page_fault=true;
        for(int j=0;j<MAX_FRAMES;j++){
            if(frames[j].page_number==pages[i].page_number){
                page_fault=false;
                frames[j].counter++;
                break;
            }
        }
        if(page_fault){
            page_faults++;
            if(frame_pointer<MAX_FRAMES){
                frames[frame_pointer]=pages[i];
                printf("page %d loaded into frame %d\n",pages[i].page_number,frame_pointer);
                frame_pointer++;
            }
            else{
                int lfu=0;
                for(int k=0;k<MAX_FRAMES;k++){
                    if(frames[k].counter<frames[lfu].counter){
                        lfu=k;
                    }
                }
                printf("page %d replaced page %d in frame %d\n",pages[i].page_number,frames[lfu].page_number,lfu);
                frames[lfu]=pages[i];
                frames[lfu].counter=1;
            }
        }
        printf("frames: ");
        for(int k=0;k<MAX_FRAMES;k++){
            printf("%d  ",frames[k].page_number);
        }
        printf("\n");
    }
    printf("page faults: %d\n",page_faults);
}

int main(){
    int page_list[MAX_PAGES]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1}; //page numbers
    int page_size=20; //no. of pages

    Page pages[MAX_PAGES];
    for(int i=0;i<page_size;i++){
        pages[i].page_number=page_list[i];
        pages[i].counter=0;
        pages[i].timestamp=0;
    }
    printf("FIFO page replacement:\n");
    FIFO(pages,page_size);
    printf("\n");
    printf("LRU page replacement:\n");
    LRU(pages,page_size);
    // printf("LFU page replacement:\n");
    // LFU(pages,page_size);
}

//7,2,7,3,2,5,3,4,6,7,7,1,5,6,1