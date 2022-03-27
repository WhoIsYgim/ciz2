make_minimum_required(VERSION 3.16.3)

project(ciz2 C CXX)

set(CMAKE_C_STANDARD 99)



add_executable(main main.c)

add_subdirectory(src)