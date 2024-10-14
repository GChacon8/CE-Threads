#ifndef CETHREADS_H
#define CETHREADS_H
#define _GNU_SOURCE
#include <sched.h>  // Para clone()
#include <stdlib.h>  // Para malloc()
#include <string.h>  // Para memset()
#include <unistd.h>  // Para syscalls
#include <sys/wait.h> // Para waitpid()


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

#endif /* CETHREADS_H */
