//  Round Robin
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct Process {
    int pid, at, bt, st, ct, rt, tat, wt, isDone, remain;
}st;
int comp(const void *a, const void * b) {
    st *p1 = (st*)a;
    st *p2 = (st*)b;
    if(p1->at == p2->at)
        return p1->pid > p2->pid;
    return p1->at > p2->at;
}
int max(int a, int b) {
    if(a > b) return a;
    return b;
}
int main() {
    printf("Enter number of processes: ");
    int n;
    scanf("%d", &n);
    st pro[n];
    for(int i=0; i<n; i++) {
        printf("Enter AT, BT: ");
        pro[i].pid = i+1;
        scanf("%d%d",&pro[i].at,&pro[i].bt);
        pro[i].remain = pro[i].bt;
        pro[i].isDone = 0;
    }
    qsort(pro,n,sizeof(st),comp);
    int qn;
    printf("Enter Time Quantum: ");
    scanf("%d", &qn);
    int q[100];
    int front = 0, rear = 0;
    q[front] = 0;
    pro[front].isDone = 1;
    int completed=0, currTime=0;
    printf("\nGantt's Chart: ");
    while(completed != n) {
        int idx = q[front];
        front++;

        if(pro[idx].remain == pro[idx].bt) {
            pro[idx].st = max(pro[idx].at, currTime);
            currTime = pro[idx].st;
        }
        if(pro[idx].remain - qn > 0) {
            currTime += qn;
            pro[idx].remain -= qn;
        }
        else {
            currTime += pro[idx].remain;
            pro[idx].ct = currTime;
            pro[idx].rt = pro[idx].st - pro[idx].at;
            pro[idx].tat = pro[idx].ct - pro[idx].at;
            pro[idx].wt = pro[idx].tat - pro[idx].bt;
            pro[idx].remain = 0;
            completed++;
            printf("%d ", pro[idx].pid);
        }
        for(int i=0; i<n; i++) {
            if(currTime >= pro[i].at && pro[i].isDone == 0) {
                rear++;
                q[rear] = i;
                pro[i].isDone = 1;
            }
        }
        if(pro[idx].remain != 0) {
            rear++;
            q[rear] = idx;
        }
    }
    printf("\nPID\tAT\tBT\tST\tCT\tRT\tTAT\tWT\n");
    for(int i=0; i<n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",pro[i].pid,pro[i].at,pro[i].bt,pro[i].st,pro[i].ct,pro[i].rt,pro[i].tat,pro[i].wt);
    }
    return 0;
}