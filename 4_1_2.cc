#include <stdio.h>
#include <limits.h>

typedef struct {
    int id;
    int burst_time;
    int remaining_time;
    int arrival_time;
    int priority;
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
    int is_completed;
} Process;

void calculate_times(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        if (processes[i].response_time == -1) {
            processes[i].response_time = processes[i].start_time - processes[i].arrival_time;
        }
    }
}

void priority_scheduling(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int total_wt = 0, total_tat = 0;
    
    printf("\nGantt Chart:\n");
    
    while (completed < n) {
        int highest_priority = INT_MIN;
        int selected_process = -1;
        
        // Find the highest priority process that has arrived and is not yet completed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].is_completed) {
                if (processes[i].priority > highest_priority || 
                   (processes[i].priority == highest_priority && processes[i].arrival_time < processes[selected_process].arrival_time)) {
                    highest_priority = processes[i].priority;
                    selected_process = i;
                }
            }
        }
        
        if (selected_process != -1) {
            // If this is the first time the process is running, record the start time
            if (processes[selected_process].remaining_time == processes[selected_process].burst_time) {
                processes[selected_process].start_time = current_time;
            }
            
            // Execute the selected process for 1 time unit
            printf("| P%d (%d) ", processes[selected_process].id, current_time);
            current_time++;
            processes[selected_process].remaining_time--;
            
            // If the process is completed, mark it and record completion time
            if (processes[selected_process].remaining_time == 0) {
                processes[selected_process].completion_time = current_time;
                processes[selected_process].is_completed = 1;
                completed++;
            }
            
        } else {
            // No process is ready, so idle time
            printf("| Idle (%d) ", current_time);
            current_time++;
        }
    }
    printf("| %d |\n", current_time);
    
    // Calculate waiting and turnaround times
    calculate_times(processes, n);
    
    // Print the table
    printf("\n| PID | Start Time | Completion Time | Response Time | TAT | WT |\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("| %3d |     %3d    |       %3d       |      %3d      | %3d | %3d |\n", 
               processes[i].id, processes[i].start_time, processes[i].completion_time, 
               processes[i].response_time, processes[i].turnaround_time, processes[i].waiting_time);
        total_wt += processes[i].waiting_time;
        total_tat += processes[i].turnaround_time;
    }
    
    // Print average TAT and WT
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
}

int main() {
    printf("\nName - Anshuman Bhandari\nSection - A2\nRoll No.- 18\n\n");
    
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    Process processes[n];
    
    // Input burst time, arrival time, and priority
    printf("Enter the burst times of the processes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].burst_time);
        processes[i].id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].is_completed = 0;  // Mark all processes as not completed initially
        processes[i].response_time = -1; // Initialize response time
    }
    
    printf("Enter the arrival times of the processes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].arrival_time);
    }
    
    printf("Enter the priorities of the processes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].priority);
    }
    
    priority_scheduling(processes, n);
    
    return 0;
}
