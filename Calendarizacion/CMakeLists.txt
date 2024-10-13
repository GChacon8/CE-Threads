cmake_minimum_required(VERSION 3.29)
project(Calendarizacion C)

set(CMAKE_C_STANDARD 11)

add_executable(Calendarizacion main.c
        Libs/PROCESS/PROCESS.c
        Libs/PROCESS/PROCESS.h
        Libs/Calendars/fcfs.c
        Libs/Calendars/fcfs.h
        Libs/Calendars/priority.c
        Libs/Calendars/priority.h
        Libs/Calendars/SJF.c
        Libs/Calendars/SJF.h
        Libs/Calendars/Round_Robin.c
        Libs/Calendars/Round_Robin.h
        Libs/Queue/queue.c
        Libs/Queue/queue.h
        Libs/Calendars/edfs.c
        Libs/Calendars/edfs.h
        Libs/Calendars/Calendars.h)
