cmake_minimum_required(VERSION 3.20)
project(Trabalho_P1 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -lm -O3")
add_executable(Trabalho_P1 subset_sum_problem.c SchroeppelShamirs.c)
