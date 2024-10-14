#include "edfs.h"

/**
 * Esta funcion se encarga de calcular la calendarizacion del EDFS
 * @param processes objeto de tipo proceso
 * @param n length
 * @param total_time
 */
void edfs(struct Node* head) {
    struct Node* current = head;
    int current_time = 0;

    while (current != NULL) {
        current_time += current->process.burst_time;
        current->process.completion_time = current_time;
        current->process.turnaround_time = current->process.completion_time - current->process.arrival_time;
        current->process.waiting_time = current->process.turnaround_time - current->process.burst_time;
        current->process.is_completed=1;

        current = current->next;
    }

}