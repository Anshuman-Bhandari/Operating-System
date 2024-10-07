//  SJF - NP
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct Process {
    int pid, at, bt, pr, st, ct, rt, tat, wt, isDone, remain;
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
        printf("Enter AT, BT, Pr : ");
        pro[i].pid = i+1;
        scanf("%d%d%d",&pro[i].at,&pro[i].bt,&pro[i].pr);
        pro[i].remain = pro[i].bt;
        pro[i].isDone = 0;
    }
    qsort(pro,n,sizeof(st),comp);
    int completed=0, currTime=0;
    while(completed != n) {
        int hp = -1, idx = -1;
        for(int i=0; i<n; i++) {
            if(currTime >= pro[i].at && pro[i].isDone == 0) {
                if(pro[i].pr > hp) {
                    hp = pro[i].pr;
                    idx = i;
                }
                if(pro[i].pr == hp && pro[i].at < pro[idx].at) {
                    hp = pro[i].pr;
                    idx = i;
                } 
            }
        }

        if(idx != -1) {
            if(pro[idx].remain == pro[idx].bt) {
                pro[idx].st = currTime;
            }
            pro[idx].remain--;
            currTime++;

            if(pro[idx].remain == 0) {
                pro[idx].ct = currTime;
                pro[idx].rt = pro[idx].st - pro[idx].at;
                pro[idx].tat = pro[idx].ct - pro[idx].at;
                pro[idx].wt = pro[idx].tat - pro[idx].bt;
                pro[idx].isDone = 1;
                completed++;
            }
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