#define _GNU_SOURCE //Importante para el clone()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Para sleep()
#include <limits.h>
#include <stdbool.h>
#include "Calendarizacion/Libs/Calendars/edfs.h"
#include "Calendarizacion/Libs/Calendars/fcfs.h"
#include "Calendarizacion/Libs/Calendars/priority.h"
#include "Calendarizacion/Libs/Calendars/Round_Robin.h"
#include "Calendarizacion/Libs/Calendars/SJF.h"
#include "CEThreads/CEthreads.h"  // CEthreads
#include "ArdCom/Libs/serial_com.h"
char command[100];
char response[100];
int fd;

void *cruzar_canal(void *arg){

   int sleeper = *(int *)arg;
   int sleep_time = 5 + 5*sleeper;

   printf("Este proceso va a durar %d segs pasando\n", sleep_time);

   sleep(sleep_time);

   return NULL;
}

// Equidad
void equidad(struct Node* barcos_L, struct Node* barcos_R) {
   int W;
   bool finish_L = true;
   bool finish_R = true;
   // Se pide el algoritmo de canal deseado.
   printf("Ingrese el valor W para el algoritmo de equidad: ");
   scanf("%d", &W);

   while (finish_L || finish_R)
   {
      for (int i = 0; i < W; i++)
   {
      if (isEmpty(barcos_L)==0)
      {
         struct CEthread current_process = dequeue(&barcos_L);
         printf("Hilo va a pasar el canal de izquierda a derecha\n");
         switch (current_process.arrival_time) {
            case 2:
               strcpy(command, "normal_izq_on");
               enviarComando(fd, command);
               break;
            case 1:
               strcpy(command,"pesquero_izq_on"); enviarComando(fd,command); break;
            case 0:
               strcpy(command,"patrulla_izq_on"); enviarComando(fd,command); break;
         }
         sleep(4);
         print_process(&current_process);
         CEthread_create(&current_process, cruzar_canal, &(current_process.arrival_time));
         CEthread_join(&current_process);
         switch (current_process.arrival_time) {
            case 2:
               strcpy(command, "normal_izq_off");
            enviarComando(fd, command);
            break;
            case 1:
               strcpy(command,"pesquero_izq_off"); enviarComando(fd,command); break;
            case 0:
               strcpy(command,"patrulla_izq_off"); enviarComando(fd,command); break;
         }
         sleep(4);
         CEthread_end(&current_process);

      }
      else{
         finish_L = false;
         break;
      }
   }

   for (int j = 0; j < W; j++)
   {
      if (isEmpty(barcos_R)==0)
      {
         struct CEthread current_process = dequeue(&barcos_R);
         printf("Hilo va a pasar el canal de derecha a izquierda\n");
         switch (current_process.arrival_time) {
            case 2:
               strcpy(command, "normal_der_on");
            enviarComando(fd, command);
            break;
            case 1:
               strcpy(command,"pesquero_der_on"); enviarComando(fd,command); break;
            case 0:
               strcpy(command,"patrulla_der_on"); enviarComando(fd,command); break;
         }
         sleep(4);
         print_process(&current_process);
         CEthread_create(&current_process, cruzar_canal, &(current_process.arrival_time));
         CEthread_join(&current_process);
         switch (current_process.arrival_time) {
            case 2:
               strcpy(command, "normal_der_off"); enviarComando(fd, command); break;
            case 1:
               strcpy(command,"pesquero_der_off"); enviarComando(fd,command); break;
            case 0:
               strcpy(command,"patrulla_der_off"); enviarComando(fd,command); break;
         }
         sleep(4);
         CEthread_end(&current_process);
      }

      else{
         finish_R = false;
         break;
      }
   }


   }
    
}

