#include <stdio.h>
typedef struct {
    int id;
    int burst_time;
    int arrival_time;
    int priority;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;
void calculate_waiting_and_turnaround(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}
void priority_scheduling(Process processes[], int n) {
    int completed = 0, current_time = 0;
    while (completed < n) {
        int highest_priority = -1;
        int selected_process = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].completion_time == 0 && processes[i].arrival_time <= current_time) {
                if (processes[i].priority > highest_priority) {
                    highest_priority = processes[i].priority;
                    selected_process = i;
                }
            }
        }
        if (selected_process != -1) {
            current_time += processes[selected_process].burst_time;
            processes[selected_process].completion_time = current_time;
            completed++;
        }
        else 
            current_time++;
    }
    calculate_waiting_and_turnaround(processes, n);
    printf("Gantt Chart: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", processes[i].id);
    printf("\n");
    float total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    printf("Average waiting time: %.2f\n", total_waiting_time / n);
    printf("Average turnaround time: %.2f\n", total_turnaround_time / n);
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
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].arrival_time);
    }
    printf("Enter the priorities of the processes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].priority);
        processes[i].completion_time = 0; 
    }
    priority_scheduling(processes, n);
    return 0;
}

