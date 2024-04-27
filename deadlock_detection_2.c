#include<stdio.h>

#include<stdio.h>


int isSafe(int available[],int request[][10],int allocation[][10],int n, int m){
    int work[m], finished[n], safeSeq[n], count=0;
    int i,j;

    for(int i=0;i<n;i++){
        finished[i]=1;
        for(int j=0;j<m;j++){
            if(allocation[i][j]!=0){
                finished[i]=0;
                break;
            }
        }
    }

    for(int j=0;j<m;j++){
        work[j]=available[j];
    }

    while(count<n){
        int found=0;
        for(i=0;i<n;i++){
            if(finished[i]==0){
                int canExecute=1;
                for(j=0;j<m;j++){
                    if(request[i][j] > work[j]){
                        canExecute=0;
                        break;
                    }
                }
                if(canExecute){
                    for(int k=0;k<m;k++){
                        work[k]+=allocation[i][k];
                    }
                    finished[i]=1;
                    found=1;
                    safeSeq[count++]=i;
                }
            }
        }
        if(found==0) return 0;
    }
    printf("safe seq: ");
    for(int i=0;i<n;i++){
        printf("%d  ",safeSeq[i]);
    }
    return 1;
}

int main(){
    int available[10];
    int request[10][10];
    int allocation[10][10];
    int n,m;

    printf("input n and m: ");scanf("%d %d",&n,&m);

    printf("input available resources:\n");
    for(int i=0;i<m;i++){
        scanf("%d",&available[i]);
    }

    printf("input allocation matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&allocation[i][j]);
        }
    }
        
    printf("input request matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&request[i][j]);
        }
    }

    if(isSafe(available,request,allocation,n,m)==0){
        printf("system is not safe");
    }
}