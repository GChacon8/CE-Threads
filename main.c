#define _GNU_SOURCE //Importante para el clone()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Para sleep()
#include "Calendarizacion/Libs/Calendars/Calendars.h"
#include "CEThreads/CEthreads.h"  // CEthreads
#include "CEThreads/CEthreads.c"  // CEthreads

int main() {

   int pesqueros_L;
   int patrullas_L; //Barcos Left
   int normales_L;

   int pesqueros_R;
   int patrullas_R; //Barcos Left
   int normales_R;

   int alg_canal; //Algoritmo de canal 1.Equidad 2.Letrero 3.Tico
   int intervalo; //Intervalo para el letrero
   int W; //Numero de barcos para equidad

   int calendarizador;

   
   printf("Ingrese la cantidad de barcos NORMALES a la IZQUIERDA del canal: ");
   scanf("%d", &normales_L);

   printf("Ingrese la cantidad de barcos PESQUEROS a la IZQUIERDA del canal: ");
   scanf("%d", &pesqueros_L);

   printf("Ingrese la cantidad de barcos PATRULLA a la IZQUIERDA del canal: ");
   scanf("%d", &normales_L);

   printf("Ingrese la cantidad de barcos NORMALES a la IZQUIERDA del canal: ");
   scanf("%d", &normales_R);

   printf("Ingrese la cantidad de barcos PESQUEROS a la IZQUIERDA del canal: ");
   scanf("%d", &pesqueros_R);

   printf("Ingrese la cantidad de barcos PATRULLA a la IZQUIERDA del canal: ");
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
   printf("Seleccione el calendarizador deseado:\n1.EDFS\n2.FCFS\n3.Priority\n4.RR\n5.SJF");
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
   printf("Ingrese el algoritmo de canal deseado:\n1.Equidad\n2.Letrero\n3.Tico");
   scanf("%d", &alg_canal);

   return 0;
}