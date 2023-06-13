#include <stdio.h>
#include "domain/grid/Grid.h"
#include "exposition/cli/CLI.h"



int main(int argc, char* argv[]) {
    //Grid grid = emptyGrid();
    //CLI cli = newCLI(grid);

    InitParseResult initResult = init(stdin);

    printf("players: %d\n", initResult.init.players);

    return 0;
}
