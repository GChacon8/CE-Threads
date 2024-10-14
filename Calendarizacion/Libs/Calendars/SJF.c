#include "SJF.h"

/**
 * Esta funcion se encarga de calcular el tiempo por SJF
 * @param processes objeto de tipo proceso
 * @param n lenght
 */
void SJF(struct Node* head) {
    int current_time = 0;
    int completed = 0;

    while (completed != 0) {
        struct Process* current_process = find_shortest_job(head, current_time);

        if (current_process != NULL) {
            current_process->completion_time = current_time + current_process->burst_time;
            current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;
            current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;

            current_time = current_process->completion_time;
            current_process->is_completed = 1;
            completed++;

            // Aquí podrías guardar o imprimir los resultados
            printf("Proceso PID=%d completado en tiempo=%d\n", current_process->pid, current_process->completion_time);
        } else {
            current_time++; // Si no hay procesos listos, incrementamos el tiempo
        }
    }
}

/**
 *
 * @param head
 * @param current_time
 * @return
 */
struct Process* find_shortest_job(struct Node* head, int current_time) {
    struct Node* temp = head;
    struct Process* shortest = NULL;
    int min_burst = INT_MAX;

    while (temp != NULL) {
        if (temp->process.arrival_time <= current_time && temp->process.is_completed == 0) {
            if (temp->process.burst_time < min_burst) {
                min_burst = temp->process.burst_time;
                shortest = &(temp->process);
            } else if (temp->process.burst_time == min_burst) {
                // Si hay empate en tiempo de ráfaga, preferimos el que llegó primero
                if (temp->process.arrival_time < shortest->arrival_time) {
                    shortest = &(temp->process);
                }
            }
        }
        temp = temp->next;
    }

    return shortest;
}