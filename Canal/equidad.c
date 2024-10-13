#define _GNU_SOURCE //Importante para el clone()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Para sleep()
#include "CEthreads.h"  // CEthreads
#include "CEthreads.c"  // CEthreads

// Variables globales para la cantidad de barcos en cada lado
int barcos_izquierda = 0;
int barcos_derecha = 0;
int W;  // Cantidad de barcos que pasan en cada turno

// Mutex para controlar el acceso exclusivo al canal
CEmutex canal_mutex;

// Variables para controlar el turno
int turno = 0;  // 0 = izquierda, 1 = derecha

// Función para simular el paso de barcos de un lado
void* barcos(void* args) {
    char* lado = (char*) args;
    int* barcos = lado[0] == 'I' ? &barcos_izquierda : &barcos_derecha;
    int direccion = lado[0] == 'I' ? 0 : 1;  // 0 para izquierda, 1 para derecha

    while (*barcos > 0) {
        CEmutex_lock(&canal_mutex);

        // Si no es el turno de este lado, libera el mutex y espera
        if (turno != direccion) {
            CEmutex_unlock(&canal_mutex);
            usleep(500000);  // Espera un poco antes de volver a intentar
            continue;
        }

        // Si es el turno, permite pasar hasta W barcos o la cantidad restante
        for (int i = 0; i < W && *barcos > 0; i++) {
            printf("Barco pasando del lado %s. Barcos restantes: %d\n", lado, --(*barcos));
            sleep(1);  // Simula el tiempo que tarda en pasar el barco
        }

        // Cambia el turno al otro lado si hay barcos en el otro lado
        if ((turno == 0 && barcos_derecha > 0) || (turno == 1 && barcos_izquierda > 0)) {
            turno = (turno + 1) % 2;
        }

        CEmutex_unlock(&canal_mutex);
        usleep(500000);  // Espera un poco antes de volver a intentar
    }

    printf("Todos los barcos del lado %s han pasado.\n", lado);
    return NULL;
}

int main() {
    CEthread hilo_barcos_izquierda, hilo_barcos_derecha;

    // Solicita el parámetro W
    printf("Ingrese el número de barcos que pueden pasar por cada lado (W): ");
    scanf("%d", &W);

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

