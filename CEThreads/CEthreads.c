#define _GNU_SOURCE
#include <sched.h>  // Para clone()
#include <stdlib.h> // Para malloc()
#include <stdio.h>  // Para perror
#include <sys/wait.h>  // Para waitpid()
#include <stddef.h> // Para usar size_t
#include <string.h>  // Para memset()
#include <unistd.h>  // Para syscalls
#include "CEthreads.h"

//CE_thread_t: identificador del hilo
//CE_thread_attr_t: atributos del hilo (debe haber default)

//CE_thread_create:
//1.
//-Puntero al identificadodr del hilo
//-Puntero a los atributos del hilo
//-Puntero a la funcion de inicio (funcion a correr)
//-Puntero a los argumentos de la funcion de inicio

//2.
//Reservar espacio para la estructura del hilo (control block)
//Asigna memoria para la pila del hilo (puede ser especificada en CE_thread_attr_t)

//3.
//Configuracion del contexto del hilo (mucha vara)

//4.
//Interaccion con el kernel syscall (clone() en linux)
// user space -> kernel

//5.
//Se asigno el TID con el CE_thread_t

//...

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
                              CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD, arg);
    if (thread->thread_id == -1) return -1; // Error al crear el hilo

    return 0; // Éxito
}

// Función para esperar a que un hilo termine (equivalente a pthread_join)
int CEthread_join(CEthread *thread) {
    // Espera que el hilo termine (waitpid con __WALL para hilos tipo clone)
    return waitpid(thread->thread_id, NULL, __WALL);
}
