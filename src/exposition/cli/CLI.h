
//
// Created by Theo OMNES on 11/06/2023.
//

#ifndef TIC_TAC_TOC_CLI_H
#define TIC_TAC_TOC_CLI_H

#include "../../domain/grid/Grid.h"

typedef struct CLI {
    Grid grid;
} CLI;

CLI newCLI(Grid grid);
CLI start(CLI cli);

#endif //TIC_TAC_TOC_CLI_H
