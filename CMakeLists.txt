cmake_minimum_required(VERSION 3.10)
project(Scheduler)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

include_directories(.)

add_executable(scheduler
        global.c
        global.h
        lists.c
        lists.h
        main.c)