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

#include <sched.h>  // Para clone()
#include <stdlib.h> // Para malloc()

// Función para crear un hilo (equivalente a pthread_create)
int CEthread_create(CEthread *thread, CEthread_attr_t *attr, void *(*start_routine)(void *), void *arg) {
    // Define el tamaño de la pila
    size_t stack_size = attr ? attr->stack_size : (1024 * 1024); // 1MB de pila por defecto
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
int CEthread_join(CEthread *thread) {
    // Espera que el hilo termine (waitpid con __WALL para hilos tipo clone)
    return waitpid(thread->thread_id, NULL, __WALL);
}

// Terminar el hilo
void CEthread_end(CEthread *thread) {
    kill(thread->thread_id, SIGTERM);  // Enviar señal de terminación
    free(thread->stack);  // Liberar la pila
}


void CEmutex_init(CEmutex *mutex) {
    mutex->futex = 0;
}

void CEmutex_destroy(CEmutex *mutex) {
    mutex->futex = 0;  // Opcional: Dejar el valor en 0 para indicar que está destruido
}

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

void CEmutex_unlock(CEmutex *mutex) {
    // Cambia el valor de 1 a 0 (libera el lock)
    if (__sync_val_compare_and_swap(&mutex->futex, 1, 0) == 1) {
        // Despierta a cualquier hilo esperando en el futex
        syscall(SYS_futex, &mutex->futex, FUTEX_WAKE, 1, NULL, NULL, 0);
    }
}

