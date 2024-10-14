#ifndef CETHREADS_H
#define CETHREADS_H
#define _GNU_SOURCE
#include <sched.h>  // Para clone()
#include <stdlib.h>  // Para malloc()
#include <string.h>  // Para memset()
#include <unistd.h>  // Para syscalls
#include <sys/wait.h> // Para waitpid()
#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

typedef enum {
    Normal, Pesquero, Patrulla
}TipoBarco;

// Estructura para representar un hilo (equivalente a pthread_t)
struct CEthread{
    int thread_id;       // ID del hilo
    int arrival_time;
    TipoBarco tipo;
    int priority;
    int burst_time;
    int completion_time;
    float turnaround_time;
    int waiting_time;
    int is_completed;
    int remaining_time;
    int deadline;
    void *stack;         // Puntero a la pila del hilo
    void *(*start_routine)(void *); // Función que ejecuta el hilo
    void *arg;           // Argumento de la función
};

// Estructura para representar un mutex (equivalente a pthread_mutex_t)
typedef struct {
    int futex;          // Estado del mutex (0 = desbloqueado, 1 = bloqueado)
} CEmutex;

struct Node {
    struct CEthread process;
    struct Node* next;
};

// Función para crear un hilo (equivalente a pthread_create)
int CEthread_create(struct CEthread *thread, void *(*start_routine)(void *), void *arg);

// Función para terminar un hilo (equivalente a pthread_exit)
void CEthread_end(struct CEthread *thread);

// Función para esperar a que un hilo termine (equivalente a pthread_join)
int CEthread_join(struct CEthread *thread);

// Función para inicializar un mutex (equivalente a pthread_mutex_init)
void CEmutex_init(CEmutex *mutex);

// Función para destruir un mutex (equivalente a pthread_mutex_destroy)
void CEmutex_destroy(CEmutex *mutex);

// Función para bloquear un mutex (equivalente a pthread_mutex_lock)
void CEmutex_lock(CEmutex *mutex);

// Función para desbloquear un mutex (equivalente a pthread_mutex_unlock)
void CEmutex_unlock(CEmutex *mutex);

int l_size(struct Node* head);
float calculate_average_waiting_time(struct Node* head);
struct CEthread create_process(int thread_id, TipoBarco tipo, int priority, int burst_time, int deadline);
struct Node* create_node(struct CEthread process);
void append_node(struct Node** head, struct CEthread process);
void print_process_list(struct Node* head);
void free_list(struct Node* head);
void enqueue(struct Node** head, struct CEthread process);
int isEmpty(struct Node* head);
struct CEthread dequeue(struct Node** head);

#endif /* CETHREADS_H */