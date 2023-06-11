#include <stdio.h>
#include "domain/grid/Grid.h"
#include "exposition/cli/CLI.h"



int main(int argc, char* argv[]) {
    printf("Tic Tac Toc\n");

    Grid grid = emptyGrid();
    CLI cli = newCLI(grid);

    start(cli);

    return 0;
}
