#include "Round_Robin.h"

/**
 * Esta funcion se encarga de calcular el tiempo que se  gastaria con el round_robin
 * @param processes objeto de tipo proceso
 * @param n lenght
 * @param time_quantum Tamaño del quantum(Set basico 3)
 */
void round_robin(struct Node* head) {
    int time_quantum = 3;
    struct Node* ready_queue = NULL; // Cola de procesos listos
    int current_time = 0;
    int completed = 0;

    // Contar el número total de procesos
    struct Node* temp = head;
    int n = 0;
    while (temp != NULL) {
        n++;
        temp = temp->next;
    }

    // Inicializar los tiempos restantes de los procesos
    temp = head;
    while (temp != NULL) {
        temp->process.remaining_time = temp->process.burst_time;
        temp = temp->next;
    }

    while (completed != n) {
        // Verificar si hay procesos que llegaron
        temp = head;
        while (temp != NULL) {
            if (temp->process.arrival_time <= current_time && temp->process.remaining_time > 0) {
                enqueue(&ready_queue, temp->process);
            }
            temp = temp->next;
        }

        if (isEmpty(ready_queue)) {
            current_time++;
            continue;
        }

        // Desencolar el primer proceso de la cola
        struct Process current_process = dequeue(&ready_queue);

        if (current_process.remaining_time <= time_quantum) {
            current_time += current_process.remaining_time;
            current_process.remaining_time = 0;
            completed++;
            current_process.completion_time = current_time;
            current_process.turnaround_time = current_process.completion_time - current_process.arrival_time;
            current_process.waiting_time = current_process.turnaround_time - current_process.burst_time;

            // Aquí podrías guardar o imprimir los resultados
            printf("Proceso PID=%d completado en tiempo=%d\n", current_process.pid, current_process.completion_time);
        } else {
            current_time += time_quantum;
            current_process.remaining_time -= time_quantum;

            // Volver a encolar el proceso, haciendo una copia para no perder la referencia
            enqueue(&ready_queue, current_process);
        }
    }
}