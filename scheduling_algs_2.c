
//         {1,0,8,0,0,0},
//         {2,1,4,0,0,0},
//         {3,2,9,0,0,0},
//         {4,3,5,0,0,0},
//         {5,4,2,0,0,0}


// #include <stdio.h>

// #define MAX_PROCESSES 10

// // Process structure
// typedef struct {
//     int pid;
//     int arrival_time;
//     int burst_time;
//     int remaining_time;
//     int turnaround_time;
//     int waiting_time;
// } Process;

// // Function prototypes
// void fcfs(Process processes[], int n);
// void round_robin(Process processes[], int n, int quantum);
// void display_gantt_chart(Process processes[], int n);

// int main() {
//     int n, i, quantum;

//     printf("Enter the number of processes: ");
//     scanf("%d", &n);

//     Process processes[MAX_PROCESSES];

//     // Input process details
//     for (i = 0; i < n; i++) {
//         processes[i].pid = i + 1;
//         printf("Enter arrival time and burst time for process %d: ", i + 1);
//         scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
//         processes[i].remaining_time = processes[i].burst_time;
//     }

//     // Set time quantum for Round Robin
//     printf("Enter the time quantum for Round Robin: ");
//     scanf("%d", &quantum);

//     // Run FCFS algorithm
//     fcfs(processes, n);
//     display_gantt_chart(processes, n);

//     // Reset remaining time for Round Robin
//     for (i = 0; i < n; i++) {
//         processes[i].remaining_time = processes[i].burst_time;
//     }

//     // Run Round Robin algorithm
//     round_robin(processes, n, quantum);
//     display_gantt_chart(processes, n);

//     return 0;
// }

// // Function to implement FCFS scheduling algorithm
// void fcfs(Process processes[], int n) {
//     int i;
//     float total_turnaround_time = 0, total_waiting_time = 0;

//     processes[0].waiting_time = 0;

//     for (i = 1; i < n; i++) {
//         processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
//     }

//     for (i = 0; i < n; i++) {
//         processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
//         total_waiting_time += processes[i].waiting_time;
//         total_turnaround_time += processes[i].turnaround_time;
//     }

//     printf("\nFCFS Scheduling:\n");
//     printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

//     for (i = 0; i < n; i++) {
//         printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time,
//                processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
//     }

//     printf("Average Waiting Time: %.2f\n", total_waiting_time / n);
//     printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
// }

// // Function to implement Round Robin scheduling algorithm
// void round_robin(Process processes[], int n, int quantum) {
//     int i, time = 0, remaining_processes = n;
//     float total_turnaround_time = 0, total_waiting_time = 0;

//     while (remaining_processes > 0) {
//         for (i = 0; i < n; i++) {
//             if (processes[i].remaining_time > 0) {
//                 if (processes[i].remaining_time > quantum) {
//                     time += quantum;
//                     processes[i].remaining_time -= quantum;
//                 } else {
//                     time += processes[i].remaining_time;
//                     processes[i].waiting_time = time - processes[i].burst_time;
//                     processes[i].remaining_time = 0;
//                     remaining_processes--;
//                 }
//             }
//         }
//     }

//     for (i = 0; i < n; i++) {
//         processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
//         total_waiting_time += processes[i].waiting_time;
//         total_turnaround_time += processes[i].turnaround_time;
//     }

//     printf("\nRound Robin Scheduling (Quantum: %d):\n", quantum);
//     printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

//     for (i = 0; i < n; i++) {
//         printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time,
//                processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
//     }

//     printf("Average Waiting Time: %.2f\n", total_waiting_time / n);
//     printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
// }

// // Function to display Gantt chart
// // Function to display Gantt chart
// void display_gantt_chart(Process processes[], int n) {
//     int i, j;

//     // Sort processes based on turnaround time
//     for (i = 0; i < n - 1; i++) {
//         for (j = 0; j < n - i - 1; j++) {
//             if (processes[j].turnaround_time > processes[j + 1].turnaround_time) {
//                 Process temp = processes[j];
//                 processes[j] = processes[j + 1];
//                 processes[j + 1] = temp;
//             }
//         }
//     }

