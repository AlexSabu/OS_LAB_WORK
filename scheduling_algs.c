// process scheduling algorithms

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct { 
    char pid[10];
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
} process;

void sort(process list[],int n){ //sorting processes based on arrival time
    for(int i=0;i<n;i++){
        for(int j=0;j<n-1;j++){
            if(list[j].arrival_time > list[j+1].arrival_time){
                process temp=list[j];
                list[j]=list[j+1];
                list[j+1]=temp;
            }
        }
    }
}

void FCFS(process list[],int n){ //FCFS Scheduling
    printf("FCFS scheduling: \n");
    printf("process details:\n");
    printf("process_id  Arrival_time  Burst_time\n");
    for(int i=0;i<n;i++){
        printf("%s\t\t%d\t\t%d\n",list[i].pid,list[i].arrival_time,list[i].burst_time);
    }
    printf("Gantt chart:\n");
    for(int i=0;i<n;i++){
        printf("%s\t",list[i].pid);
    }
    printf("\n");
}

void SJF(process list[],int n){ //SJF Scheduling
    int current_time=0;
    int completed=0;
    printf("SJF scheduling: \n");
    printf("process details:\n");
    printf("process_id  Arrival_time  Burst_time\n");
    for(int i=0;i<n;i++){
        printf("%s\t\t%d\t\t%d\n",list[i].pid,list[i].arrival_time,list[i].burst_time);
        list[i].remaining_time=list[i].burst_time;
    }
    printf("Gantt chart:\n");
    while(completed<n){
        int shortest_job=-1;
        int shortest_burst_time=9999;
        for(int i=0;i<n;i++){
            if(list[i].arrival_time<=current_time && list[i].remaining_time>0){
                if(list[i].remaining_time<shortest_burst_time){
                    shortest_burst_time=list[i].remaining_time;
                    shortest_job=i;
                }
            }
        }
        if(shortest_job==-1){
            printf("idle");
            current_time++;
            continue;
        }
        printf("%s\t",list[shortest_job].pid);
        current_time+=list[shortest_job].remaining_time;
        list[shortest_job].remaining_time=0;
        completed++;
    }
    printf("\n");
}

void Priority(process list[],int n){ //highest priority is given priority (pre-emptive)
    int completed=0;
    int current_time=0;
    printf("Priority scheduling: \n");
    printf("process details:\n");
    printf("process_id  Arrival_time  Burst_time  Priority\n");
    for(int i=0;i<n;i++){
        printf("%s\t\t%d\t\t%d\t\t%d\n",list[i].pid,list[i].arrival_time,list[i].burst_time,list[i].priority);
        list[i].remaining_time=list[i].burst_time;
    }
    printf("Gantt chart:\n");
    while(completed<n){
        int highest_priority=-1;
        int job=-1;
        for(int i=0;i<n;i++){
            if(list[i].arrival_time<=current_time && list[i].remaining_time>0){
                if(list[i].priority>highest_priority){
                    highest_priority=list[i].priority;
                    job=i;
                }
            }
        }
        if(job==-1){
            printf("idle\t");
            current_time++;
            continue;
        }
        printf("%s\t",list[job].pid);
        list[job].remaining_time--;
        current_time++;
        if (list[job].remaining_time == 0) {
            completed++;
        }
    }
    printf("\n");
}

int main(){
    int n;
    printf("int n: "); scanf("%d",&n);
    process* list=(process*)malloc(sizeof(process)*n);
    printf("input process details (pid,AT,BT,priority): \n");
    for(int i=0;i<n;i++){
        scanf("%s %d %d %d",list[i].pid,&list[i].arrival_time,&list[i].burst_time,&list[i].priority);
    }
    sort(list,n);
    //FCFS(list,n);
    //SJF(list,n);
    Priority(list,n);
    free(list);
    return 0;
}

