#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<string.h>
#include<math.h>

#define quantum 5

typedef struct{
    int pid,arrival,burst,remaining,completion,turnaround,waiting;
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

void push(Queue *q,Process p){
    if(is_full(q)){
        perror("push");
        exit(1);
    }
    q->ready_queue[++q->rear]=p;
    q->size++;
    return;
}

void pop(Queue *q){
    if(is_empty(q)){
        perror("pop");
        exit(1);
    }
    q->front--;
    q->size--;
    return;
}

Process front_p(Queue *q){
    if(is_empty(q)){
        perror("front");
        exit(1);
    }
    return q->ready_queue[q->front];
}

Process rear_p(Queue *q){
    if(is_empty(q)){
        perror("rear");
        exit(1);
    }
    return q->ready_queue[q->rear];
}

void print_gantt(int pid,int time){
    printf("P:%d <%d> | ",pid,time);
}

void print_stat(Process *procs, int n) {
    printf("\n");
    for(int i = 0;  i < n; i++) {
        printf("P:%d -> at: %d, bt: %d, ct: %d, tat: %d, wt: %d, rt: %d\n", procs[i].pid, procs[i].arrival, procs[i].burst, procs[i].completion, procs[i].turnaround, procs[i].waiting, procs[i].remaining);
    }
    return;
}

void round_robin(Process *process,int n){
    Queue *q=get_queue();

    for(int i=0;i<n;i++){
        push(q,process[i]);
    }

    int total_turnaround=0;
    int total_waiting=0;

    int time=0;
    while(!is_empty(q)){
        int time_quantum=quantum;
        Process p=front_p(q);
        pop(q);

        if(p.arrival > time){
            print_gantt(-1,p.arrival);
            time+=p.arrival;
        }

        if(p.remaining > time_quantum){
            print_gantt(p.pid,time+time_quantum);
            p.remaining-=time_quantum;
            time+=time_quantum;
            time_quantum=0;
            push(q,p);
        }
        else{
            print_gantt(p.pid,time+p.remaining);
            time_quantum-=p.remaining;
            time+=p.remaining;
            p.remaining=0;

            p.completion=time;
            p.turnaround=p.completion-p.arrival;
            p.waiting=p.turnaround-p.burst;

            total_turnaround+=p.turnaround;
            total_waiting+=p.waiting;

            process[p.pid]=p;
        }
    }
    print_stat(process,n);
    printf("avg tat: %f", 1.0*total_turnaround/n);
    printf("avg wq: %f", 1.0*total_waiting/n);
    printf("\n");

    return;
}

void FCSF(Process *process,int n){
    int time;
    int total_turnaround=0, total_waiting=0;
    for(int i=0;i<n;i++){
        if(process[i].arrival > time){
            time=process[i].arrival;
            print_gantt(-1,time);
        }
        time+=process[i].burst;
        process[i].remaining=0;
        process[i].completion=time;
        process[i].turnaround = process[i].completion - process[i].arrival;
        process[i].waiting = process[i].turnaround - process[i].burst;
        total_turnaround += process[i].turnaround;
        total_waiting += process[i].waiting;
        print_gantt(i, time);
    }
    print_stat(process, n);   
    printf("avg tat: %f", 1.0*total_turnaround/n);
    printf("avg wq: %f", 1.0*total_waiting/n);
    printf("\n");
    return;
}


Process* get_copy(Process* procs, int n) {
    Process* copy = (Process*)malloc(n*sizeof(Process));
    for(int i = 0; i < n; i++) {
        copy[i] = procs[i];
    }
    return copy;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process* procs = (Process*)malloc(n*sizeof(Process));

    for(int i = 0; i < n; i++) {
        procs[i].pid = i;
        printf("Enter at and bt of process %d: ", procs[i].pid);
        scanf("%d %d", &procs[i].arrival, &procs[i].burst);
        procs[i].remaining = procs[i].burst;
        procs[i].turnaround =0;
        procs[i].waiting = 0;
    }

    printf("\nround_robin\n");
    round_robin(get_copy(procs, n), n);
    printf("\n");

    printf("\nfcfs\n");
    FCSF(get_copy(procs, n), n);
    printf("\n");

    return 0;
}