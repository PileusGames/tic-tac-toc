
//
// Created by Theo OMNES on 11/06/2023.
//

#include <stdlib.h>
#include "Grid.h"

// --- Private functions
bool isTheWinner(Grid grid, enum Mark mark);
// --- Private functions


Grid emptyGrid(Mark startPlayer) {
    Grid new = {
            startPlayer,
        {
            {EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY}
        }
    };

    return new;
}

bool gridsAreEquals(Grid a, Grid b) {
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            if(a.marks[x][y] != b.marks[x][y]) return false;
        }
    }
    return true;
}

Mark getWinner(Grid grid) {
    if(isTheWinner(grid, X)) return X;
    if(isTheWinner(grid, O)) return O;
    return EMPTY;
}

bool isTheWinner(Grid g, Mark mark) {

    //lines
    if(g.marks[0][0] == mark && g.marks[0][1] == mark && g.marks[0][2] == mark) return true;
    if(g.marks[1][0] == mark && g.marks[1][1] == mark && g.marks[1][2] == mark) return true;
    if(g.marks[2][0] == mark && g.marks[2][1] == mark && g.marks[2][2] == mark) return true;

    //columns
    if(g.marks[0][0] == mark && g.marks[1][0] == mark && g.marks[2][0] == mark) return true;
    if(g.marks[0][1] == mark && g.marks[1][1] == mark && g.marks[2][1] == mark) return true;
    if(g.marks[0][2] == mark && g.marks[1][2] == mark && g.marks[2][2] == mark) return true;

    //diagonals
    if(g.marks[0][0] == mark && g.marks[1][1] == mark && g.marks[2][2] == mark) return true;
    if(g.marks[0][2] == mark && g.marks[1][1] == mark && g.marks[2][0] == mark) return true;

    return false;
}

Grid placeOnGrid(Grid grid, Mark mark, int8_t x, int8_t y) {
    if(mark == EMPTY) return grid;
    if(x < 0 || x > 2 || y < 0 || y > 2) return grid;
    if(grid.marks[x][y] != EMPTY) return grid;

    grid.marks[x][y] = mark;
    return grid;
}

bool gridIsFull(Grid grid) {
    for(int x = 0; x < 3; x ++) {
        for(int y = 0; y < 3; y ++) {
            if(grid.marks[x][y] == EMPTY) return false;
        }
    }
    return true;
}

bool isGameOver(Grid grid) {
    return getWinner(grid) || gridIsFull(grid);
}

Grid switchPlayer(Grid grid) {
    if(grid.currentPlayer == EMPTY) return grid;
    Mark nextPlayer = grid.currentPlayer == X ? O : X;
    grid.currentPlayer = nextPlayer;
    return grid;
}