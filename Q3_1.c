#include<stdio.h>
#include<stdlib.h>
// FCFS
typedef struct Process {
    int pid, at, bt, st, ct, rt, tat, wt;
}st;
int comp(const void *a, const void *b) {
    st *p1 = (st*)a;
    st *p2 = (st*)b;
    return p1->at > p2->at;
}
int main() {
    int n;
    scanf("%d", &n);
    st pro[n];
    for(int i=0; i<n; i++) {
        printf("Enter AT : BT: ");
        scanf("%d%d",&pro[i].at,&pro[i].bt);
        pro[i].pid = i+1;
    }
    qsort(pro,n,sizeof(st),comp);
    for(int i=0; i<n; i++) {
        if(i == 0) {
            pro[i].st = pro[i].at;
            pro[i].ct = pro[i].at+pro[i].bt;
        }
        else {
            pro[i].st = (pro[i-1].ct >= pro[i].at) ? pro[i-1].ct : pro[i].at;
            if(pro[i].at >= pro[i-1].ct) 
                pro[i].ct = pro[i].at + pro[i].bt;
            else 
                pro[i].ct = pro[i-1].ct + pro[i].bt;
        }
        pro[i].rt = pro[i].st - pro[i].at;
        pro[i].tat = pro[i].ct - pro[i].at;
        pro[i].wt = pro[i].tat - pro[i].bt;
    }
    printf("\nPID\tAT\tBT\tST\tCT\tRT\tTAT\tWT\n");
    for(int i=0; i<n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",pro[i].pid,pro[i].at,pro[i].bt,pro[i].st,pro[i].ct,pro[i].rt,pro[i].tat,pro[i].wt);
    }
    return 0;
}