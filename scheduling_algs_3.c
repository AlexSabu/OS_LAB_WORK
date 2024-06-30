#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<string.h>
#include<limits.h>

#define quantum 4

typedef struct{
    int pid,arrival,burst,remaining,completion,turnaround,waiting,priority;
} Process;

typedef struct{
    int front,rear,size;
    Process ready_queue[100];
} Queue;

Queue* get_queue(){
    Queue *q=(Queue*)malloc(sizeof(Queue));
    q->front=0;q->rear=-1;q->size=0;
    return q;
}

bool is_empty(Queue *q){
    return q->size==0;
}

bool is_full(Queue *q){
    return q->size==100;
}

void push(Queue *q, Process p){
    if(is_full(q)){
        perror("push");
        exit(1);
    }
    q->ready_queue[++q->rear]=p;
    q->size++;
    return;
}

Process pop(Queue *q){
    if(is_empty(q)){
        perror("pop");
        exit(1);
    }
    Process p=q->ready_queue[q->front];
    q->front++;
    q->size--;
    return p;
}

void print_gantt(int pid,int time){
    printf(" P%d : <%d> |",pid,time);
}

void print_stats(Process *process,int n){
    for(int i=0;i<n;i++){
        printf("\nP:%d -> at: %d, bt: %d, ct: %d, tat: %d, wt: %d, rt: %d", process[i].pid, process[i].arrival, process[i].burst, process[i].completion, process[i].turnaround, process[i].waiting, process[i].remaining);
    }
    printf("\n");
}


void Round_Robin(Process *process, int n) {
    Queue *q = get_queue();
    int time = 0;
    int total_turnaround = 0, total_waiting = 0;

    // Load processes into the queue in order of their arrival time
    int i = 0;
    while (i < n || !is_empty(q)) {
        while (i < n && process[i].arrival <= time) {
            push(q, process[i]);
            i++;
        }

        if (is_empty(q)) {
            time++;
            continue;
        }

        Process p = pop(q);
        int exec_time = (p.remaining > quantum) ? quantum : p.remaining;
        time += exec_time;
        p.remaining -= exec_time;
        print_gantt(p.pid, time);

        if (p.remaining > 0) {
            push(q, p);
        } else {
            p.completion = time;
            p.turnaround = p.completion - p.arrival;
            p.waiting = p.turnaround - p.burst;
            total_turnaround += p.turnaround;
            total_waiting += p.waiting;
            process[p.pid] = p;
        }
    }

    print_stats(process, n);
    printf("avg tat: %f\n", 1.0 * total_turnaround / n);
    printf("avg wt: %f\n", 1.0 * total_waiting / n);
}

void SJF(Process *process,int n){
    int time=0;
    int total_turnaround=0,total_waiting=0;
    int count=0;

    while(count<n){
        int min_burst=INT_MAX;
        int min_index=-1;

        for(int i=0;i<n;i++){
            if(process[i].remaining>0 && process[i].arrival<=time && process[i].burst<min_burst){
                min_burst=process[i].burst;
                min_index=i;
            }
        }

        if(min_index==-1){
            int min_at=INT_MAX;
            for(int i=0;i<n;i++){
                if(process[i].remaining>0 && process[i].arrival<min_at){
                    min_at=process[i].arrival;
                }
            }
            time=min_at;
            print_gantt(-1,time);
        }
        else{
            time+=process[min_index].burst;
            process[min_index].remaining=0;
            process[min_index].completion=time;
            process[min_index].turnaround=process[min_index].completion-process[min_index].arrival;
            process[min_index].waiting=process[min_index].turnaround-process[min_index].burst;
            total_turnaround+=process[min_index].turnaround;
            total_waiting+=process[min_index].waiting;

            print_gantt(process[min_index].pid,time);
            count++;
        }
    }
    print_stats(process,n);
    printf("avg tat: %f", 1.0*total_turnaround/n);
    printf("avg wq: %f", 1.0*total_waiting/n);
    printf("\n");
    return;
}

void NonPreemtive_Priority(Process *process,int n){ //lower number = higher priority
    int time=0;
    int total_turnaround=0,total_waiting=0;
    int count=0;

    while(count<n){
        int min_priority_no=INT_MAX;
        int min_index=-1;

        for(int i=0;i<n;i++){
            if(process[i].remaining>0 && process[i].arrival<=time && process[i].priority<min_priority_no){
                min_priority_no=process[i].priority;
                min_index=i;
            }
        }

        if(min_index==-1){
            int min_at=INT_MAX;
            for(int i=0;i<n;i++){
                if(process[i].remaining>0 && process[i].arrival<min_at){
                    min_at=process[i].arrival;
                }
            }
            time=min_at;
            print_gantt(-1,time);
        }
        else{
            time+=process[min_index].burst;
            process[min_index].remaining=0;
            process[min_index].completion=time;
            process[min_index].turnaround=process[min_index].completion-process[min_index].arrival;
            process[min_index].waiting=process[min_index].turnaround-process[min_index].burst;
            total_turnaround+=process[min_index].turnaround;
            total_waiting+=process[min_index].waiting;

            print_gantt(process[min_index].pid,time);
            count++;
        }
    }
    print_stats(process,n);
    printf("avg tat: %f", 1.0*total_turnaround/n);
    printf("avg wq: %f", 1.0*total_waiting/n);
    printf("\n");
    return;
}

void FCFS(Process *process,int n){
    int time=0;
    int total_turnaround=0,total_waiting=0;
    for(int i=0;i<n;i++){
        if(process[i].arrival > time){
            time=process[i].arrival;
            print_gantt(-1,time);
        }
        time+=process[i].burst;
        process[i].remaining=0;
        process[i].completion=time;
        process[i].turnaround=process[i].completion-process[i].arrival;
        process[i].waiting=process[i].turnaround-process[i].burst;
        total_turnaround+=process[i].turnaround;
        total_waiting+=process[i].waiting;
        print_gantt(i,time);
    }
    print_stats(process,n);
    printf("avg tat: %f", 1.0*total_turnaround/n);
    printf("avg wq: %f", 1.0*total_waiting/n);
    printf("\n");
    return;
}

Process* get_copy(Process *process,int n){
    Process *copy=(Process*)malloc(n*sizeof(Process));
    for(int i=0;i<n;i++){
        copy[i]=process[i];
    }
    return copy;
}

int main(){
    int n;
    printf("imput n: ");scanf("%d",&n);
    Process *process=(Process*)malloc(n*sizeof(Process));

    for(int i=0;i<n;i++){
        process[i].pid=i;
        printf("input at, bt and priority:");
        scanf("%d %d %d",&process[i].arrival,&process[i].burst,&process[i].priority);
        process[i].remaining=process[i].burst;
        process[i].completion=process[i].turnaround=process[i].waiting=0;
    }
    //sort based on arrival time
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(process[j].arrival > process[j+1].arrival){
                Process temp=process[j];
                process[j]=process[j+1];
                process[j+1]=temp;
            }
        }
    }

    // printf("\nfcfs\n");
    // FCFS(get_copy(process, n), n);
    // printf("\n");

    // printf("\nround_robin\n");
    // Round_Robin(get_copy(process, n), n);
    // printf("\n");

    // printf("\nSJF\n");
    // SJF(get_copy(process, n), n);
    // printf("\n");

    printf("\nnon pre-emptive priority:\n");
    NonPreemtive_Priority(get_copy(process, n), n);
    printf("\n");

    return 0;
}

