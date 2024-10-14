#include <stdio.h>
#include "Libs/PROCESS/PROCESS.h"
#include "Libs/Calendars/Calendars.h"

int main(void)
{
    struct Process procesess[3];

    procesess[0] = create_process(1,Pesquero,2,10,20);
    procesess[1] = create_process(2,Normal,2,10,20);
    procesess[2] = create_process(3,Pesquero,5,15,30);

    priority(procesess,2);
    print_results(procesess,3);
}

