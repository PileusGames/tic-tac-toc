
//
// Created by Theo OMNES on 11/06/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "../../minunit.h"
#include "../../../src/domain/grid/Grid.h"

int tests_run = 0;

static char * test_should_create_new_empty_grid() {
    Grid empty = {
            {
                    {_,_,_},
                    {_,_,_},
                    {_,_,_}
            }
    };

    Grid new = emptyGrid();
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            char *msg = malloc(sizeof(char) * 64);
            sprintf(msg, "error, emptyGrid[%d][%d] is not empty", x, y);
            mu_assert(msg, empty.marks[x][y] == new.marks[x][y]);
        }
    }
    return 0;
}

static char * test_gridsAreEquals_should_return_true() {
    Grid a = {
            {
                    {X,O,_},
                    {_,O,_},
                    {_,_,X}
            }
    };

    Grid b = {
            {
                    {X,O,_},
                    {_,O,_},
                    {_,_,X},
            }
    };
    mu_assert("error, grids should be equal", gridsAreEquals(a,b));
    return 0;
}

static char * test_gridsAreEquals_should_return_false() {
    Grid a = {
            {
                    {_,O,_},
                    {_,_,_},
                    {_,_,_},
            }
    };

    Grid b = {
            {
                    {_,X,_},
                    {_,_,_},
                    {_,_,_},
            }
    };
    mu_assert("error, grids should be different", !gridsAreEquals(a,b));
    return 0;
}

static char * test_should_get_winner_X() {
    Grid grid = {
            {
                    {X,X,X},
                    {_,_,_},
                    {_,_,_},
            }
    };
    mu_assert("error, X should be the winner", getWinner(grid) == X);
    return 0;
}

static char * all_tests() {
    mu_run_test(test_should_create_new_empty_grid);
    mu_run_test(test_gridsAreEquals_should_return_true);
    mu_run_test(test_gridsAreEquals_should_return_false);
    mu_run_test(test_should_get_winner_X);

    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}