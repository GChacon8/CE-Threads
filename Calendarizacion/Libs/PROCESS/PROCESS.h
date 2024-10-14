#ifndef PROCESS_H
#define PROCESS_H

#define MAX_PROCESSES 10

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
    int turnaround_time;
    int waiting_time;
    int is_completed;
    int remaining_time;
    int deadline;
};

void swap(struct Process *xp, struct Process *yp);
void sort_by_arrival_time(struct Process processes[], int n);
void sort_by_waiting_time(struct Process processes[], int n);
float calculate_average_waiting_time(struct Process processes[], int n);
float calculate_average_turnaround_time(struct Process processes[], int n);
void print_results(struct Process processes[], int n);
struct Process create_process(int pid, TipoBarco tipo, int priority, int burst_time, int deadline);
//void barco_info(struct Process processes[], int n);
#endif
