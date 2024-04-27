//fcfs and scan

#include<stdio.h>
#include<stdlib.h>

#define RIGHT 0
#define LEFT 199

void FCFS(int requests[],int initial_head_position,int num_requests){
    int total_head_movement=0;
    for(int i=0;i<num_requests;i++){
        total_head_movement+= abs(requests[i]-initial_head_position);
        initial_head_position=requests[i];
    }
    printf("FCFS....total head movt: %d\n",total_head_movement);
}

void SCAN(int requests[],int initial_head_position,int num_requests){
    int right_min,right_max,left_min,left_max;
    int total_head_movement=0;

    for(int i=0;i<num_requests-1;i++){
        for(int j=0;j<num_requests-i-1;j++){
            if(requests[j] > requests[j+1]){
                int temp = requests[j];
                requests[j]=requests[j+1];
                requests[j+1]=temp;
            }
        }
    }

    right_min=0; left_max=num_requests-1;

    for(int i=0;i<num_requests;i++){
        if(requests[i] > initial_head_position){
            left_min = i;
            break;
        }
    }

    right_max=left_min-1;

    for(int i=left_min;i<=left_max;i++){
        total_head_movement+= abs(requests[i]-initial_head_position);
        initial_head_position=requests[i];   
    }
    total_head_movement+=abs(LEFT-requests[left_max]);
    total_head_movement+=abs(requests[right_max]-LEFT);
    for(int i=right_max;i>=right_min;i--){
        total_head_movement+= abs(requests[i]-initial_head_position);
        initial_head_position=requests[i];   
    }

    printf("SCAN...total head movt: %d",total_head_movement);
}

int main(){
    int initial_head_position;
    int num_requests;
    printf("input num_requests: ");scanf("%d",&num_requests);
    int requests[num_requests];
    printf("initial_head_position: ");scanf("%d",&initial_head_position);
    printf("input disk requests: ");
    for(int i=0;i<num_requests;i++){
        scanf("%d",&requests[i]);
    }

    FCFS(requests,initial_head_position,num_requests);
    SCAN(requests,initial_head_position,num_requests);

}