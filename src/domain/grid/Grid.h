
//
// Created by Theo OMNES on 11/06/2023.
//

#ifndef TIC_TAC_TOC_GRID_H
#define TIC_TAC_TOC_GRID_H

#include "../mark/Mark.h"
#include "stdbool.h"
#include "inttypes.h"


typedef struct Grid {
    Mark marks[3][3];
} Grid;

Grid emptyGrid();
bool gridsAreEquals(Grid a, Grid b);
Mark getWinner(Grid grid);
Grid placeOnGrid(Grid grid, Mark mark, int8_t x, int8_t y);
bool gridIsFull(Grid grid);

#endif //TIC_TAC_TOC_GRID_H