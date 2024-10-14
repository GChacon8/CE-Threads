#include "fcfs.h"

/**
 * Esta funcion se encarga de calcular el tiempo por fcfs
 * @param processes lista de objetos de tipo proceso
 * @param n length
 */
void fcfs(struct Node* head) {
    int current_time = 0;
    struct Node* current = head;
    while (current != NULL) {
        if (current_time < current->process.arrival_time) {
            current_time = current->process.arrival_time;
        }

        // Calcular los tiempos
        current->process.completion_time = current_time + current->process.burst_time;
        current->process.turnaround_time = current->process.completion_time - current->process.arrival_time;
        current->process.waiting_time = current->process.turnaround_time - current->process.burst_time;

        // Actualizar el tiempo actual
        current_time = current->process.completion_time;

        // Mover al siguiente nodo
        current = current->next;
    }
}
