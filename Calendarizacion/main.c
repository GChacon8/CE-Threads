#include <stdio.h>
#include "Libs/PROCESS/PROCESS.h"
#include "Libs/Calendars/Calendars.h"

int main(void){
    struct Node* procesess = NULL;

    append_node(&procesess, create_process(1,Patrulla,5,10,20));
    append_node(&procesess, create_process(2,Normal,2,15,30));
    append_node(&procesess, create_process(3,Pesquero,5,20,40));

    edfs(procesess);
    print_process_list(procesess);

}