//     printf("\nGantt Chart:\n");

//     // Print the top bar
//     printf(" ");
//     for (i = 0; i < n; i++) {
//         for (j = 0; j < processes[i].burst_time; j++) printf("--");
//         printf(" ");
//     }
//     printf("\n|");

//     // Print the process number
//     for (i = 0; i < n; i++) {
//         for (j = 0; j < processes[i].burst_time - 1; j++) printf(" ");
//         printf("P%d", processes[i].pid);
//         for (j = 0; j < processes[i].burst_time - 1; j++) printf(" ");
//         printf("|");
//     }
//     printf("\n ");

//     // Print the bottom bar
//     for (i = 0; i < n; i++) {
//         for (j = 0; j < processes[i].burst_time; j++) printf("--");
//         printf(" ");
//     }
//     printf("\n");

//     // Print the time line
//     printf("0");
//     for (i = 0; i < n; i++) {
//         for (j = 0; j < processes[i].burst_time; j++) printf("  ");
//         if (processes[i].turnaround_time > 9) printf("\b"); // Adjusting backspace
//         printf("%d", processes[i].turnaround_time);
//     }
//     printf("\n");
// }

// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>

// #define MAX_PROCESSES 5

// typedef struct{
//     int pid;
//     int arrival;
//     int burst;
//     int remaining;
//     int turnaround;
//     int waiting;
// } Process;

// void FCFS(Process processes[],int n){
//     float total_turnaround=0, total_waiting=0;

//     processes[0].waiting=0;

//     for(int i=1;i<n;i++){
//         processes[i].waiting=processes[i-1].waiting+processes[i-1].burst;
//     }
//     for(int i=0;i<n;i++){
//         processes[i].turnaround=processes[i].waiting+processes[i].burst;
//         total_turnaround+=processes[i].turnaround;
//         total_waiting+=processes[i].waiting;
//     }

//     printf("\nFCFS Scheduling:\n");
//     printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

//     for (int i = 0; i < n; i++) {
//         printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival,
//                processes[i].burst, processes[i].waiting, processes[i].turnaround);
//     }

//     printf("Average Waiting Time: %.2f\n", total_waiting / n);
//     printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
// }

// void RoundRobin(Process processes[],int n,int quantum){
//     int time=0,remaining_processes=n;
//     float total_turnaround=0, total_waiting=0;

//     while ((remaining_processes>0)){
//         for(int i=0;i<n;i++){
//             if(processes[i].remaining>0){
//                 if(processes[i].remaining>quantum){
//                     time+=quantum;
//                     processes[i].remaining-=quantum;
//                 }
//                 else{
//                     time+=processes[i].remaining;
//                     processes[i].waiting=time-processes[i].burst;
//                     processes[i].remaining=0;
//                     remaining_processes--;
//                 }
//             }
//         }
//     }
//     for (int i = 0; i < n; i++) {
//         processes[i].turnaround = processes[i].waiting + processes[i].burst;
//         total_waiting += processes[i].waiting;
//         total_turnaround += processes[i].turnaround;
//     }

//     printf("\nRound Robin Scheduling (Quantum: %d):\n", quantum);
//     printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

// void RoundRobin(Process processes[], int n, int quantum) {
//     int time = 0, remaining_processes = n;
//     float total_turnaround = 0, total_waiting = 0;
//     int *completed = (int *)malloc(n * sizeof(int));
//     memset(completed, 0, n * sizeof(int));

//     while (remaining_processes > 0) {
//         for (int i = 0; i < n; i++) {
//             if (completed[i] == 0 && processes[i].remaining > 0) {
//                 if (processes[i].remaining > quantum) {
//                     time += quantum;
//                     processes[i].remaining -= quantum;
//                 } else {
//                     time += processes[i].remaining;
//                     processes[i].waiting += time - processes[i].burst;
//                     processes[i].turnaround = processes[i].waiting + processes[i].burst;
//                     total_waiting += processes[i].waiting;
//                     total_turnaround += processes[i].turnaround;
//                     processes[i].remaining = 0;
//                     completed[i] = 1;
//                     remaining_processes--;
//                 }
//             }
//         }
//     }

