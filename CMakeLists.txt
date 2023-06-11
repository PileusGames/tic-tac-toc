cmake_minimum_required(VERSION 3.25)
project(tic_tac_toc C)

set(CMAKE_C_STANDARD 11)

add_executable(tic_tac_toc src/main.c src/domain/grid/Grid.h src/domain/grid/Grid.c)


add_executable(test
        tests/domain/grid/GridTest.c
        src/domain/grid/Grid.h src/domain/grid/Grid.c)
