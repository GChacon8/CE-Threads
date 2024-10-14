#include <stdio.h>
#include "Libs/PROCESS/PROCESS.h"
#include "Libs/Calendars/Calendars.h"
#include <glib-2.0/glib.h>

int main(void){
    struct Node* procesess = NULL;

    append_node(&procesess, create_process(1,Normal,5,10,20));
    append_node(&procesess, create_process(2,Pesquero,2,15,30));
    append_node(&procesess, create_process(3,Patrulla,5,20,40));
    Glist *list = NULL;

    list = g_list_append(list,create_process(1,Normal,5,10,20));
    list = g_list_append(list,create_process(2,Normal,2,15,20));
    list = g_list_append(list,create_process(3,Normal,3,20,20));

    SJF(list, g_list_length(list));
    for (GList *1 = list; 1!=NULL;1->next) {
        printf("%s",(char *)1->data);
    }
    g_list_free(list);

}