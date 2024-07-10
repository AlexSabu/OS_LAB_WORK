#include<stdio.h>
#include<stdlib.h>

#define MAX_BLOCKS 100

typedef struct{
    int start,length;
} SequentialFile;

typedef struct{
    int index_block;
    int *blocks;
    int length;
} IndexedFile;

typedef struct LinkedBlock{
    int block_no;
    struct LinkedBlock *next;
} LinkedBlock;

typedef struct{
    LinkedBlock *start;
    LinkedBlock *end;
} LinkedFile;

int freeBlocks[MAX_BLOCKS];
int nextFreeBlock=0;

void initializeFreeBlocks(){
    for(int i=0;i<MAX_BLOCKS;i++){
        freeBlocks[i]=1;
    }
}

int allocateBlock(){
    for(int i=nextFreeBlock;i<MAX_BLOCKS;i++){
        if(freeBlocks[i]){
            freeBlocks[i]=0;
            nextFreeBlock=i+1;
            return i;
        }
    }
    return -1;
}

void sequentialAllocation(SequentialFile *file,int length){
    for(int i=0;i<MAX_BLOCKS-length;i++){
        int found=1;
        for(int j=0;j<length;j++){
            if(!freeBlocks[i+j]){
                found=0;
                break;
            }
        }
        if(found){
            file->start=i;
            file->length=length;
            for(int j=0;j<length;j++){
                freeBlocks[i+j]=0;
            }
            return;
        }
    }
    file->start=-1;
}

void indexedAllocation(IndexedFile *file,int length){
    int indexBlock=allocateBlock();
    if(indexBlock==-1){
        file->length=-1;
        return;
    }
    file->blocks=(int*)malloc(length*sizeof(int));
    file->length=length;
    for(int i=0;i<length;i++){
        int block=allocateBlock();
        if(block==-1){
            file->length=-1;
            return;
        }
        file->blocks[i]=block;
    }
}

void linkedAllocation(LinkedFile *file,int length){
    file->start=NULL;file->end=NULL;
    for(int i=0;i<length;i++){
        int block=allocateBlock();
        if(block==-1){
            file->start=NULL;
            return;
        }
        LinkedBlock *new=(LinkedBlock*)malloc(sizeof(LinkedBlock));
        new->block_no=block;
        new->next=NULL;
        if(file->end==NULL){
            file->start=new;
            file->end=new;
        }
        else{
            file->end->next=new;
            file->end=new;
        }
    }
}

void printSequentialFile(SequentialFile *file) {
    if (file->start == -1) {
        printf("No space for sequential file allocation\n");
        return;
    }
    printf("Sequential file: Start block = %d, Length = %d\n", file->start, file->length);
}

void printIndexedFile(IndexedFile *file) {
    if (file->length == -1) {
        printf("No space for indexed file allocation\n");
        return;
    }
    printf("Indexed file: Index block = %d, Blocks = ", file->index_block);
    for (int i = 0; i < file->length; i++) {
        printf("%d ", file->blocks[i]);
    }
    printf("\n");
}

void printLinkedFile(LinkedFile *file) {
    if (file->start == NULL) {
        printf("No space for linked file allocation\n");
        return;
    }
    printf("Linked file: ");
    LinkedBlock *current = file->start;
    while (current != NULL) {
        printf("%d -> ", current->block_no);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    initializeFreeBlocks();

    SequentialFile seqFile;
    sequentialAllocation(&seqFile, 5);
    printSequentialFile(&seqFile);

    IndexedFile idxFile;
    indexedAllocation(&idxFile, 5);
    printIndexedFile(&idxFile);

    LinkedFile lnkFile;
    linkedAllocation(&lnkFile, 5);
    printLinkedFile(&lnkFile);

    return 0;
}