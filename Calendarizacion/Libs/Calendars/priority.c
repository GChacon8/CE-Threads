#include "priority.h"

/**
 * Esta funcion se encarga de calcular el tiempo que se  gastaria con el priority
 * @param head
 */
void priority(struct Node* head) {
    int current_time = 0;
    int completed = 0;
    int total_idle_time = 0;

    // Contar el número total de procesos
    struct Node* temp = head;
    int n = 0;
    while (temp != NULL) {
        n++;
        temp = temp->next;
    }

    while (completed != n) {
        int idx = -1;
        int highest_priority = INT_MAX;

        // Buscar el proceso listo con la mayor prioridad
        temp = head;
        int i = 0;
        while (temp != NULL) {
            if (temp->process.arrival_time <= current_time && temp->process.is_completed == 0) {
                if (temp->process.priority < highest_priority) {
                    highest_priority = temp->process.priority;
                    idx = i;
                }
                if (temp->process.priority == highest_priority) {
                    if (temp->process.arrival_time < head->process.arrival_time) {
                        highest_priority = temp->process.priority;
                        idx = i;
                    }
                }
            }
            temp = temp->next;
            i++;
        }

        if (idx != -1) {
            // Ejecutar el proceso seleccionado
            temp = head;
            for (i = 0; i < idx; i++) {
                temp = temp->next;
            }

            temp->process.completion_time = current_time + temp->process.burst_time;
            temp->process.turnaround_time = temp->process.completion_time - temp->process.arrival_time;
            temp->process.waiting_time = temp->process.turnaround_time - temp->process.burst_time;

            total_idle_time += current_time - temp->process.arrival_time;

            current_time = temp->process.completion_time;
            temp->process.is_completed = 1;
            completed++;
        } else {
            current_time++;
        }
    }
}