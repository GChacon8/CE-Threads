#ifndef SJF_H
#define SJF_H

#include "../PROCESS/PROCESS.h"
#include <limits.h>

void SJF(struct Node* head);
struct Process* find_shortest_job(struct Node* head, int current_time);

#endif //SJF_H
