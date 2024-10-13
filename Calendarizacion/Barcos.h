#ifndef BARCO_H
#define BARCO_H

#include "CEThreads/CEthreads.h"


typedef enum {
    NORMAL,
    PESQUERO,
    PATRULLA
} TipoBarco;

// Estructura de Barco
typedef struct Barco {
    int pid;
    TipoBarco tipo;       // Tipo de Barco
    float arrival_time;      // VELOCIDAD a la que se genera
    int remaining_time;  // Para Round Robin
    int deadline;         // Para el algoritmo de Tiempo Real
    int priority;        // Para el algoritmo de prioridad
    struct Barco *siguiente; // Puntero para listas enlazadas (si es necesario en otras partes del sistema)
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int is_completed;


} Barco;

// Prototipos de funciones
void instanciarBarcos(Barco* barco, int id, TipoBarco tipo, int longitud_canal); // Función para inicializar un barco
void barcosInfo(const Barco* barco); // Función para mostrar información del barco

#endif // BARCO_H