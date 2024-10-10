#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Variable global para el letrero (0 = izquierda, 1 = derecha)
int letrero = 0;

// Mutex para proteger el acceso al letrero
pthread_mutex_t letrero_mutex;

// Variables para la cantidad de barcos en cada lado
int barcos_izquierda = 0;
int barcos_derecha = 0;

// Función para cambiar el letrero
void* cambiar_letrero(void* args) {
    int intervalo = *((int*) args);

    while (1) {
        sleep(intervalo);  // Espera el intervalo definido
        pthread_mutex_lock(&letrero_mutex);
        letrero = (letrero + 1) % 2;  // Cambia entre 0 (izquierda) y 1 (derecha)
        printf("Letrero cambiado a: %s\n", letrero == 0 ? "izquierda" : "derecha");
        pthread_mutex_unlock(&letrero_mutex);

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
        pthread_mutex_lock(&letrero_mutex);
        if ((letrero == 0 && lado[0] == 'I') || (letrero == 1 && lado[0] == 'D')) {
            printf("Barco pasando del lado %s. Barcos restantes: %d\n", lado, --(*barcos));
            pthread_mutex_unlock(&letrero_mutex);
            sleep(1);  // Simula el tiempo que tarda en pasar el barco
        } else {
            pthread_mutex_unlock(&letrero_mutex);
            usleep(500000);  // Espera un poco antes de volver a intentar
        }
    }

    printf("Todos los barcos del lado %s han pasado.\n", lado);
    return NULL;
}

int main() {
    pthread_t hilo_letrero, hilo_barcos_izquierda, hilo_barcos_derecha;
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
    pthread_mutex_init(&letrero_mutex, NULL);

    // Crea los hilos
    pthread_create(&hilo_letrero, NULL, cambiar_letrero, &intervalo);
    pthread_create(&hilo_barcos_izquierda, NULL, barcos, "Izquierda");
    pthread_create(&hilo_barcos_derecha, NULL, barcos, "Derecha");

    // Espera a que los hilos de los barcos terminen
    pthread_join(hilo_barcos_izquierda, NULL);
    pthread_join(hilo_barcos_derecha, NULL);

    // Una vez que todos los barcos han pasado, terminamos el hilo del letrero
    pthread_cancel(hilo_letrero);

    // Destruye el mutex
    pthread_mutex_destroy(&letrero_mutex);

    printf("Programa terminado.\n");

    return 0;
}
