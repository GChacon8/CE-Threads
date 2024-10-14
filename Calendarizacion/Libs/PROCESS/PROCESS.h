#ifndef PROCESS_H
#define PROCESS_H

#define MAX_PROCESSES 10

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    Normal, Pesquero, Patrulla
}TipoBarco;

struct Process {
    int pid;
    int arrival_time;
    TipoBarco tipo;
    int priority;
    int burst_time;
    int completion_time;
    float turnaround_time;
    int waiting_time;
    int is_completed;
    int remaining_time;
    int deadline;
};

struct Node {
    struct Process process;
    struct Node* next;
};

void swap(struct Process *xp, struct Process *yp);
void sort_by_arrival_time(struct Node** head);
void sort_by_waiting_time(struct Node** head);
float calculate_average_waiting_time(struct Node* head);
float calculate_average_turnaround_time(struct Process processes[], int n);
struct Process create_process(int pid, TipoBarco tipo, int priority, int burst_time, int deadline);

struct Node* create_node(struct Process process);
void append_node(struct Node** head, struct Process process);
void print_process_list(struct Node* head);
void free_list(struct Node* head);
void enqueue(struct Node** head, struct Process process);
int isEmpty(struct Node* head);
struct Process dequeue(struct Node** head);
#endif
