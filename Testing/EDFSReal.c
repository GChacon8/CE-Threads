#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_PROCESSES 100

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int deadline;
    int remaining_time;
    int completion_time;
    int is_completed;
};

void edf_scheduling(struct Process processes[], int n, int total_time) {
    int current_time = 0;
    int completed = 0;
    int *timeline = (int *)calloc(total_time, sizeof(int));

    while (current_time < total_time && completed < n) {
        int idx = -1;
        int earliest_deadline = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].is_completed == 0 && processes[i].remaining_time > 0) {
                if (processes[i].deadline < earliest_deadline) {
                    earliest_deadline = processes[i].deadline;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            timeline[current_time] = processes[idx].pid;
            processes[idx].remaining_time--;
            
            if (processes[idx].remaining_time == 0) {
                processes[idx].completion_time = current_time + 1;
                processes[idx].is_completed = 1;
                completed++;
            }
        }
        
        current_time++;
    }

    printf("\nTimeline: ");
    for (int i = 0; i < total_time; i++) {
        if (timeline[i] == 0) {
            printf("- ");
        } else {
            printf("P%d ", timeline[i]);
        }
    }
    printf("\n");

    free(timeline);
}

void print_results(struct Process processes[], int n) {
    printf("\nProcess\t Arrival Time\t Burst Time\t Deadline\t Completion Time\t Met Deadline?\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t %d\t\t %d\t\t %d\t\t %d\t\t\t %s\n", 
               processes[i].pid, 
               processes[i].arrival_time, 
               processes[i].burst_time, 
               processes[i].deadline,
               processes[i].completion_time, 
               (processes[i].completion_time <= processes[i].deadline) ? "Yes" : "No");
    }
}

int main() {
    struct Process processes[MAX_PROCESSES];
    int n, total_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter deadline for process %d: ", i + 1);
        scanf("%d", &processes[i].deadline);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].is_completed = 0;
        if (processes[i].deadline > total_time) {
            total_time = processes[i].deadline;
        }
    }

    edf_scheduling(processes, n, total_time);
    print_results(processes, n);

    return 0;
}