//     printf("\nRound Robin Scheduling (Quantum: %d):\n", quantum);
//     printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define CAP 1000
#define TQ 5

typedef struct proc_t proc_t;
typedef struct queue queue;

//process
struct proc_t {
    int pid, at, bt, ct, tat, wt, rt, p; 
};

//queue
struct queue {
    int f, r, size;
    proc_t a[CAP];
};

queue* get_queue() {
    queue* q = (queue*)malloc(sizeof(queue));
    q->f = 0;
    q->r = -1;
    q->size = 0;
    return q;
}

bool is_empty(queue* q) {
    return q->size == 0;
}

bool is_full(queue* q) {
    return q->size == CAP;
}

void push(queue* q, proc_t x) {
    if(is_full(q)) {
        perror("push");
        exit(1);
    }
    q->a[++q->r] = x;
    q->size++;
    return;
}

void pop(queue* q) {
    if(is_empty(q)) {
        perror("pop");
        exit(1);
    }
    q->f++;
    q->size--;
    return;
}

proc_t front(queue* q) {
    if(is_empty(q)) {
        perror("front");
        exit(1);
    }
    return q->a[q->f];
}

proc_t rear(queue* q) {
    if(is_empty(q)) {
        perror("rear");
        exit(1);
    }
    return q->a[q->r];
}

void print_gantt(int pid, int end) {
    printf("P:%d <%d>", pid, end);
}

void print_stat(proc_t* procs, int n) {
    printf("\n");
    for(int i = 0;  i < n; i++) {
        printf("P:%d -> at: %d, bt: %d, ct: %d, tat: %d, wt: %d, rt: %d\n", procs[i].pid, procs[i].at, procs[i].bt, procs[i].ct, procs[i].tat, procs[i].wt, procs[i].rt);
    }
    return;
}

void run_rr(proc_t* procs, int n, int tq) {
    queue* q = get_queue();

    for(int i = 0; i < n; i++) {
        push(q, procs[i]);
    }

    int t_tat = 0;
    int t_wt = 0;

    int elap = 0;
    while(!is_empty(q)) {
        int t_lt = tq;
        proc_t proc = front(q);      
        pop(q);

        if(proc.at > elap) {
            print_gantt(-1, proc.at);
            elap = proc.at; 
        }

        if(proc.rt > t_lt) {
            print_gantt(proc.pid, elap + t_lt);

            proc.rt -= t_lt;
            elap += t_lt;
            t_lt = 0;

            push(q, proc);
        }
        else {
            print_gantt(proc.pid, elap + proc.rt);

            t_lt -= proc.rt;
            elap += proc.rt;
            proc.rt = 0;

            proc.ct = elap;
            proc.tat = proc.ct - proc.at;
            proc.wt = proc.tat - proc.bt;

            t_tat += proc.tat;
            t_wt += proc.wt;

            procs[proc.pid] = proc;
        }
    }
    print_stat(procs, n);   
    printf("avg tat: %f", 1.0*t_tat/n);
    printf("avg wq: %f", 1.0*t_wt/n);
    printf("\n");

    return;
}

// void run_sjf(proc_t* procs, int n) {
//     int elap = 0;
//     int fin = 0;
//     int t_tat = 0, t_wt = 0;
//     while(fin < n) {
//         int min_bt = INT_MAX;
//         int min_i = -1;

//         for(int i = 0; i < n; i++) {
//             if(procs[i].rt > 0 && procs[i].bt < min_bt && procs[i].at <= elap) {
//                 min_bt = procs[i].bt;
//                 min_i = i;
//             }
//         }

