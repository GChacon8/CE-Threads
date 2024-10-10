cmake_minimum_required(VERSION 3.29)
project(Calendarizacion C)

set(CMAKE_C_STANDARD 11)

add_executable(Calendarizacion main.c
        Libs/PROCESS/PROCESS.c
        Libs/PROCESS/PROCESS.h
        Libs/Calendars/fcfs.c
        Libs/Calendars/fcfs.h
        Libs/Calendars/priority.cpp
        Libs/Calendars/priority.h)
