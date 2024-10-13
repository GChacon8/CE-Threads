#include "edfs.h"

/**
 * Esta funcion se encarga de calcular la calendarizacion del EDFS
 * @param processes objeto de tipo proceso
 * @param n length
 * @param total_time
 */
void edfs(struct Process processes[], int n, int total_time) {
    int current_time = 0;
    int completed = 0;
    int *timeline = (int *)calloc(total_time, sizeof(int));

    while (current_time < total_time && completed < n) {
        int idx = -1;
        int earliest_deadline = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].is_completed == 0 && processes[i].remaining_time > 0) {
                if (processes[i].deadline < earliest_deadline) {
                    earliest_deadline = processes[i].deadline;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            timeline[current_time] = processes[idx].pid;
            processes[idx].remaining_time--;

            if (processes[idx].remaining_time == 0) {
                processes[idx].completion_time = current_time + 1;
                processes[idx].is_completed = 1;
                completed++;
            }
        }

        current_time++;
    }
}