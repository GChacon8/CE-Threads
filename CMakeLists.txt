cmake_minimum_required(VERSION 3.29)
project(CE_Threads)

set(CMAKE_CXX_STANDARD 14)

include_directories(ArdCom/Libs)
include_directories("ArdCom/SetupHardware(Arduino)")
include_directories("ArdCom/SetupHardware(Arduino)/SetupHardware")
include_directories(Calendarizacion/Libs/Calendars)
include_directories(CEThreads)

add_executable(CE_Threads
    ArdCom/Libs/serial_com.c
    ArdCom/Libs/serial_com.h
    "ArdCom/SetupHardware(Arduino)/SetupHardware/SetupHardware.ino"
        Calendarizacion/Libs/Calendars/edfs.c
    Calendarizacion/Libs/Calendars/edfs.h
    Calendarizacion/Libs/Calendars/fcfs.c
    Calendarizacion/Libs/Calendars/fcfs.h
    Calendarizacion/Libs/Calendars/priority.c
    Calendarizacion/Libs/Calendars/priority.h
    Calendarizacion/Libs/Calendars/Round_Robin.c
    Calendarizacion/Libs/Calendars/Round_Robin.h
    Calendarizacion/Libs/Calendars/SJF.c
    Calendarizacion/Libs/Calendars/SJF.h
    CEThreads/CEthreads.c
    CEThreads/CEthreads.h
    main.c)
