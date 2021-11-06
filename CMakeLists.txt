cmake_minimum_required(VERSION 3.20)
project(itba_progra1_tp12 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(itba_progra1_tp12
        pin_handler.c
        pin_handler.h led.c led.h)
