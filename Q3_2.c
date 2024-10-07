//  SJF - NP
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct Process {
    int pid, at, bt, st, ct, rt, tat, wt, isDone;
}st;
int comp(const void *a, const void * b) {
    st *p1 = (st*)a;
    st *p2 = (st*)b;
    if(p1->at == p2->at)
        return p1->pid > p2->pid;
    return p1->at > p2->at;
}
int main() {
    printf("Enter number of processes: ");
    int n;
    scanf("%d", &n);
    st pro[n];
    for(int i=0; i<n; i++) {
        printf("Enter AT, BT : ");
        pro[i].pid = i+1;
        scanf("%d%d",&pro[i].at,&pro[i].bt);
        pro[i].isDone = 0;
    }
    qsort(pro,n,sizeof(st),comp);
    int completed=0, currTime=0;
    while(completed != n) {
        int mn = INT_MAX, idx = -1;
        for(int i=0; i<n; i++) {
            if(currTime >= pro[i].at && pro[i].isDone == 0) {
                if(pro[i].bt < mn) {
                    mn = pro[i].bt;
                    idx = i;
                }
                if(pro[i].bt == mn && pro[i].at < pro[idx].at) {
                    mn = pro[i].bt;
                    idx = i;
                } 
            }
        }

        if(idx != -1) {
            pro[idx].st = currTime;
            pro[idx].ct = currTime + pro[idx].bt;
            pro[idx].rt = pro[idx].st - pro[idx].at;
            pro[idx].tat = pro[idx].ct - pro[idx].at;
            pro[idx].wt = pro[idx].tat - pro[idx].bt;
            pro[idx].isDone = 1;
            completed++;
            currTime = pro[idx].ct;
        }
        else 
            currTime++;
    }
    printf("\nPID\tAT\tBT\tST\tCT\tRT\tTAT\tWT\n");
    for(int i=0; i<n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",pro[i].pid,pro[i].at,pro[i].bt,pro[i].st,pro[i].ct,pro[i].rt,pro[i].tat,pro[i].wt);
    }
    return 0;
}