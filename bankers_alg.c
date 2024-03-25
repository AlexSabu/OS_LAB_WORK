//implementing bankers algorithm

#include<stdio.h>

int isSafe(int processes[],int available[],int max[][10],int allocation[][10],int need[][10], int n,int m){
    int i,j,work[10],finished[10],safeSeq[10],count=0;
    //initialize
    for(i=0;i<n;i++){
        work[i]=available[i];
        finished[i]=0; //0 = not finished
    }
    while(count<n){
        int found=0; //checking if the process can be executed in the current state
        for(i=0;i<n;i++){
            if(finished[i]==0){ //if true = can be executed
                int canExecute=1;
                for(int j=0;j<m;j++){
                    if(need[i][j] > work[j]){
                        canExecute=0; //cannot be executed by current resources
                        break;
                    }
                }
                if(canExecute){
                    for(j=0;j<m;j++){
                        work[j]+=allocation[i][j];
                    }
                    finished[i]=1;
                    safeSeq[count++]=i;
                    found=1;
                }
            }
        }
        if(!found) return 0;
    }
    printf("safe seq:\n");
    for(i = 0; i < n-1; i++)
        printf("P%d -> ", safeSeq[i]);
    printf("P%d\n", safeSeq[n-1]);
    return 1;
}

int main(){
    int processes[10]; //processes
    int available[10]; //available resources
    int max[10][10]; //maximum resource required by each process
    int allocation[10][10]; //initial resource allocated to each process
    int need[10][10]; //remaining requirement
    int n, /*number of processes*/ m; /*number of resources*/

    printf("input no. processes (n<10):");scanf("%d",&n);
    printf("input no. of resources (m<10):"); scanf("%d",&m);

    printf("input initial allocation\n");
    for(int i=0;i<n;i++){ //initial allocation
        for(int j=0;j<m;j++){
            scanf("%d",&allocation[i][j]);
        }
    }
    printf("input maximum resources req\n");
    for(int i=0;i<n;i++){ //imaximum resources
        for(int j=0;j<m;j++){
            scanf("%d",&max[i][j]);
        }
    }    
    printf("input available resources:\n");
    for(int i=0;i<m;i++){
        scanf("%d",&available[i]);
    }
    //remaining need
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            need[i][j]=max[i][j]-allocation[i][j];
        }
    } 
    if(isSafe(processes,available,max,allocation,need,n,m)){
        printf("Safe is in safe state\n");
    }
    else{
        printf("Safe is not in safe state\n");
    }
}