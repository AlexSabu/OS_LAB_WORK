#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>

#define LEFT 0
#define RIGHT 199

void FCFS(int request[],int initial_head_position,int num_requests){
    int total_head_movt=0;
    for(int i=0;i<num_requests;i++){
        total_head_movt+=abs(request[i]-initial_head_position);
        initial_head_position=request[i];
    }
    printf("total head movement: %d\n",total_head_movt);
}

void SCAN(int request[],int initial_head_position,int num_requests){
    int total_head_movt=0;
    //sort
    for(int i=0;i<num_requests-1;i++){
        for(int j=0;j<num_requests-i-1;j++){
            if(request[j]>request[j+1]){
                int temp=request[j];
                request[j]=request[j+1];
                request[j+1]=temp;
            }
        }
    }
    //finding position of initial_head_position
    int right_min,right_max;
    int left_min,left_max;

    left_min=0;
    right_max=num_requests-1;

    for(int i=0;i<num_requests;i++){
        if(request[i]>initial_head_position){
            right_min=i;
            break;
        }
    }
    left_max=right_min-1;
    //calc total head movt
    //moving to the left
    for(int i=left_max;i>=left_min;i--){
        total_head_movt+=abs(request[i]-initial_head_position);
        initial_head_position=request[i];
    }
    total_head_movt+=abs(LEFT-request[left_min]);
    //moving to the right
    total_head_movt+=abs(request[right_min]-LEFT);
    initial_head_position=request[right_min];
    for(int i=right_min+1;i<=right_max;i++){
        total_head_movt+=abs(request[i]-initial_head_position);
        initial_head_position=request[i];
    }
    printf("SCAN...total head movt: %d\n",total_head_movt);
}

void LOOK(int request[],int initial_head_position,int num_requests){
    int total_head_movt=0;
    //sort
    for(int i=0;i<num_requests-1;i++){
        for(int j=0;j<num_requests-i-1;j++){
            if(request[j]>request[j+1]){
                int temp=request[j];
                request[j]=request[j+1];
                request[j+1]=temp;
            }
        }
    }
    //finding position of initial_head_position
    int right_min,right_max;
    int left_min,left_max;

    left_min=0;
    right_max=num_requests-1;

    for(int i=0;i<num_requests;i++){
        if(request[i]>initial_head_position){
            right_min=i;
            break;
        }
    }
    left_max=right_min-1;
    //calc total head movt
    //moving to the left
    for(int i=left_max;i>=left_min;i--){
        total_head_movt+=abs(request[i]-initial_head_position);
        initial_head_position=request[i];
    }
    //moving to the right
    total_head_movt+=abs(request[right_min]-request[left_min]);
    initial_head_position=request[right_min];
    for(int i=right_min+1;i<=right_max;i++){
        total_head_movt+=abs(request[i]-initial_head_position);
        initial_head_position=request[i];
    }
    printf("LOOK...total head movt: %d\n",total_head_movt);
}

void C_SCAN(int request[],int initial_head_position,int num_requests){
    int total_head_movt=0;
    //sort
    for(int i=0;i<num_requests-1;i++){
        for(int j=0;j<num_requests-i-1;j++){
            if(request[j]>request[j+1]){
                int temp=request[j];
                request[j]=request[j+1];
                request[j+1]=temp;
            }
        }
    }
    //finding position of initial_head_position
    int right_min,right_max;
    int left_min,left_max;

    left_min=0;
    right_max=num_requests-1;

    for(int i=0;i<num_requests;i++){
        if(request[i]>initial_head_position){
            right_min=i;
            break;
        }
    }
    left_max=right_min-1;
    //scanning always to left
    for(int i=left_max;i>=left_min;i--){
        total_head_movt+=abs(request[i]-initial_head_position);
        initial_head_position=request[i];
    }

    total_head_movt+=abs(LEFT-request[left_min]);
    total_head_movt+=RIGHT-LEFT;
    total_head_movt+=abs(request[right_max]-RIGHT);
    initial_head_position=request[right_max];

    for(int i=right_max-1;i>=right_min;i--){
        total_head_movt+=abs(request[i]-initial_head_position);
        initial_head_position=request[i];
    }
    printf("C_SCAN...total head movt: %d\n",total_head_movt);
}

void C_LOOK(int request[],int initial_head_position,int num_requests){
    int total_head_movt=0;
    //sort
    for(int i=0;i<num_requests-1;i++){
        for(int j=0;j<num_requests-i-1;j++){
            if(request[j]>request[j+1]){
                int temp=request[j];
                request[j]=request[j+1];
                request[j+1]=temp;
            }
        }
    }
    //finding position of initial_head_position
    int right_min,right_max;
    int left_min,left_max;

    left_min=0;
    right_max=num_requests-1;

    for(int i=0;i<num_requests;i++){
        if(request[i]>initial_head_position){
            right_min=i;
            break;
        }
    }
    left_max=right_min-1;
    //scanning always to left
    for(int i=left_max;i>=left_min;i--){
        total_head_movt+=abs(request[i]-initial_head_position);
        initial_head_position=request[i];
    }

    total_head_movt+=abs(request[right_max]-request[left_min]);
    initial_head_position=request[right_max];

    for(int i=right_max-1;i>=right_min;i--){
        total_head_movt+=abs(request[i]-initial_head_position);
        initial_head_position=request[i];
    }
    printf("C_LOOK...total head movt: %d\n",total_head_movt);
}

void SSTF(int request[],int initial_head_position,int num_requests){
    int total_head_movt=0;
    int count=0;
    //sort
    for(int i=0;i<num_requests-1;i++){
        for(int j=0;j<num_requests-i-1;j++){
            if(request[j]>request[j+1]){
                int temp=request[j];
                request[j]=request[j+1];
                request[j+1]=temp;
            }
        }
    }
    //finding position of initial_head_position
    int right_index,left_index;

    for(int i=0;i<num_requests;i++){
        if(request[i]>initial_head_position){
            right_index=i;
            break;
        }
    }
    left_index=right_index-1;
    
    while(count<num_requests){
        int left_distance,right_distance;
        left_distance = abs(request[left_index] - initial_head_position);
        right_distance = abs(request[right_index] - initial_head_position);
        if(left_distance>=right_distance){
            total_head_movt+=right_distance;
            initial_head_position=request[right_index];
            if(right_index<num_requests-1){
                right_index++;
            }
        }
        else{
            total_head_movt+=left_distance;
            initial_head_position=request[left_index];
            if(left_index>0){
                left_index--;
            }
        }    
        count++;
    }
    printf("SSTF...total head movt: %d\n",total_head_movt);
}


int main(){
    int initial_head_position=53;
    int num_requests=8;
    //printf("input num_requests: ");scanf("%d",&num_requests);
    int request[8]={98,183,37,122,14,124,65,67};
    //printf("initial_head_position: ");scanf("%d",&initial_head_position);
    //printf("input disk requests: ");
    // for(int i=0;i<num_requests;i++){
    //     scanf("%d",&requests[i]);
    // }

    //FCFS(request,initial_head_position,num_requests);
    //SCAN(request,initial_head_position,num_requests);
    //LOOK(request,initial_head_position,num_requests);
    //C_SCAN(request,initial_head_position,num_requests);
    //C_LOOK(request,initial_head_position,num_requests);
    SSTF(request,initial_head_position,num_requests);
}
