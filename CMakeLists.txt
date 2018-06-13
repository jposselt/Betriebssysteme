cmake_minimum_required(VERSION 3.10)
project(Synchronisation C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(synchronize main.c queue.h miniz.h miniz.c tools.c tools.h threads.h threads.c mutexQueue.h mutexQueue.c queue.c)