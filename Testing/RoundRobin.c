#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

struct Queue {
    int items[MAX_PROCESSES];
    int front;
    int rear;
};

void initQueue(struct Queue* q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(struct Queue* q) {
    return q->rear == -1;
}

void enqueue(struct Queue* q, int value) {
    if (q->rear == MAX_PROCESSES - 1)
        printf("Queue is full");
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(struct Queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

void swap(struct Process *xp, struct Process *yp) {
    struct Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort_by_arrival_time(struct Process processes[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (processes[j].arrival_time > processes[j+1].arrival_time)
                swap(&processes[j], &processes[j+1]);
}

void round_robin_scheduling(struct Process processes[], int n, int time_quantum) {
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

float calculate_average_waiting_time(struct Process processes[], int n) {
    float total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
    }
    return total_waiting_time / n;
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
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
}

int main() {
    struct Process processes[MAX_PROCESSES];
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    sort_by_arrival_time(processes, n);
    round_robin_scheduling(processes, n, time_quantum);
    print_results(processes, n);

    return 0;
}