void letrero(struct Node* barcos_L, struct Node* barcos_R) {
   int intervalo;
   bool finish_L = true;
   bool finish_R = true;
   int timer = 0;

   // Se pide el algoritmo de canal deseado.
   printf("Ingrese el tiempo de letrero en segundos: ");
   scanf("%d", &intervalo);

   while (finish_L || finish_R){
      while (timer<intervalo)
      {
         if (isEmpty(barcos_L)==0)
      {
         struct CEthread current_process = dequeue(&barcos_L);
         printf("Hilo va a pasar el canal de izquierda a derecha\n");
            switch (current_process.arrival_time) {
               case 2:
                  strcpy(command, "normal_izq_on");
               enviarComando(fd, command);
               break;
               case 1:
                  strcpy(command,"pesquero_izq_on"); enviarComando(fd,command); break;
               case 0:
                  strcpy(command,"patrulla_izq_on"); enviarComando(fd,command); break;
            }
            sleep(4);
         print_process(&current_process);
         CEthread_create(&current_process, cruzar_canal, &(current_process.arrival_time));
         CEthread_join(&current_process);
         timer = timer + 5 + 5*(current_process.arrival_time);
            switch (current_process.arrival_time) {
               case 2:
                  strcpy(command, "normal_izq_off");
               enviarComando(fd, command);
               break;
               case 1:
                  strcpy(command,"pesquero_izq_off"); enviarComando(fd,command); break;
               case 0:
                  strcpy(command,"patrulla_izq_off"); enviarComando(fd,command); break;
            }
            sleep(4);
         CEthread_end(&current_process);
      }

      else{
         finish_L = false;
         break;
      }
      }

      printf("\nCambio de lado por cambio de letrero\n");
      timer = 0;

      while (timer<intervalo)
      {
         printf("Cambio de lado por cambio de letrero");
         if (isEmpty(barcos_R)==0)
      {
         struct CEthread current_process = dequeue(&barcos_R);
            switch (current_process.arrival_time) {
               case 2:
                  strcpy(command, "normal_der_on");
               enviarComando(fd, command);
               break;
               case 1:
                  strcpy(command,"pesquero_der_on"); enviarComando(fd,command); break;
               case 0:
                  strcpy(command,"patrulla_der_on"); enviarComando(fd,command); break;
            }
            sleep(4);
         printf("Hilo va a pasar el canal de derecha a izquierda\n");
         print_process(&current_process);
         CEthread_create(&current_process, cruzar_canal, &(current_process.arrival_time));
         CEthread_join(&current_process);
         timer = timer + 5 + 5*(current_process.arrival_time);
            switch (current_process.arrival_time) {
               case 2:
                  strcpy(command, "normal_der_off");
               enviarComando(fd, command);
               break;
               case 1:
                  strcpy(command,"pesquero_der_off"); enviarComando(fd,command); break;
               case 0:
                  strcpy(command,"patrulla_der_off"); enviarComando(fd,command); break;
            }
            sleep(4);
         CEthread_end(&current_process);
      }

      else{
         finish_R = false;
         break;
      }
      }
      printf("\nCambio de lado por cambio de letrero\n");
      timer = 0;
      
   }

}

void tico(struct Node* barcos_L, struct Node* barcos_R) {
   
   printf("Nada de momento");

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
   //int W; //Numero de barcos para equidad

   //Iniciar comunicacion serial
   fd = iniciarComunicacion("/dev/ttyACM0");
   if (fd==-1) {
      return 1;
   }

   CEmutex canal_mutex; //Control de recursos

   
   printf("Ingrese la cantidad de barcos NORMALES a la IZQUIERDA del canal: ");
   scanf("%d", &normales_L);

   printf("Ingrese la cantidad de barcos PESQUEROS a la IZQUIERDA del canal: ");
   scanf("%d", &pesqueros_L);

   printf("Ingrese la cantidad de barcos PATRULLA a la IZQUIERDA del canal: ");
   scanf("%d", &patrullas_L);

   printf("Ingrese la cantidad de barcos NORMALES a la DERECHA del canal: ");
   scanf("%d", &normales_R);

   printf("Ingrese la cantidad de barcos PESQUEROS a la DERECHA del canal: ");
   scanf("%d", &pesqueros_R);

   printf("Ingrese la cantidad de barcos PATRULLA a la DERECHA del canal: ");
   scanf("%d", &patrullas_R);


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

   for (int i = 0; i < normales_R; i++)
   {
      append_node(&barcos_R, create_process(i+1,Normal,5,10,20));
   }

   for (int i = 0; i < pesqueros_R; i++)
   {
      append_node(&barcos_R, create_process(i+1,Pesquero,5,10,20));
   }

   for (int i = 0; i < patrullas_R; i++)
   {
      append_node(&barcos_R, create_process(i+1,Patrulla,5,10,20));
   }
    
   // Se pide el algoritmo de canal deseado.
   printf("Seleccione el calendarizador deseado:\n1.EDFS\n2.FCFS\n3.Priority\n4.RR\n5.SJF\n\nRespuesta: ");
   scanf("%d", &calendarizador);

   switch (calendarizador)
   {
   case 1:
      edfs(barcos_L);
      edfs(barcos_R);
      printf("La lista izquierda es:\n");
      print_process_list(barcos_L);
      printf("La lista derecha es:\n");
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