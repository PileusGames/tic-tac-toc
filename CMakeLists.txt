cmake_minimum_required(VERSION 3.25)
project(tic_tac_toc C)

set(CMAKE_C_STANDARD 11)

add_executable(tic_tac_toc src/main.c src/domain/grid/Grid.c src/exposition/cli/CLI.c src/exposition/dto/Init.c)


add_executable(test_grid
        tests/domain/grid/GridTest.c
        src/domain/grid/Grid.h src/domain/grid/Grid.c)

add_executable(test_jsmn
        tests/lib/jsmn/jsmnTest.c)

add_executable(test_init
        tests/exposition/init/InitTest.c
        src/exposition/dto/Init.c lib/jsmn.c)

add_executable(test_cli
        tests/exposition/cli/CliTest.c
        src/exposition/cli/CLI.c
        src/domain/grid/Grid.c
        src/exposition/dto/Init.c
        lib/jsmn.c)