//         if(min_i == -1) {
//             for(int i = 0; i < n; i++) {
//                 if(procs[i].rt > 0 && procs[i].at > elap) {
//                     elap = procs[i].at;
//                     print_gantt(-1, elap);
//                     break;
//                 }
//             }
//         }
//         else {
//             elap += procs[min_i].bt;
//             procs[min_i].rt = 0;
//             procs[min_i].ct = elap;
//             procs[min_i].tat = procs[min_i].ct - procs[min_i].at;
//             procs[min_i].wt = procs[min_i].tat - procs[min_i].bt;
//             t_tat += procs[min_i].tat;
//             t_wt += procs[min_i].wt;
//             print_gantt(min_i, elap);
//             fin++;
//         }
//     }
//     print_stat(procs, n);   
//     printf("avg tat: %f", 1.0*t_tat/n);
//     printf("avg wq: %f", 1.0*t_wt/n);
//     printf("\n");
// }

void run_fcfs(proc_t* procs, int n) {
    int elap = 0;
    int t_tat = 0, t_wt = 0;
    for(int i = 0; i < n; i++) {
        if(procs[i].at > elap) {
            elap = procs[i].at;
            print_gantt(-1, elap);
        }

        elap += procs[i].bt;
        procs[i].rt = 0;
        procs[i].ct = elap;
        procs[i].tat = procs[i].ct - procs[i].at;
        procs[i].wt = procs[i].tat - procs[i].bt;
        t_tat += procs[i].tat;
        t_wt += procs[i].wt;
        print_gantt(i, elap);
    }
    print_stat(procs, n);   
    printf("avg tat: %f", 1.0*t_tat/n);
    printf("avg wq: %f", 1.0*t_wt/n);
    printf("\n");
    return;
}

// void run_priority(proc_t* procs, int n) {
//     int elap = 0;
//     int fin = 0;

//     int t_tat = 0, t_wt = 0;
//     while(fin < n) {
//         int minv = INT_MAX;
//         int minv_j = -1;
//         for(int j = 0; j < n; j++) {
//             if(procs[j].rt > 0 && procs[j].p < minv && procs[j].at <= elap) {
//                 minv = procs[j].p;
//                 minv_j = j;
//             }
//         }

//         if(minv_j == -1) {
//             int min_at = INT_MAX;
//             for(int j = 0; j < n; j++) {
//                 if(procs[j].rt > 0 && procs[j].at < min_at) {
//                     min_at = procs[j].at;
//                 }
//             }
//             elap = min_at;
//             print_gantt(-1, elap);
//         }
//         else {
//             elap += procs[minv_j].bt;
//             procs[minv_j].rt = 0;
//             procs[minv_j].ct = elap;
//             procs[minv_j].tat = procs[minv_j].ct - procs[minv_j].at;
//             procs[minv_j].wt = procs[minv_j].tat - procs[minv_j].bt;
//             t_tat += procs[minv_j].tat;
//             t_wt += procs[minv_j].wt;
//             print_gantt(minv_j, elap);
//             fin++;
//         }
//     }

//     print_stat(procs, n);   
//     printf("avg tat: %f", 1.0*t_tat/n);
//     printf("avg wq: %f", 1.0*t_wt/n);
//     printf("\n");
//     return;
// }

proc_t* set_procs(int n) {
    proc_t* procs = (proc_t*)malloc(n*sizeof(proc_t));

    for(int i = 0; i < n; i++) {
        procs[i].pid = i;
        printf("Enter at and bt and p of process %d: ", procs[i].pid);
        scanf("%d%d%d", &procs[i].at, &procs[i].bt, &procs[i].p);
        procs[i].rt = procs[i].bt;
        procs[i].tat = procs[i].wt = 0;
    }
    return procs;
}

proc_t* get_copy(proc_t* procs, int n) {
    proc_t* copy = (proc_t*)malloc(n*sizeof(proc_t));
    for(int i = 0; i < n; i++) {
        copy[i] = procs[i];
    }
    return copy;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    proc_t* procs = set_procs(n);

    printf("\nround_robin\n");
    run_rr(get_copy(procs, n), n, TQ);
    printf("\n");

    // printf("\nsjf\n");
    // run_sjf(get_copy(procs, n), n);
    // printf("\n");

    printf("\nfcfs\n");
    run_fcfs(get_copy(procs, n), n);
    printf("\n");

    // printf("\npriority\n");
    // run_priority(get_copy(procs, n), n);
    // printf("\n");

    return 0;
}