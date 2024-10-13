#define _GNU_SOURCE //Importante para el clone()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Para sleep()
#include "CEthreads.h"  // CEthreads
#include "CEthreads.c"  // CEthreads

// Variables para la cantidad de barcos en cada lado
int barcos_izquierda = 0;
int barcos_derecha = 0;

// Mutex para asegurar que solo un barco cruce a la vez
CEmutex canal_mutex;

// Función para simular el paso de barcos por el canal
void* barcos(void* args) {
    char* lado = (char*) args;
    int* barcos = lado[0] == 'I' ? &barcos_izquierda : &barcos_derecha;

    while (*barcos > 0) {
        CEmutex_lock(&canal_mutex);  // Asegura que solo un barco cruce a la vez

        // Simula el paso del barco
        printf("Barco pasando del lado %s. Barcos restantes: %d\n", lado, --(*barcos));
        sleep(1);  // Simula el tiempo que tarda en pasar el barco

        CEmutex_unlock(&canal_mutex);  // Libera el canal para el siguiente barco

        usleep(500000);  // Espera un poco antes de que otro barco intente cruzar
    }

    printf("Todos los barcos del lado %s han pasado.\n", lado);
    return NULL;
}

int main() {
    CEthread hilo_barcos_izquierda, hilo_barcos_derecha;

    // Solicita la cantidad de barcos en cada lado
    printf("Ingrese la cantidad de barcos en el lado izquierdo: ");
    scanf("%d", &barcos_izquierda);
    printf("Ingrese la cantidad de barcos en el lado derecho: ");
    scanf("%d", &barcos_derecha);

    // Inicializa el mutex
    CEmutex_init(&canal_mutex);

    // Crea los hilos para simular el paso de los barcos de ambos lados
    CEthread_create(&hilo_barcos_izquierda, NULL, barcos, "izquierda");
    CEthread_create(&hilo_barcos_derecha, NULL, barcos, "derecha");

    // Espera a que los hilos de los barcos terminen
    CEthread_join(&hilo_barcos_izquierda);
    CEthread_join(&hilo_barcos_derecha);

    // Destruye el mutex
    CEmutex_destroy(&canal_mutex);

    printf("Programa terminado.\n");

    return 0;
}