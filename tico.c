#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Variables para la cantidad de barcos en cada lado
int barcos_izquierda = 0;
int barcos_derecha = 0;

// Mutex para asegurar que solo un barco cruce a la vez
pthread_mutex_t canal_mutex;

// Función para simular el paso de barcos por el canal
void* barcos(void* args) {
    char* lado = (char*) args;
    int* barcos = lado[0] == 'I' ? &barcos_izquierda : &barcos_derecha;

    while (*barcos > 0) {
        pthread_mutex_lock(&canal_mutex);  // Asegura que solo un barco cruce a la vez

        // Simula el paso del barco
        printf("Barco pasando del lado %s. Barcos restantes: %d\n", lado, --(*barcos));
        sleep(1);  // Simula el tiempo que tarda en pasar el barco

        pthread_mutex_unlock(&canal_mutex);  // Libera el canal para el siguiente barco

        usleep(500000);  // Espera un poco antes de que otro barco intente cruzar
    }

    printf("Todos los barcos del lado %s han pasado.\n", lado);
    return NULL;
}

int main() {
    pthread_t hilo_barcos_izquierda, hilo_barcos_derecha;

    // Solicita la cantidad de barcos en cada lado
    printf("Ingrese la cantidad de barcos en el lado izquierdo: ");
    scanf("%d", &barcos_izquierda);
    printf("Ingrese la cantidad de barcos en el lado derecho: ");
    scanf("%d", &barcos_derecha);

    // Inicializa el mutex
    pthread_mutex_init(&canal_mutex, NULL);

    // Crea los hilos para simular el paso de los barcos de ambos lados
    pthread_create(&hilo_barcos_izquierda, NULL, barcos, "Izquierda");
    pthread_create(&hilo_barcos_derecha, NULL, barcos, "Derecha");

    // Espera a que los hilos de los barcos terminen
    pthread_join(hilo_barcos_izquierda, NULL);
    pthread_join(hilo_barcos_derecha, NULL);

    // Destruye el mutex
    pthread_mutex_destroy(&canal_mutex);

    printf("Programa terminado.\n");

    return 0;
}
