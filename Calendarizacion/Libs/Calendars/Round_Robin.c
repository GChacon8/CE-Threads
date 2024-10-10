#include "Round_Robin.h"

void round_robin(struct Process processes[], int n, int time_quantum) {
    struct Queue ready_queue;
    initQueue(&ready_queue);

    int current_time = 0;
    int completed = 0;
    int i = 0;

    while (completed != n) {
        // Check for newly arrived processes
        for (; i < n && processes[i].arrival_time <= current_time; i++) {
            enqueue(&ready_queue, i);
        }

        if (isEmpty(&ready_queue)) {
            current_time++;
            continue;
        }

        int idx = dequeue(&ready_queue);
        if (processes[idx].remaining_time <= time_quantum) {
            current_time += processes[idx].remaining_time;
            processes[idx].remaining_time = 0;
            completed++;

            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
        } else {
            current_time += time_quantum;
            processes[idx].remaining_time -= time_quantum;

            // Check for newly arrived processes again
            for (; i < n && processes[i].arrival_time <= current_time; i++) {
                enqueue(&ready_queue, i);
            }

            enqueue(&ready_queue, idx);
        }
    }
}