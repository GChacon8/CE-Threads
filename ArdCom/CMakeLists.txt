cmake_minimum_required(VERSION 3.29)
project(ArdCom C)

set(CMAKE_C_STANDARD 11)

add_executable(ArdCom main.c
        Libs/serial_com.h
        Libs/serial_com.c)
