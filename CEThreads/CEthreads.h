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



// Estructura para representar un hilo (equivalente a pthread_t)
typedef struct {
    int thread_id;       // ID del hilo
    void *stack;         // Puntero a la pila del hilo
    void *(*start_routine)(void *); // Función que ejecuta el hilo
    void *arg;           // Argumento de la función
} CEthread;

// Estructura para definir atributos del hilo (equivalente a pthread_attr_t)
typedef struct {
    size_t stack_size;   // Tamaño de la pila del hilo
    int priority;        // Prioridad del hilo (si decides implementar planificación)
} CEthread_attr_t;

// Estructura para representar un mutex (equivalente a pthread_mutex_t)
typedef struct {
    int futex;          // Estado del mutex (0 = desbloqueado, 1 = bloqueado)
} CEmutex;

// Función para crear un hilo (equivalente a pthread_create)
int CEthread_create(CEthread *thread, CEthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
//int CEthread_create(CEthread *thread, void *(*start_routine)(void *), void *arg);

// Función para terminar un hilo (equivalente a pthread_exit)
void CEthread_end(CEthread *thread);

// Función para esperar a que un hilo termine (equivalente a pthread_join)
int CEthread_join(CEthread *thread);

// Función para inicializar un mutex (equivalente a pthread_mutex_init)
void CEmutex_init(CEmutex *mutex);

// Función para destruir un mutex (equivalente a pthread_mutex_destroy)
void CEmutex_destroy(CEmutex *mutex);

// Función para bloquear un mutex (equivalente a pthread_mutex_lock)
void CEmutex_lock(CEmutex *mutex);

// Función para desbloquear un mutex (equivalente a pthread_mutex_unlock)
void CEmutex_unlock(CEmutex *mutex);

typedef enum {
    Normal, Pesquero, Patrulla
}TipoBarco;

struct Process {
    int pid;
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
};

struct Node {
    struct Process process;
    struct Node* next;
};

void swap(struct Process *xp, struct Process *yp);
void sort_by_arrival_time(struct Node** head);
void sort_by_waiting_time(struct Node** head);
float calculate_average_waiting_time(struct Node* head);
float calculate_average_turnaround_time(struct Process processes[], int n);
struct Process create_process(int pid, TipoBarco tipo, int priority, int burst_time, int deadline);

struct Node* create_node(struct Process process);
void append_node(struct Node** head, struct Process process);
void print_process_list(struct Node* head);
void free_list(struct Node* head);
void enqueue(struct Node** head, struct Process process);
int isEmpty(struct Node* head);
struct Process dequeue(struct Node** head);


#endif /* CETHREADS_H */
