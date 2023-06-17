#include <stdio.h>
#include "exposition/cli/CLI.h"



int main(int argc, char* argv[]) {
    Grid grid = emptyGrid(X);
    CLI cli = newCLI(grid);

    InitParseResult initResult = init(stdin);

    if(initResult.error == NO_ERROR) start(cli);
    else printf("ERROR: %d\n", initResult.error);
    return 0;
}
