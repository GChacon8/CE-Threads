#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define W 3 // Número de barcos que deben pasar por cada lado
#define TOTAL_BARCOS 10 // Número total de barcos por cada lado

pthread_mutex_t canal_mutex; // Para controlar el acceso al canal
int barcos_izquierda = TOTAL_BARCOS; 
int barcos_derecha = 4;//TOTAL_BARCOS;

void* pasar_barco_izq_a_der(void* arg) {
    pthread_mutex_lock(&canal_mutex); // Acceso al canal
    printf("Barco %d pasa de izquierda a derecha\n", *(int*)arg);
    sleep(1); // Simula el tiempo de cruce del canal
    pthread_mutex_unlock(&canal_mutex); // Libera el canal
    return NULL;
}

void* pasar_barco_der_a_izq(void* arg) {
    pthread_mutex_lock(&canal_mutex); // Acceso al canal
    printf("Barco %d pasa de derecha a izquierda\n", *(int*)arg);
    sleep(1); // Simula el tiempo de cruce del canal
    pthread_mutex_unlock(&canal_mutex); // Libera el canal
    return NULL;
}

void transportar_barcos() {
    pthread_t barcos[W];
    int barco_id[W];

    // Transporta W barcos de izquierda a derecha
    for (int i = 0; i < W && barcos_izquierda > 0; i++) {
        barco_id[i] = i + 1;
        pthread_create(&barcos[i], NULL, pasar_barco_izq_a_der, &barco_id[i]);
        barcos_izquierda--;
    }
    for (int i = 0; i < W; i++) {
        pthread_join(barcos[i], NULL);
    }

    // Transporta W barcos de derecha a izquierda
    for (int i = 0; i < W && barcos_derecha > 0; i++) {
        barco_id[i] = i + 1;
        pthread_create(&barcos[i], NULL, pasar_barco_der_a_izq, &barco_id[i]);
        barcos_derecha--;
    }
    for (int i = 0; i < W; i++) {
        pthread_join(barcos[i], NULL);
    }
}

int main() {
    pthread_mutex_init(&canal_mutex, NULL);

    while (barcos_izquierda > 0 || barcos_derecha > 0) {
        transportar_barcos();
    }

    pthread_mutex_destroy(&canal_mutex);
    return 0;
}
