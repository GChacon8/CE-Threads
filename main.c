#define _GNU_SOURCE //Importante para el clone()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Para sleep()
#include <limits.h>
#include "Calendarizacion/Libs/Calendars/edfs.c"
#include "Calendarizacion/Libs/Calendars/fcfs.c"
#include "Calendarizacion/Libs/Calendars/priority.c"
#include "Calendarizacion/Libs/Calendars/Round_Robin.c"
#include "Calendarizacion/Libs/Calendars/SJF.c"
#include "CEThreads/CEthreads.h"  // CEthreads
#include "CEThreads/CEthreads.c"  // CEthreads


// Equidad
void equidad(struct Node* barcos_L, struct Node* barcos_R) {
    
}

void letrero(struct Node* barcos_L, struct Node* barcos_R) {
    
}

void tico(struct Node* barcos_L, struct Node* barcos_R) {
    
}


int main() {

   int pesqueros_L;
   int patrullas_L; //Barcos Left
   int normales_L;

   int pesqueros_R;
   int patrullas_R; //Barcos Left
   int normales_R;

   int calendarizador; //Calendarizador a escoger

   int alg_canal; //Algoritmo de canal 1.Equidad 2.Letrero 3.Tico
   int intervalo; //Intervalo para el letrero
   int W; //Numero de barcos para equidad

   CEmutex canal_mutex; //Control de recursos

   
   printf("Ingrese la cantidad de barcos NORMALES a la IZQUIERDA del canal: ");
   scanf("%d", &normales_L);

   printf("Ingrese la cantidad de barcos PESQUEROS a la IZQUIERDA del canal: ");
   scanf("%d", &pesqueros_L);

   printf("Ingrese la cantidad de barcos PATRULLA a la IZQUIERDA del canal: ");
   scanf("%d", &normales_L);

   printf("Ingrese la cantidad de barcos NORMALES a la DERECHA del canal: ");
   scanf("%d", &normales_R);

   printf("Ingrese la cantidad de barcos PESQUEROS a la DERECHA del canal: ");
   scanf("%d", &pesqueros_R);

   printf("Ingrese la cantidad de barcos PATRULLA a la DERECHA del canal: ");
   scanf("%d", &normales_R);


   //Creamos las listas de la izquierda y la derecha
   struct Node* barcos_L = NULL;
   struct Node* barcos_R = NULL;
    

   //Creamos los diferentes barcos y los appendiamos a las listas correspondientes
   for (int i = 0; i < normales_L; i++)
   {
      append_node(&barcos_L, create_process(i+1,Normal,5,10,20));
   }

   for (int i = 0; i < pesqueros_L; i++)
   {
      append_node(&barcos_L, create_process(i+1,Pesquero,5,10,20));
   }

   for (int i = 0; i < patrullas_L; i++)
   {
      append_node(&barcos_L, create_process(i+1,Patrulla,5,10,20));
   }

   for (int i = 0; i < normales_L; i++)
   {
      append_node(&barcos_L, create_process(i+1,Normal,5,10,20));
   }

   for (int i = 0; i < pesqueros_L; i++)
   {
      append_node(&barcos_L, create_process(i+1,Pesquero,5,10,20));
   }

   for (int i = 0; i < patrullas_L; i++)
   {
      append_node(&barcos_L, create_process(i+1,Patrulla,5,10,20));
   }
    
   // Se pide el algoritmo de canal deseado.
   printf("Seleccione el calendarizador deseado:\n1.EDFS\n2.FCFS\n3.Priority\n4.RR\n5.SJF\n\nRespuesta: ");
   scanf("%d", &calendarizador);

   switch (calendarizador)
   {
   case 1:
      edfs(barcos_L);
      edfs(barcos_R);
      print_process_list(barcos_L);
      print_process_list(barcos_R);
      break;
   
   case 2:
      fcfs(barcos_L);
      fcfs(barcos_R);
      print_process_list(barcos_L);
      print_process_list(barcos_R);
      break;
   
   case 3:
      priority(barcos_L);
      priority(barcos_R);
      print_process_list(barcos_L);
      print_process_list(barcos_R);
      break;
   
   case 4:
      round_robin(barcos_L);
      round_robin(barcos_R);
      print_process_list(barcos_L);
      print_process_list(barcos_R);
      break;
   
   case 5:
      SJF(barcos_L);
      SJF(barcos_R);
      print_process_list(barcos_L);
      print_process_list(barcos_R);
      break;

   default:
      edfs(barcos_L);
      edfs(barcos_R);
      print_process_list(barcos_L);
      print_process_list(barcos_R);
      break;
   }

   // Se pide el algoritmo de canal deseado.
   printf("Ingrese el algoritmo de canal deseado:\n1.Equidad\n2.Letrero\n3.Tico\n\nRespuesta: ");
   scanf("%d", &alg_canal);

   // Inicializa el mutex
   CEmutex_init(&canal_mutex);

   switch (alg_canal)
   {
   case 1:
      equidad(barcos_L,barcos_R);
      break;
   
   case 2:
      letrero(barcos_L,barcos_R);
      break;
   
   case 3:
      tico(barcos_L,barcos_R);
      break;
   
   default:
      equidad(barcos_L,barcos_R);
      break;
   }

   

   return 0;
}