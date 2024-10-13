#include "Barcos.h"
#include <stdio.h>

// Función para inicializar un barco con los valores dados
void instanciarBarcos(Barco* barco, int pid, TipoBarco tipo, int longitud_canal) {
    barco->pid = pid;
    barco->tipo = tipo;

    // Ajustar la velocidad y deadline según el tipo de barco
    switch (tipo) {
        case NORMAL:
            barco->arrival_time = 1.0; // Ejemplo: 1.5 unidades/segundo para barco normal
            barco->deadline = (int)(longitud_canal / barco->arrival_time) + 2;
            barco->priority = 1;
            break;
        case PESQUERO:
            barco->arrival_time = 2.0; // Ejemplo: 2.0 unidades/segundo para barco pesquero
            barco->deadline = (int)(longitud_canal / barco->arrival_time) + 2;
            barco->priority = 2;
            break;
        case PATRULLA:
            barco->arrival_time = 3.0; // Ejemplo: 3 unidades/segundo para barco patrullero
            barco->deadline = (int)(longitud_canal / barco->arrival_time) + 2;
            barco->priority = 3;
            break;
        default:
            barco->arrival_time = 1.0; // Valor por defecto
            barco->deadline = (int)(longitud_canal / barco->arrival_time) + 2;
            barco->priority = 1;
            break;
    }

    // Inicializar el tiempo restante
    barco->remaining_time = (int)(longitud_canal / barco->arrival_time);
}

// Función para mostrar información del barco
void barcosInfo(const Barco* barco) {
    const char* tipo_str;

    switch (barco->tipo) {
        case NORMAL:
            tipo_str = "Normal";
            break;
        case PESQUERO:
            tipo_str = "Pesquero";
            break;
        case PATRULLA:
            tipo_str = "Patrulla";
            break;
        default:
            tipo_str = "Desconocido";
            break;
    }

    printf("Barco ID: %d, Tipo: %s, Velocidad: %.2f unidades/segundo, Tiempo restante: %d, Deadline: %d, Prioridad: %d\n",
       barco->pid, tipo_str, barco->arrival_time, barco->remaining_time, barco->deadline, barco->priority);
}