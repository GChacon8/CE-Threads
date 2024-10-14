#define _GNU_SOURCE //Importante para el clone()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Para sleep()
#include "CEthreads.h"  // CEthreads
#include "CEthreads.c"  // CEthreads

#define NUM_THREADS 5

// Variables compartidas
int contador = 0;  // Variable que será incrementada por los hilos
CEmutex mutex;     // Mutex para proteger la variable 'contador'

// Función que cada hilo ejecutará
void *incrementar(void *arg) {
    int id = *(int *)arg;

    // Cada hilo incrementa el contador 5 veces
    for (int i = 0; i < 5; ++i) {
        CEmutex_lock(&mutex);  // Sección crítica
        contador++;
        printf("Hilo %d incrementa contador a %d\n", id, contador);
        CEmutex_unlock(&mutex);  // Fin de sección crítica

        sleep(1);  // Simula alguna tarea
    }
    return NULL;
}

int main() {
    CEthread threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Inicializar el mutex
    CEmutex_init(&mutex);

    // Crear los hilos
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_ids[i] = i + 1;
        if (CEthread_create(&threads[i], NULL, incrementar, &thread_ids[i]) != 0) {
            perror("Error al crear hilo");
            exit(1);
        }
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_THREADS; ++i) {
        CEthread_join(&threads[i]);
    }

    // Mostrar el valor final del contador
    printf("Valor final del contador: %d\n", contador);

    // Destruir el mutex
    CEmutex_destroy(&mutex);

    // Finalizar los hilos
    for (int i = 0; i < NUM_THREADS; ++i) {
        CEthread_end(&threads[i]);
    }

    return 0;
}

