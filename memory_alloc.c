//memory allocation via First Fit, Worst fit,& Best fit

#include<stdio.h>

#define MAX_PROCESSES 10
#define MAX_BLOCKS 10

int First_Fit(int blocks[],int process,int num){
    for(int i=0;i<num;i++){
        if(blocks[i]>=process){
            int allocated_memory_block=blocks[i];
            blocks[i]-=process;
            return allocated_memory_block;
        }
    }
    return -1;
}

int Worst_Fit(int blocks[],int process,int num){
    int worst_fit_index=-1;
    int max_fragmentation=-1;

    for(int i=0;i<num;i++){
        if(blocks[i]>=process && blocks[i]-process > max_fragmentation){
            worst_fit_index=i;
            max_fragmentation=blocks[i]-process;
        }
    }
    if(worst_fit_index!=-1){
        int allocated_memory=blocks[worst_fit_index];
        blocks[worst_fit_index]-=process;
        return allocated_memory;
    }
    else{
        return -1;
    }
    
}

int Best_Fit(int blocks[],int process,int num){
    int best_fit_index=-1;
    int min_fragmentation=__INT_MAX__;

    for(int i=0;i<num;i++){
        if(blocks[i]>=process && blocks[i]-process < min_fragmentation){
            best_fit_index=i;
            min_fragmentation=blocks[i]-process;
        }
    }
    if(best_fit_index!=-1){
        int allocated_memory=blocks[best_fit_index];
        blocks[best_fit_index]-=process;
        return allocated_memory;
    }
    else{
        return -1;
    }    
}

void revert(int blocks[],int original[],int num){
    for(int i=0;i<num;i++){
        blocks[i]=original[i];
    }
}

int main(){
    int memory_blocks[MAX_BLOCKS], num_blocks,temp[MAX_BLOCKS];
    int process[MAX_PROCESSES],num_processes;

    printf("no. of blocks: "); scanf("%d",&num_blocks);
    printf("input block sizes:\n");
    for(int i=0;i<num_blocks;i++){
        scanf("%d",&memory_blocks[i]);
        temp[i]=memory_blocks[i];
    }

    printf("no. of processes: "); scanf("%d",&num_processes);
    printf("input process sizes:\n");
    for(int i=0;i<num_processes;i++){
        scanf("%d",&process[i]);
    }

    printf("First Fit:\n");
    for(int i=0;i<num_processes;i++){
        int first_alloc=First_Fit(memory_blocks,process[i],num_blocks);
        if(first_alloc!=-1)
            printf("process: %d accoated to memory %d\n",i+1,first_alloc);
        else
            printf("No suitable block found for process %d. waiting...",i+1);
    }

    revert(memory_blocks,temp,num_blocks);

    printf("Worst Fit:\n");
    for(int i=0;i<num_processes;i++){
        int worst_alloc=Worst_Fit(memory_blocks,process[i],num_blocks);
        if(worst_alloc!=-1)
            printf("process: %d accoated to memory %d\n",i+1,worst_alloc);
        else
            printf("No suitable block found for process %d. waiting...",i+1);
    }

    revert(memory_blocks,temp,num_blocks);

    printf("best Fit:\n");
    for(int i=0;i<num_processes;i++){
        int best_alloc=Best_Fit(memory_blocks,process[i],num_blocks);
        if(best_alloc!=-1)
            printf("process: %d accoated to memory %d\n",i+1,best_alloc);
        else
            printf("No suitable block found for process %d. waiting...",i+1);
    }

}