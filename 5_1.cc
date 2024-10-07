#include<stdio.h>
int main() {
    int n,m;
    printf("Number of process and resources: ");
    scanf("%d%d", &n, &m);
    int allot[n][m], max[n][m], need[n][m], f[n], ans[n], avail[m];
    printf("Make Allocate resources Matrix: \n");
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            scanf("%d", &allot[i][j]);

    printf("Make Max resources Matrix: \n");
    for(int i=0; i<n; i++) {
        f[i] = 0;
        for(int j=0; j<m; j++)
            scanf("%d", &max[i][j]);
    }

    printf("Available resources : ");
    for(int j=0; j<m; j++) 
        scanf("%d", &avail[j]);

    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            need[i][j] = max[i][j] - allot[i][j];

    int idx = 0;
    
    for(int k=0; k<n; k++) {
        for(int i=0; i<n; i++) {
            if(f[i] == 0) {
                int fg = 1;
                for(int j=0; j<m; j++) {
                    if(need[i][j] > avail[j]) {
                        fg = 0;
                        break;
                    }
                }
                if(fg) {
                    ans[idx++] = i;
                    for(int j=0; j<m; j++)
                        avail[j] += allot[i][j];
                    f[i] = 1;
                }
            }
        }
    }

    int safe = 1;
    for(int i=0; i<n; i++)
        if(f[i] == 0) {
            safe = 0;
            printf("Not a safe !!");
            break;
        }
    
    if(safe) {
        for(int i=0; i<n; i++)
            printf("%d -> ", ans[i]);
    }

    return 0;
}