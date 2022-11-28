cmake_minimum_required(VERSION 3.23)
project(173_Proj4 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Werror)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(173_Proj4 main.c Part1.h Part1.c)
