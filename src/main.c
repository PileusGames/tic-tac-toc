#include <stdio.h>
#include "exposition/dto/Instruction.h"
#include "exposition/cli/CLI.h"



int main(int argc, char* argv[]) {
    Grid grid = emptyGrid();
    //CLI cli = newCLI(grid);

    InitParseResult initResult = init(stdin);

    if(initResult.error == NO_ERROR) printf("%s", getInstructionForGrid(grid));
    else printf("ERROR: %d\n", initResult.error);

    return 0;
}
