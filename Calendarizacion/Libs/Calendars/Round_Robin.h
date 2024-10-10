#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include "../PROCESS/PROCESS.h"
#include "../Queue/queue.h"
#include <stdio.h>

void round_robin(struct Process processes[], int n, int time_quantum);

#endif //ROUND_ROBIN_H
