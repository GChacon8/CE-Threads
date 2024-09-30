#include <stdio.h>
#include <limits.h>

#define MAX_PROCESSES 100

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int is_completed;
};

void sjf_scheduling(struct Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int total_idle_time = 0;

    while (completed != n) {
        int idx = -1;
        int min_burst = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].is_completed == 0) {
                if (processes[i].burst_time < min_burst) {
                    min_burst = processes[i].burst_time;
                    idx = i;
                }
                if (processes[i].burst_time == min_burst) {
                    if (processes[i].arrival_time < processes[idx].arrival_time) {
                        min_burst = processes[i].burst_time;
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            processes[idx].completion_time = current_time + processes[idx].burst_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            
            total_idle_time += current_time - processes[idx].arrival_time;

            current_time = processes[idx].completion_time;
            processes[idx].is_completed = 1;
            completed++;
        }
        else {
            current_time++;
        }
    }
}

float calculate_average_waiting_time(struct Process processes[], int n) {
    float total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
    }
    return total_waiting_time / n;
}

float calculate_average_turnaround_time(struct Process processes[], int n) {
    float total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_turnaround_time += processes[i].turnaround_time;
    }
    return total_turnaround_time / n;
}

void print_results(struct Process processes[], int n) {
    printf("\nProcess\t Arrival Time\t Burst Time\t Completion Time\t Turnaround Time\t Waiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t %d\t\t %d\t\t %d\t\t\t %d\t\t\t %d\n", 
               processes[i].pid, 
               processes[i].arrival_time, 
               processes[i].burst_time, 
               processes[i].completion_time, 
               processes[i].turnaround_time, 
               processes[i].waiting_time);
    }
    
    float avg_waiting_time = calculate_average_waiting_time(processes, n);
    float avg_turnaround_time = calculate_average_turnaround_time(processes, n);
    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    struct Process processes[MAX_PROCESSES];
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].is_completed = 0;
    }

    sjf_scheduling(processes, n);
    print_results(processes, n);

    return 0;
}