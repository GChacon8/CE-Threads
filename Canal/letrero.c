#define _GNU_SOURCE //Importante para el clone()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Para sleep()
#include "CEthreads.h"  // CEthreads
#include "CEthreads.c"  // CEthreads

// Variable global para el letrero (0 = izquierda, 1 = derecha)
int letrero = 0;

// Mutex para proteger el acceso al letrero
CEmutex letrero_mutex;

// Variables para la cantidad de barcos en cada lado
int barcos_izquierda = 0;
int barcos_derecha = 0;

// Función para cambiar el letrero
void* cambiar_letrero(void* args) {
    int intervalo = *((int*) args);

    while (1) {
        sleep(intervalo);  // Espera el intervalo definido
        CEmutex_lock(&letrero_mutex);
        letrero = (letrero + 1) % 2;  // Cambia entre 0 (izquierda) y 1 (derecha)
        printf("Letrero cambiado a: %s\n", letrero == 0 ? "izquierda" : "derecha");
        CEmutex_unlock(&letrero_mutex);

        // Si no quedan barcos, terminamos el hilo de cambio de letrero
        if (barcos_izquierda == 0 && barcos_derecha == 0) {
            printf("Todos los barcos han pasado.\n");
            break;
        }
    }
    return NULL;
}

// Función para simular el paso de barcos por el canal
void* barcos(void* args) {
    char* lado = (char*) args;
    int* barcos = lado[0] == 'I' ? &barcos_izquierda : &barcos_derecha;

    while (*barcos > 0) {
        CEmutex_lock(&letrero_mutex);
        if ((letrero == 0 && lado[0] == 'I') || (letrero == 1 && lado[0] == 'D')) {
            printf("Barco pasando del lado %s. Barcos restantes: %d\n", lado, --(*barcos));
            CEmutex_unlock(&letrero_mutex);
            sleep(1);  // Simula el tiempo que tarda en pasar el barco
        } else {
            CEmutex_unlock(&letrero_mutex);
            usleep(500000);  // Espera un poco antes de volver a intentar
        }
    }

    printf("Todos los barcos del lado %s han pasado.\n", lado);
    return NULL;
}

int main() {
    CEthread hilo_letrero, hilo_barcos_izquierda, hilo_barcos_derecha;
    int intervalo;

    // Solicita el intervalo de cambio del letrero
    printf("Ingrese el intervalo de cambio del letrero (segundos): ");
    scanf("%d", &intervalo);

    // Solicita la cantidad de barcos en cada lado
    printf("Ingrese la cantidad de barcos en el lado izquierdo: ");
    scanf("%d", &barcos_izquierda);
    printf("Ingrese la cantidad de barcos en el lado derecho: ");
    scanf("%d", &barcos_derecha);

    // Inicializa el mutex
    CEmutex_init(&letrero_mutex);

    // Crea los hilos
    CEthread_create(&hilo_letrero, NULL, cambiar_letrero, &intervalo);
    CEthread_create(&hilo_barcos_izquierda, NULL, barcos, "izquierda");
    CEthread_create(&hilo_barcos_derecha, NULL, barcos, "derecha");

    // Espera a que los hilos de los barcos terminen
    CEthread_join(&hilo_barcos_izquierda);
    CEthread_join(&hilo_barcos_derecha);

    // Una vez que todos los barcos han pasado, terminamos el hilo del letrero
    //pthread_cancel(hilo_letrero);

    // Destruye el mutex
    CEmutex_destroy(&letrero_mutex);

    printf("Programa terminado.\n");

    return 0;
}