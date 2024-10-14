#ifndef SJF_H
#define SJF_H

#include "../../../CEThreads/CEthreads.h"
#include "../../../CEThreads/CEthreads.c"
#include <limits.h>

void SJF(struct Node* head);
struct Process* find_shortest_job(struct Node* head, int current_time);

#endif //SJF_H
