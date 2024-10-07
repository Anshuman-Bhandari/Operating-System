#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    printf("\nName - Anshuman Bhandari\nSection - A2\nRoll No. - 18\n\n");

    // First child process to list files
    int pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed for first child");
        return 1;
    } 
    else if (pid1 == 0) {
        // Child process
        printf("Child Process 1 (PID: %d): Listing files in the current directory...\n", getpid());
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp failed"); // Error handling if execlp fails
        exit(1); // Exit if execlp fails
    } 
    else {
        // Parent process waits for the first child to complete
        wait(NULL);
        printf("Parent Process (PID: %d): First child has completed.\n", getpid());

        // Second child process
        int pid2 = fork();
        if (pid2 < 0) {
            perror("Fork failed for second child");
            return 1;
        } 
        else if (pid2 == 0) {
            // Second child process
            printf("Child Process 2 (PID: %d): I am the second child. Simulating work...\n", getpid());
            sleep(5); // Simulate some work for 5 seconds
            printf("Child Process 2 (PID: %d): Work done.\n", getpid());
            exit(0); // Exit normally
        } 
        else {
            // Parent process exits before the second child completes
            printf("Parent Process (PID: %d): Exiting now.\n", getpid());
            exit(0); // Parent exits before the second child
        }
    }

    return 0; // This line will never be reached
}