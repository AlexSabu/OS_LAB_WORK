
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

#include<stdio.h>

#define MAX_PROCESSES 5

typedef struct{
    int pid;
    int arrival;
    int burst;
    int remaining;
    int turnaround;
    int waiting;
} Process;

void FCFS(Process processes[],int n){
    float total_turnaround=0, total_waiting=0;

    processes[0].waiting=0;

    for(int i=1;i<n;i++){
        processes[i].waiting=processes[i-1].waiting+processes[i-1].burst;
    }
    for(int i=0;i<n;i++){
        processes[i].turnaround=processes[i].waiting+processes[i].burst;
        total_turnaround+=processes[i].turnaround;
        total_waiting+=processes[i].waiting;
    }

    printf("\nFCFS Scheduling:\n");
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival,
               processes[i].burst, processes[i].waiting, processes[i].turnaround);
    }

    printf("Average Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
}

void RoundRobin(Process processes[],int n,int quantum){
    int time=0,remaining_processes=n;
    float total_turnaround=0, total_waiting=0;

    while ((remaining_processes>0)){
        for(int i=0;i<n;i++){
            if(processes[i].remaining>0){
                if(processes[i].remaining>quantum){
                    time+=quantum;
                    processes[i].remaining-=quantum;
                }
                else{
                    time+=processes[i].remaining;
                    processes[i].waiting=time-processes[i].burst;
                    processes[i].remaining=0;
                    remaining_processes--;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        processes[i].turnaround = processes[i].waiting + processes[i].burst;
        total_waiting += processes[i].waiting;
        total_turnaround += processes[i].turnaround;
    }

    printf("\nRound Robin Scheduling (Quantum: %d):\n", quantum);
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival,
               processes[i].burst, processes[i].waiting, processes[i].turnaround);
    }

    printf("Average Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround/ n);
}

void gantt_chart(Process processes[],int n){
    //sorting based on turnaround time
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1;j++){
            if(processes[j].turnaround > processes[j+1].turnaround){
                Process temp=processes[j];
                processes[j]=processes[j+1];
                processes[j+1]=temp;
            }
        }
    }
    printf("Gantt Chart:\n");
    //top bar
    printf(" ");
    for(int i=0;i<n;i++){
        for(int j=0;j<processes[i].burst;j++) printf("--");
        printf(" ");
    }
    printf("\n|");

    //processes
    for(int i=0;i<n;i++){
        for(int j=0;j<processes[i].burst-1;j++) printf(" ");
        printf("P%d",processes[i].pid);
        for(int j=0;j<processes[i].burst-1;j++) printf(" ");
        printf("|");
    }
    printf("\n");

    //bottom bar
    printf(" ");
    for(int i=0;i<n;i++){
        for(int j=0;j<processes[i].burst;j++) printf("--");
        printf(" ");
    }
    printf("\n|");

    //time line
    printf("0");
    for(int i=0;i<n;i++){
        for(int j=0;j<processes[i].burst;j++) printf("  ");
        if(processes[i].turnaround>9) printf("\b");
        printf("%d",processes[i].turnaround);
    }
    printf("\n");
}

int main(){
    int n, quantum;
    printf("enter n:");scanf("%d",&n);

    Process processes[n];
    for(int i=0;i<n;i++){
        processes[i].pid=i+1;
        printf("input p1 arrival and burst time:");scanf("%d %d",&processes[i].arrival,&processes[i].burst);
        processes[i].remaining=processes[i].burst;
    }

    printf("enter time quantum:");scanf("%d",&quantum);    

    FCFS(processes,n);
    gantt_chart(processes,n);

    for(int i=0;i<n;i++){
        processes[i].remaining=processes[i].burst;
    }

    RoundRobin(processes,n,quantum);
    gantt_chart(processes,n);
}