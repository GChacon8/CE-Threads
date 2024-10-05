#define _GNU_SOURCE
#include <sched.h>  // Para clone()
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "CEthreads.h"  // Tu nueva biblioteca CEthreads
#include "CEthreads.c"  // Tu nueva biblioteca CEthreads

#define NUM_THREADS 5

void *perform_work(void *arguments) {
    int index = *((int *)arguments);
    int sleep_time = 1 + rand() % NUM_THREADS;
    printf("Thread %d: Started.\n", index);
    printf("Thread %d: Will be sleeping for %d seconds.\n", index, sleep_time);
    sleep(sleep_time);
    printf("Thread %d: Ended.\n", index);
    return NULL;
}

int main(void) {
    CEthread threads[NUM_THREADS];    // Usamos CEthread en lugar de pthread_t
    int thread_args[NUM_THREADS];
    int i;
    int result_code;

    // Crear todos los hilos uno por uno
    for (i = 0; i < NUM_THREADS; i++) {
        printf("In main: Creating thread %d.\n", i);
        thread_args[i] = i;
        result_code = CEthread_create(&threads[i], NULL, perform_work, &thread_args[i]);
        if (result_code != 0) {
        fprintf(stderr, "Error creating thread %d: %d\n", i, result_code);
        exit(EXIT_FAILURE);  // Salir si hubo un error
        }
        assert(!result_code);  // Verificar que se crea el hilo correctamente
    }

    printf("In main: All threads are created.\n");

    // Esperar que cada hilo termine
    for (i = 0; i < NUM_THREADS; i++) {
        result_code = CEthread_join(&threads[i]);
        if (result_code != 0) {
        fprintf(stderr, "Error joining thread %d: %d\n", i, result_code);
        exit(EXIT_FAILURE);  // Salir si hubo un error
        }
        assert(!result_code);  // Verificar que el hilo termina correctamente
        printf("In main: Thread %d has ended.\n", i);
    }

    printf("Main program has ended.\n");
    return 0;
}
