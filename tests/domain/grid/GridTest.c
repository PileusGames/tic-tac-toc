
//
// Created by Theo OMNES on 11/06/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "../../minunit.h"
#include "../../../src/domain/grid/Grid.h"

int tests_run = 0;

static char * test_should_create_new_empty_grid() {
    struct Grid empty = {EMPTY,
                         {
                    {EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY}
            }
    };

    Grid new = emptyGrid(X);
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            char *msg = malloc(sizeof(char) * 64);
            sprintf(msg, "error, emptyGrid[%d][%d] is not empty", x, y);
            mu_assert(msg, empty.marks[x][y] == new.marks[x][y]);
            free(msg);
        }
    }
    return EXIT_SUCCESS;
}

static char * test_gridsAreEquals_should_return_true() {
    Grid a = {EMPTY,
              {
                    {X, O, EMPTY},
                    {EMPTY, O, EMPTY},
                    {EMPTY, EMPTY, X}
            }
    };

    Grid b = {EMPTY,
              {
                    {X, O, EMPTY},
                    {EMPTY, O, EMPTY},
                    {EMPTY, EMPTY, X},
            }
    };
    mu_assert("error, grids should be equal", gridsAreEquals(a,b));
    return EXIT_SUCCESS;
}

static char * test_gridsAreEquals_should_return_false() {
    Grid a = {EMPTY,
              {
                    {EMPTY, O, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
            }
    };

    Grid b = {EMPTY,
              {
                    {EMPTY, X, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
            }
    };
    mu_assert("error, grids should be different", !gridsAreEquals(a,b));
    return EXIT_SUCCESS;
}

static char * test_should_get_winner_X_first_line() {
    Grid grid = {EMPTY,
                 {
                    {X,X,X},
                    {EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
            }
    };
    mu_assert("error, X should be the winner at first line", getWinner(grid) == X);
    return EXIT_SUCCESS;
}

static char * test_should_get_winner_O_first_line() {
    Grid grid = {EMPTY,
                 {
                    {O,O,O},
                    {EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
            }
    };
    mu_assert("error, O should be the winner at first line", getWinner(grid) == O);
    return EXIT_SUCCESS;
}

static char * test_should_get_winner_X_second_line() {
    Grid grid = {EMPTY,
                 {
                    {EMPTY, EMPTY, EMPTY},
                    {X,X,X},
                    {EMPTY, EMPTY, EMPTY},
            }
    };
    mu_assert("error, X should be the winner at second line", getWinner(grid) == X);
    return EXIT_SUCCESS;
}

static char * test_should_get_winner_X_third_line() {
    Grid grid = {EMPTY,
                 {
                    {EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
                    {X,X,X},
            }
    };
    mu_assert("error, X should be the winner at third line", getWinner(grid) == X);
    return EXIT_SUCCESS;
}

static char * test_should_get_winner_X_first_column() {
    Grid grid = {EMPTY,
                 {
                    {X, EMPTY, EMPTY},
                    {X, EMPTY, EMPTY},
                    {X, EMPTY, EMPTY},
            }
    };
    mu_assert("error, X should be the winner at first column", getWinner(grid) == X);
    return EXIT_SUCCESS;
}

static char * test_should_get_winner_X_second_column() {
    Grid grid = {EMPTY,
                 {
                    {EMPTY, X, EMPTY},
                    {EMPTY, X, EMPTY},
                    {EMPTY, X, EMPTY},
            }
    };
    mu_assert("error, X should be the winner at second column", getWinner(grid) == X);
    return EXIT_SUCCESS;
}

static char * test_should_get_winner_X_third_column() {
    Grid grid = {EMPTY,
                 {
                    {EMPTY, EMPTY, X},
                    {EMPTY, EMPTY, X},
                    {EMPTY, EMPTY, X},
            }
    };
    mu_assert("error, X should be the winner at third column", getWinner(grid) == X);
    return EXIT_SUCCESS;
}

static char * test_should_get_winner_X_diagonal_up_left_corner_to_down_right_corner() {
    Grid grid = {EMPTY,
                 {
                    {X, EMPTY, EMPTY},
                    {EMPTY, X, EMPTY},
                    {EMPTY, EMPTY, X},
            }
    };
    mu_assert("error, X should be the winner at diagonal up left to down right", getWinner(grid) == X);
    return EXIT_SUCCESS;
}

static char * test_should_get_winner_X_diagonal_up_right_corner_to_down_left_corner() {
    Grid grid = {EMPTY,
                 {
                    {EMPTY, EMPTY, X},
                    {EMPTY, X, EMPTY},
                    {X, EMPTY, EMPTY},
            }
    };
    mu_assert("error, X should be the winner at diagonal up right to down left", getWinner(grid) == X);
    return EXIT_SUCCESS;
}

static char * test_should_place_X_at_0_0() {
    Grid empty = emptyGrid(X);
    Grid updatedGrid = placeOnGrid(empty, X, 0, 0);
    mu_assert("error, X should have been placed at [0,0]", updatedGrid.marks[0][0] == X);
    mu_assert("error, old grid should not have been updated", empty.marks[0][0] == EMPTY);
    return EXIT_SUCCESS;
}

static char * test_place_outside_grid_should_do_nothing() {
    Grid grid = {EMPTY,
                 {
                    {X, EMPTY, EMPTY},
                    {EMPTY, X, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
            }
    };
    Grid updatedGrid = placeOnGrid(grid, X, -1, 0);
    mu_assert("error, place outside should do nothing", gridsAreEquals(grid, updatedGrid));
    return EXIT_SUCCESS;
}

static char * test_place_EmptyMark_should_do_nothing() {
    Grid grid = {EMPTY,
                 {
                    {X, EMPTY, EMPTY},
                    {EMPTY, X, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
            }
    };
    Grid updatedGrid = placeOnGrid(grid, EMPTY, 0, 0);
    mu_assert("error, place EmptyMark should do nothing", updatedGrid.marks[0][0] == X);
    return EXIT_SUCCESS;
}

static char * test_place_on_already_played_space_should_do_nothing() {
    Grid grid = {EMPTY,
                 {
                    {X, EMPTY, EMPTY},
                    {EMPTY, X, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
            }
    };
    Grid updatedGrid = placeOnGrid(grid, O, 1, 1);
    mu_assert("error, place on other mark should do nothing", updatedGrid.marks[1][1] == X);
    return EXIT_SUCCESS;
}

static char * test_return_true_when_grid_is_full() {
    Grid grid = {EMPTY,
                 {
                    {X,O,X},
                    {O,X,O},
                    {O,X,O},
            }
    };
    mu_assert("error, grid should be full", gridIsFull(grid));
    return EXIT_SUCCESS;
}

static char* test_return_false_when_grid_is_not_full() {
    Grid grid = {EMPTY,
                 {
                    {X,O,X},
                    {O, EMPTY, O},
                    {O,X,O},
            }
    };
    mu_assert("error, grid should not be full", !gridIsFull(grid));
    return EXIT_SUCCESS;
}

static char* should_get_game_is_over_with_winner() {
    Grid gridWithXWinner = {EMPTY, {
                         {X,X,X},
                         {O, EMPTY, EMPTY},
                         {O, EMPTY, O},
                 }};

    mu_assert("error, game should be over", isGameOver(gridWithXWinner));
    return EXIT_SUCCESS;
}

static char* should_get_game_is_over_with_full_grid() {
    Grid fullGrid = {EMPTY, {
        {X,O,X},
        {O,X,O},
        {O,X,O},
        }};

    mu_assert("error, game should be over", isGameOver(fullGrid));
    return EXIT_SUCCESS;
}

static char * all_tests() {
    mu_run_test(test_should_create_new_empty_grid);
    mu_run_test(test_gridsAreEquals_should_return_true);
    mu_run_test(test_gridsAreEquals_should_return_false);
    mu_run_test(test_should_get_winner_X_first_line);
    mu_run_test(test_should_get_winner_O_first_line);
    mu_run_test(test_should_get_winner_X_second_line);
    mu_run_test(test_should_get_winner_X_third_line);
    mu_run_test(test_should_get_winner_X_first_column);
    mu_run_test(test_should_get_winner_X_second_column);
    mu_run_test(test_should_get_winner_X_third_column);
    mu_run_test(test_should_get_winner_X_diagonal_up_left_corner_to_down_right_corner);
    mu_run_test(test_should_get_winner_X_diagonal_up_right_corner_to_down_left_corner);
    mu_run_test(test_should_place_X_at_0_0);
    mu_run_test(test_place_outside_grid_should_do_nothing);
    mu_run_test(test_place_EmptyMark_should_do_nothing);
    mu_run_test(test_place_on_already_played_space_should_do_nothing);
    mu_run_test(test_return_true_when_grid_is_full);
    mu_run_test(test_return_false_when_grid_is_not_full);
    mu_run_test(should_get_game_is_over_with_winner);
    mu_run_test(should_get_game_is_over_with_full_grid);

    return EXIT_SUCCESS;
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

    return result != EXIT_SUCCESS;
}