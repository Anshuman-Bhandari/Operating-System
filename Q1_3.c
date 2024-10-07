#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main() {
    int pid = fork();
    if(pid < 0) {
        printf("Child 1 failed");
        return 1;
    }
    else if(pid == 0) {
        printf("Child 1 %d, Listting directory File\n", getpid());
        execlp("ls","ls",NULL);
        perror("execlp Failed");
        exit(1);
    }
    else {
        wait(NULL);
        printf("\nParent Process %d from child 1", getpid());
        int pid2 = fork();
        if(pid2 < 0) {
            perror("Child 2 failed ");
            return 1;
        }
        else if(pid2 == 0) {
            printf("Child 2 %d, Start", getpid());
            sleep(5);
            printf("Child 2 end");
            exit(0);
        }
        else {
            printf("Parent Process from child 2 %d", getpid());
            exit(0);
        }
    }
    return 0;
}