#include "SJF.h"

/**
 * Esta funcion se encarga de calcular la calendarizacion del SJF
 * @param head La cabeza de una lista enlazada
 */
void SJF(struct Node* head) {
    int current_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int size = l_size(head);
    int count = 0;
    struct Node* current = head;

    while (current != NULL) {
        current->process.waiting_time = current_time;
        current->process.turnaround_time = current->process.waiting_time + current->process.burst_time;

        total_waiting_time += current->process.waiting_time;
        total_turnaround_time += current->process.turnaround_time;

        current_time += current->process.burst_time;
        
        current->process.completion_time = current->process.arrival_time + current->process.burst_time + current_time;
        current=current->next;
    }
}
