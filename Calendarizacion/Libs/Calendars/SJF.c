#include "SJF.h"

/**
 * Esta funcion se encarga de calcular el tiempo por SJF
 * @param processes objeto de tipo proceso
 * @param n lenght
 */
void SJF(struct Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int total_idle_time = 0;

    while (completed != n) {
        int idx = -1;
        int min_burst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].is_completed == 0) {
                if (processes[i].burst_time < min_burst) {
                    min_burst = processes[i].burst_time;
                    idx = i;
                }
                if (processes[i].burst_time == min_burst) {
                    if (processes[i].arrival_time < processes[idx].arrival_time) {
                        min_burst = processes[i].burst_time;
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            processes[idx].completion_time = current_time + processes[idx].burst_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;

            total_idle_time += current_time - processes[idx].arrival_time;

            current_time = processes[idx].completion_time;
            processes[idx].is_completed = 1;
            completed++;
        }
        else {
            current_time++;
        }
    }
}
