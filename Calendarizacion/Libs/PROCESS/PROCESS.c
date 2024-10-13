#include "PROCESS.h"
#include <stdio.h>

/**
 * Esta funcion se encarga de cambiar un proceso por otro en la lista.
 * @param xp objeto de tipo proceso
 * @param yp objeto de tipo proceso
 */
void swap(struct Process *xp, struct Process *yp) {
    struct Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/**
 * Esta funcion ordena una lista de procesos
 * @param processes lista de objetos de tipo proceso
 * @param n length
 */
void sort_by_arrival_time(struct Process processes[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (processes[j].arrival_time > processes[j+1].arrival_time)
                swap(&processes[j], &processes[j+1]);
}

/**
 * Esta funcion calcula el tiempo promedio de espera de los procesos
 * @param processes lista de objetos de tipo proceso
 * @param n lenght
 * @return Tiempo promedio de espera
 */
float calculate_average_waiting_time(struct Process processes[], int n) {
    float total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
    }
    return total_waiting_time / n;
}

/**
 * Esta funcion calcula el tiempo promedio en cola de los procesos
 * @param processes lista de objetos de tipo proceso
 * @param n length
 * @return Tiempo de cola promedio de los procesos
 */
float calculate_average_turnaround_time(struct Process processes[], int n) {
    float total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_turnaround_time += processes[i].turnaround_time;
    }
    return total_turnaround_time / n;
}

/**
 * Esta funcion se encarga de imprimir todos los procesos
 * @param processes lista de objetos de tipo proceso
 * @param n lenght
 */
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
