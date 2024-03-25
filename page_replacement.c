//page replacement algorithms

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_PAGES 20
#define MAX_FRAMES 5

typedef struct {
    int page_number;
    int timestamp; //for lru
    int counter; //for lfu
} Page;

void FIFO(Page pages[],int page_size){
    int frame_pointer=0;
    int page_faults=0;

    for(int i=0;i<page_size;i++){
        //check if page already in memory or not
        bool page_fault=true; // assume not in memory
        for(int j=0;j<MAX_FRAMES;j++){
            if(pages[i].page_number == pages[j].page_number){
                page_fault=false; //already in memory
                break;
            }
        }
        if(page_fault){//page not in memory
            if(frame_pointer < MAX_FRAMES){ //frame is available or free
                pages[frame_pointer]=pages[i];
                printf("page %d loaded into frame %d\n",pages[i].page_number,frame_pointer);
                frame_pointer++;
            }
            else{ //no free frames available
                printf("page %d replaced page %d in frame %d\n",pages[i].page_number,pages[frame_pointer%MAX_FRAMES].page_number,frame_pointer%MAX_FRAMES);
                pages[frame_pointer%MAX_FRAMES]=pages[i];
                frame_pointer++;
            }
            page_fault++;
        }

    }
    printf("number of page faults:%d\n",page_faults);
}

void LRU(Page pages[],int page_size){ //least Recently Used
    int frame_pointer=0;
    int page_faults=0;

    //iterate through the pages
    for(int i=0;i<page_size;i++){
        //check if page is already available in memory
        bool page_fault=true; //assume it is not in memory
        for(int j=0;j<MAX_FRAMES;j++){
            if(pages[i].page_number == pages[j].page_number){
                //present in memory
                page_fault=false;
                pages[j].timestamp=i;
                break;
            }
        }

        if(page_fault){
            if(frame_pointer < MAX_FRAMES){
                pages[frame_pointer]=pages[i];
                printf("page %d loaded into frame %d\n",pages[i].page_number,frame_pointer);
                frame_pointer++;
            }
            else{
                int lru_frame=0;
                for(int j=1;j<MAX_FRAMES;j++){ //finding least timestamp
                    if(pages[j].timestamp < pages[lru_frame].timestamp){
                        lru_frame= j;
                    }
                }
                printf("page %d replaces page %d at frame %d\n",pages[i].page_number,pages[lru_frame].page_number,lru_frame);
                pages[lru_frame]=pages[i];
                pages[lru_frame].timestamp=i;
            }
            page_fault++;
        }
    }
    printf("number of page faults:%d\n",page_faults);
}

void LFU(Page pages[],int page_size){ //least frequntly used
    int frame_pointer=0;
    int page_faults=0;

    for(int i=0;i<page_size;i++){
        bool page_fault=true;
        for(int j=0;j<MAX_FRAMES;j++){
            if(pages[i].page_number == pages[j].page_number){
                page_fault=false;
                pages[j].counter++;
                break;
            }
        }
        if(page_fault){
            if(frame_pointer < MAX_FRAMES){
                pages[frame_pointer]=pages[i];
                pages[frame_pointer].counter=1;
                printf("page %d loaded into frame %d\n",pages[i].page_number,frame_pointer);
                frame_pointer++;
            }
            else{
                int lfu_frame=0;
                for(int j=1;j<MAX_FRAMES;j++){ //finding least counter
                    if(pages[j].counter < pages[lfu_frame].counter){
                        lfu_frame= j;
                    }
                }
                printf("page %d replaces page %d at frame %d\n",pages[i].page_number,pages[lfu_frame].page_number,lfu_frame);
                pages[lfu_frame]=pages[i];
                pages[lfu_frame].counter=1;
            }
            page_fault++;
        }
    }
    printf("number of page faults:%d\n",page_faults);
}

int main(){
    int page_list[MAX_PAGES]={1,5,2,3,1,1,2,2,3,2,4,1,3}; //page numbers
    int page_size=13; //no. of pages

    Page pages[MAX_PAGES];
    for(int i=0;i<page_size;i++){
        pages[i].page_number=page_list[i];
        pages[i].counter=0;
        pages[i].timestamp=0;
    }
    printf("FIFO page replacement:\n");
    FIFO(pages,page_size);
    printf("LRU page replacement:\n");
    LRU(pages,page_size);
    printf("LFU page replacement:\n");
    LFU(pages,page_size);
}