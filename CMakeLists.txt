cmake_minimum_required(VERSION 3.25)
project(tic_tac_toc C)

set(CMAKE_C_STANDARD 11)
enable_testing()

if(MSVC)
    set(app_compile_options "/W4 /WX")
else()
    set(app_compile_options "-Wall")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(tic_tac_toc
        src/main.c
        src/domain/grid/Grid.c
        src/exposition/cli/CLI.c
        src/exposition/cli/json-init/json-init.c
        lib/jsmn.c
        src/exposition/cli/json-instruction/json-instruction.c
        src/utils/string-utils.c
        src/exposition/json/json.c
        src/exposition/cli/json-action/json-action.c
        src/exposition/error/errors.c)

# --------

add_executable(test_grid
        tests/domain/grid/GridTest.c
        src/domain/grid/Grid.h src/domain/grid/Grid.c)
add_test(NAME test_grid COMMAND test_grid)

add_executable(test_jsmn
        tests/lib/jsmn/jsmnTest.c)
add_test(NAME test_jsmn COMMAND test_jsmn)

add_executable(test_json_init
        src/exposition/cli/json-init/json-init.c)
add_test(NAME test_json_init COMMAND test_json_init)

add_executable(test_cli
        tests/exposition/CliTest.c
        src/exposition/cli/CLI.c
        src/exposition/cli/json-instruction/json-instruction.c
        src/utils/string-utils.c
        src/exposition/json/json.c
        src/exposition/cli/json-init/json-init.c
        src/domain/grid/Grid.c
        src/exposition/error/errors.h)
add_test(NAME test_cli COMMAND test_cli)
