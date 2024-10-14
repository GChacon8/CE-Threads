#include "PROCESS.h"
#include <stdio.h>

/**
 * Esta funcion se encarga de cambiar un proceso por otro en la lista.
 * @param xp objeto de tipo proceso
 * @param yp objeto de tipo proceso
 */
void swap(struct Process *xp, struct Process *yp) {
    struct Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/**
 * Esta funcion ordena una lista de procesos
 * @param processes lista de objetos de tipo proceso
 * @param n length
 */
void sort_by_arrival_time(struct Node** head) {
    struct Node* i;
    struct Node* j;
    struct Process temp;

    for (i = *head; i != NULL; i=i->next) {
        for (j =i->next; j != NULL; j=j->next) {
            if (i->process.arrival_time > j->process.arrival_time) {
                temp = i->process;
                i->process = j->process;
                j->process = temp;
            }
        }
    }
}
    /**
     * Esta funcion ordena una lista de procesos
     * @param processes lista de objetos de tipo proceso
     * @param n length
     */
void sort_by_waiting_time(struct Node** head) {
    struct Node* i;
    struct Node* j;
    struct Process temp;

    for (i = *head; i != NULL; i=i->next) {
        for (j =i->next; j != NULL; j=j->next) {
            if (i->process.waiting_time > j->process.waiting_time) {
                temp = i->process;
                i->process = j->process;
                j->process = temp;
            }
        }
    }
}

/**
 * Esta funcion calcula el tiempo promedio de espera de los procesos
 * @param processes lista de objetos de tipo proceso
 * @param n lenght
 * @return Tiempo promedio de espera
 */
float calculate_average_waiting_time(struct Node* head) {
    float total_waiting_time = 0;
    int count = 0;

    struct Node* temp = head;

    while (temp != NULL) {
        total_waiting_time += temp->process.waiting_time;
        count++;
        temp = temp->next;
    }

    if (count == 0) {
        return 0;
    }
    return total_waiting_time / count;
}

/**
 * Esta funcion calcula el tiempo promedio en cola de los procesos
 * @param processes lista de objetos de tipo proceso
 * @param n length
 * @return Tiempo de cola promedio de los procesos
 */
float calculate_average_turnaround_time(struct Process processes[], int n) {
    float total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_turnaround_time += processes[i].turnaround_time;
    }
    return total_turnaround_time / n;
}

/**
 * Este metodo crea un proceso que se modelara como un barco
 * @param pid int
 * @param tipo TipoBarco
 * @param priority int
 * @param burst_time int
 * @param deadline int
 * @return Process
 */
struct Process create_process(int pid, TipoBarco tipo, int priority, int burst_time, int deadline) {
    struct Process process;
    process.pid = pid;
    process.burst_time = burst_time;
    process.completion_time = 0;
    process.turnaround_time = 0;
    process.waiting_time = 0;
    process.priority = priority;
    process.is_completed = 0;
    process.deadline = deadline;
    process.remaining_time = burst_time;
    process.tipo = tipo;
    switch (tipo) {
        case Normal:
            process.arrival_time = 2;
            break;
        case Pesquero:
            process.arrival_time = 1;
            break;
        case Patrulla:
            process.arrival_time = 0;
            break;
    }
    return process;
}

/**
 * Este metodo se encarga de crear el nodo principal de la lista enlazada
 * @param process
 * @return
 */
struct Node* create_node(struct Process process) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        printf("Not enough memory to create new node\n");
        exit(EXIT_FAILURE);
    }
    new_node->process = process;
    new_node->next = NULL;
    return new_node;
}

/**
 *  Esta funcion se encarga de añadir un nuevo elemento a la lista enlazada
 * @param head
 * @param process
 */
void append_node(struct Node** head, struct Process process) {
    struct Node* new_node1 = create_node(process);
    if (*head == NULL) {
        *head = new_node1;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node1;
}

/**
 * Esta funcion se encarga de imprimir los elementos de la lista
 * @param head
 */
void print_process_list(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("PID=%d, Arrival=%d, Tipo=%d, Burst=%d, Completition Time=%d, Waiting Time=%d\n",
                temp->process.pid, temp->process.arrival_time,
                temp->process.tipo, temp->process.burst_time,
                temp->process.completion_time,temp->process.waiting_time);
        temp = temp->next;
    }
    float avg_waiting_time = calculate_average_waiting_time(head);
    printf("Tiempo de espera promedio: %.2f\n", avg_waiting_time);
}

/**
 * Esta funcion se encarga de limpiar la lista enlazada
 * @param head
 */
void free_list(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/**
 *
 * @param head
 * @param process
 */
void enqueue(struct Node** head, struct Process process) {
    append_node(head, process);
}

/**
 * 
 * @param head 
 * @return 
 */
int isEmpty(struct Node* head) {
    return head == NULL;
}

/**
 *
 * @param head
 * @return
 */
struct Process dequeue(struct Node** head) {
    if (isEmpty(*head)) {
        struct Process empty_process = {0}; // Proceso vacío
        return empty_process;
    }
    struct Node* temp = *head;
    struct Process process = temp->process;
    *head = (*head)->next;
    free(temp);

    return process;
}
