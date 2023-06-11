
//
// Created by Theo OMNES on 11/06/2023.
//

#include "Grid.h"

Grid emptyGrid() {
    Grid new = {
        {
            {_,_,_},
            {_,_,_},
            {_,_,_}
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
    return X;
}