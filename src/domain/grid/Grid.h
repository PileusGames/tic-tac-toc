
//
// Created by Theo OMNES on 11/06/2023.
//

#ifndef TIC_TAC_TOC_GRID_H
#define TIC_TAC_TOC_GRID_H

#include "../mark/Mark.h"
#include "stdbool.h"


struct Grid {
    Mark marks[3][3];
};

typedef struct Grid Grid;

Grid emptyGrid();
bool gridsAreEquals(Grid a, Grid b);
Mark getWinner(Grid grid);

#endif //TIC_TAC_TOC_GRID_H