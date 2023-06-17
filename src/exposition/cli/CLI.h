
//
// Created by Theo OMNES on 11/06/2023.
//

#ifndef TIC_TAC_TOC_CLI_H
#define TIC_TAC_TOC_CLI_H

#include <stdio.h>
#include "../../domain/grid/Grid.h"
#include "../dto/Init.h"
#include "../../utils/string-utils.h"

#define MAX_LINE_SIZE 50
#define MAX_OUTPUT_SIZE 255


#define IN stdin


typedef struct CLI {
    Grid grid;
    enum Error error;
} CLI;

CLI newCLI(Grid grid);
CLI start(CLI cli);
InitParseResult init(FILE* stream);

#endif //TIC_TAC_TOC_CLI_H
