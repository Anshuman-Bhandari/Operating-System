#include <stdio.h>

typedef struct {
    int id, burst_time, arrival_time, completion_time, start_time;
    int waiting_time, turnaround_time, is_system_process;
    int remaining_time;  // Track remaining time for the process
} Process;

void calculate_waiting_and_turnaround(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

void print_scheduling_table(Process processes[], int n) {
    printf("\nScheduling Table:\n");
    printf("PID\tAT\tBT\tST\tCT\tTAT\tWT\tType\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",
               processes[i].id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].start_time,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time,
               processes[i].is_system_process ? "System" : "User");
    }
}

int find_next_process(Process processes[], int n, int current_time) {
    int selected_process = -1;

    // First, prioritize system processes with the earliest arrival time
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && processes[i].is_system_process) {
            if (processes[i].arrival_time < processes[selected_process].arrival_time) {
                selected_process = i;
            }
        }
    }

    // If no system process is found, check user processes
    if (selected_process == -1) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && !processes[i].is_system_process) {
                if (processes[i].arrival_time < processes[selected_process].arrival_time) {
                    selected_process = i;
                }
            }
        }
    }

    return selected_process;
}

void multi_level_queue_scheduling(Process processes[], int n) {
    int current_time = 0, completed = 0;

    printf("Gantt Chart: ");

    while (completed < n) {
        int selected_process = find_next_process(processes, n, current_time);

        // If a process is found, execute it
        if (selected_process != -1) {
            if (processes[selected_process].remaining_time == processes[selected_process].burst_time) {
                processes[selected_process].start_time = current_time;  // Set start time when the process starts executing
            }
            current_time += processes[selected_process].remaining_time;
            processes[selected_process].completion_time = current_time;
            processes[selected_process].remaining_time = 0;
            completed++;
            printf("P%d ", processes[selected_process].id);
        } else {
            // If no process is ready, increment time
            current_time++;
        }
    }

    printf("\n");
    calculate_waiting_and_turnaround(processes, n);

    float total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    printf("Average waiting time: %.2f\n", total_waiting_time / n);
    printf("Average turnaround time: %.2f\n", total_turnaround_time / n);
    print_scheduling_table(processes, n);
}

int main() {
    printf("\nName - Anshuman Bhandari\nSection - A2\nRoll No.- 18\n\n");

    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    printf("Enter the burst times of the processes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].id = i;
    }

    printf("Enter the arrival times of the processes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].arrival_time);
    }

    printf("Enter the process types (1 for system process, 0 for user process): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].is_system_process);
    }

    multi_level_queue_scheduling(processes, n);

    return 0;
}
