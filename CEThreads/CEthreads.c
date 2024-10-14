#define _GNU_SOURCE
#include <sched.h>  // Para clone()
#include <stdlib.h> // Para malloc()
#include <stdio.h>  // Para perror
#include <sys/wait.h>  // Para waitpid()
#include <stddef.h> // Para usar size_t
#include <string.h>  // Para memset()
#include <unistd.h>  // Para syscalls
#include <limits.h>       // Para INT_MAX
#include <errno.h>        // Para manejar errores
#include "CEthreads.h"
#include <linux/futex.h>  // Para la syscall futex
#include <sys/syscall.h>  // Para usar syscall()


#define STACK_SIZE 1024 * 1024 // Tamaño de la pila de 1MB

// Función para crear un hilo (equivalente a pthread_create)
int CEthread_create(struct CEthread *thread, void *(*start_routine)(void *), void *arg) {
    // Define el tamaño de la pila
    size_t stack_size = (1024 * 1024); // 1MB de pila por defecto
    thread->stack = malloc(stack_size);
    if (!thread->stack) return -1; // Error al asignar memoria

    // Inicializa la pila y las variables
    memset(thread->stack, 0, stack_size);
    thread->start_routine = start_routine;
    thread->arg = arg;

    // Crea el hilo usando clone
    thread->thread_id = clone((int (*)(void *))start_routine, 
                              (char *)thread->stack + stack_size, 
                              CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND, arg);
    if (thread->thread_id == -1) return -1; // Error al crear el hilo

    return 0; // Éxito
}

// Función para esperar a que un hilo termine (equivalente a pthread_join)
int CEthread_join(struct CEthread *thread) {
    // Espera que el hilo termine (waitpid con __WALL para hilos tipo clone)
    return waitpid(thread->thread_id, NULL, __WALL);
}

// Terminar el hilo
void CEthread_end(struct CEthread *thread) {
    kill(thread->thread_id, SIGTERM);  // Enviar señal de terminación
    free(thread->stack);  // Liberar la pila
}

//Empieza un mutex en un estado de 0, o sea, desbloqueado
void CEmutex_init(CEmutex *mutex) {
    mutex->futex = 0;
}

//No destruye como tal el mutex, pero lo restablece a su estado original
void CEmutex_destroy(CEmutex *mutex) {
    mutex->futex = 0;  // Opcional: Dejar el valor en 0 para indicar que está destruido
}

//Funcion para bloquear el mutex, no permite el acceso al recurso
void CEmutex_lock(CEmutex *mutex) {
    // Intenta cambiar de 0 a 1 (adquirir el lock)
    if (__sync_val_compare_and_swap(&mutex->futex, 0, 1) != 0) {
        // Si no se adquiere el lock, bloquea en futex
        while (syscall(SYS_futex, &mutex->futex, FUTEX_WAIT, 1, NULL, NULL, 0) == -1 && errno == EINTR) {
            // Reintenta si la syscall fue interrumpida
            continue;
        }
    }
}

//Funcion para desbloquear el mutex, permite el acceso al recurso
void CEmutex_unlock(CEmutex *mutex) {
    // Cambia el valor de 1 a 0 (libera el lock)
    if (__sync_val_compare_and_swap(&mutex->futex, 1, 0) == 1) {
        // Despierta a cualquier hilo esperando en el futex
        syscall(SYS_futex, &mutex->futex, FUTEX_WAKE, 1, NULL, NULL, 0);
    }
}

/**
 * Esta función cuenta el número de nodos en la lista enlazada.
 * @param head Puntero al inicio de la lista enlazada.
 * @return Número de nodos en la lista.
 */
int l_size(struct Node* head) {
    int count = 0;
    struct Node* current = head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

/**
 * Esta funcion se encarga de calcular el tiempo promedio de espera
 * @param head La cabeza de una lista enlazada
 * @return float
 */
float calculate_average_waiting_time(struct Node* head) {
    float total_waiting_time = 0;
    struct Node* current = head;
    int size = l_size(head);

    while (current != NULL) {
        total_waiting_time += current->process.waiting_time;
        current = current->next;
    }
    return total_waiting_time / size;
}

/**
 * Esta funcion se encarga de calcular el tiempo de cola promedio
 * @param head La cabeza de una lista enlazada
 * @return float
 */
float calculate_average_turnaround_time(struct Node* head) {
    float total_turnaround_time = 0;
    struct Node* current = head;
    int size = l_size(head);
    while (current != NULL) {
        total_turnaround_time += current->process.turnaround_time;
        current = current->next;
    }

    return total_turnaround_time / size;
}

/**
 * Este metodo crea un proceso que se modelara como un barco
 * @param thread_id int
 * @param tipo TipoBarco
 * @param priority int
 * @param burst_time int
 * @param deadline int
 * @return Process
 */
struct CEthread create_process(int thread_id, TipoBarco tipo, int priority, int burst_time, int deadline) {
    struct CEthread process;
    process.thread_id = thread_id;
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
 * @return Process
 */
struct Node* create_node(struct CEthread process) {
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
void append_node(struct Node** head, struct CEthread process) {
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
                temp->process.thread_id, temp->process.arrival_time,
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
 * Esta funcion se encarga de colocar en cola un proceso
 * @param head
 * @param process
 */
void enqueue(struct Node** head, struct CEthread process) {
    append_node(head, process);
}

/**
 * Esta funcion revisa si la lista enlazada esta vacia
 * @param head 
 * @return 
 */
int isEmpty(struct Node* head) {
    return head == NULL;
}

/**
 * Esta funcion se encarga de sacar un proceso de la cola
 * @param head
 * @return
 */
struct CEthread dequeue(struct Node** head) {
    if (isEmpty(*head)) {
        struct CEthread empty_process = {0}; // Proceso vacío
        return empty_process;
    }
    struct Node* temp = *head;
    struct CEthread process = temp->process;
    *head = (*head)->next;
    free(temp);

    return process;
}

struct CEthread peek(struct Node* head) {
    if (isEmpty(head)) {
        struct CEthread empty_process = {0};  // Proceso vacío si la lista está vacía
        return empty_process;
    }

    return head->process;  // Retorna el proceso del primer nodo sin eliminarlo
}

/**
 * Esta funcion imprime un solo proceso
 * @param head La cabeza de una lista enlazada
 */
void print_process(struct Node* head) {
    struct Node* act = head;
    printf("PID=%d, Arrival=%d, Tipo=%d, Burst=%d, Completition Time=%d, Waiting Time=%d\n",
                act->process.thread_id, act->process.arrival_time,
                act->process.tipo, act->process.burst_time,
                act->process.completion_time,act->process.waiting_time);
}
