#include <stdio.h>
typedef struct {
    int id,burst_time,arrival_time,completion_time;
    int waiting_time,turnaround_time,is_system_process;
} Process;
void calculate_waiting_and_turnaround(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}
void print_scheduling_table(Process processes[], int n) {
    printf("\nScheduling Table:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tType\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%s\n",
               processes[i].id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time,
               processes[i].is_system_process ? "System" : "User");
    }
}
void multi_level_queue_scheduling(Process processes[], int n) {
    int current_time = 0;
    printf("Gantt Chart: ");
    for (int i = 0; i < n; i++) {
        if (processes[i].is_system_process) {
            if (current_time < processes[i].arrival_time) {
                current_time = processes[i].arrival_time;
            }
            current_time += processes[i].burst_time;
            processes[i].completion_time = current_time;
            printf("P%d ", processes[i].id);
        }
    }
    for (int i = 0; i < n; i++) {
        if (!processes[i].is_system_process) {
            if (current_time < processes[i].arrival_time) {
                current_time = processes[i].arrival_time;
            }
            current_time += processes[i].burst_time;
            processes[i].completion_time = current_time;
            printf("P%d ", processes[i].id);
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
        processes[i].id = i;
    }
    printf("Enter the arrival times of the processes: ");
    for (int i = 0; i < n; i++) 
        scanf("%d", &processes[i].arrival_time);
    printf("Enter the process types (1 for system process, 0 for user process): ");
    for (int i = 0; i < n; i++) 
        scanf("%d", &processes[i].is_system_process);
    multi_level_queue_scheduling(processes, n);
    return 0;
}

// 0    3    7   10   11   17   19
// | p0 | p2 | p5 | p1 | p4 | p3 |