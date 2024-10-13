#include "queue.h"

/**
 * Esta funcion inicia una cola de procesos
 * @param q Un objeto de tipo cola
 */
void initQueue(struct Queue* q) {
    q->front = -1;
    q->rear = -1;
}

/**
 * Esta funcion vacia la cola
 * @param q Un objeto de tipo cola
 * @return Bool
 */
int isEmpty(struct Queue* q) {
    return q->rear == -1;
}

/**
 * Esta funcion se encarga de añadir a la cola
 * @param q Un objeto de tipo cola
 * @param value
 */
void enqueue(struct Queue* q, int value) {
    if (q->rear == MAX_PROCESSES - 1)
        printf("Queue is full");
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

/**
 * Esta funcion se encarga de sacar de la cola
 * @param q Un objeto de tipo cola
 * @return Un objeto de tipo cola
 */
int dequeue(struct Queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}
