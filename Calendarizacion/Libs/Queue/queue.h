#ifndef QUEUE_H
#define QUEUE_H

#include "../process/process.h"
#include <stdio.h>

struct Queue {
    int items[MAX_PROCESSES];
    int front;
    int rear;
};

void initQueue(struct Queue* q);
int isEmpty(struct Queue* q);
void enqueue(struct Queue* q, int value);
int dequeue(struct Queue* q);

#endif //QUEUE_H
