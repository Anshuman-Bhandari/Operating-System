#include <stdio.h>
void calculate_need(int need[][10], int max[][10], int alloc[][10], int p, int r) {
    for (int i = 0; i < p; i++) 
        for (int j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}
int detect_deadlock(int processes[], int avail[], int max[][10], int alloc[][10], int p, int r) {
    int need[10][10];
    calculate_need(need, max, alloc, p, r);
    int finish[10] = {0};
    int work[10];
    for (int i = 0; i < r; i++)
        work[i] = avail[i];
    int count = 0;
    while (count < p) {
        int found = 0;
        for (int i = 0; i < p; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < r; j++)
                    if (need[i][j] > work[j]) break;
                if (j == r)
                {
                    for (int k = 0; k < r; k++)
                        work[k] += alloc[i][k];
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (found == 0)
        {
            printf("Deadlock detected\n");
            return 1;
        }
    }
    printf("No deadlock detected\n");
    return 0;
}
int main() {
	printf("\nName - Anshuman Bhandari\nSection - A2\nRoll No.- 18\n\n");
    int p, r;
    printf("Enter number of processes: ");
    scanf("%d", &p);
    printf("Enter number of resources: ");
    scanf("%d", &r);
    int processes[10], avail[10], max[10][10], alloc[10][10];
    printf("Enter maximum requirement:\n");
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &max[i][j]);
    printf("Enter allocated matrix:\n");
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);
    printf("Enter resource vector:\n");
    for (int i = 0; i < r; i++)
        scanf("%d", &avail[i]);
    detect_deadlock(processes, avail, max, alloc, p, r);
    return 0;
}

