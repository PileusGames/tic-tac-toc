
//
// Created by Theo OMNES on 11/06/2023.
//

#include <stdlib.h>
#include "CLI.h"
#include "stdio.h"
#include "json-instruction/json-instruction.h"
#define JSMN_HEADER
#include "../json/json.h"
#include "../dto/actions.h"
#include "json-action/json-action.h"
#include "json-init/json-init.h"

char markToChar(Mark m);
void printGrid(Grid g);
Grid applyActionOnGrid(Action action, Grid grid);

CLI newCLI(Grid grid) {
    CLI cli = {grid, NO_ERROR};
    return cli;
}

CLI start(CLI cli) {
    if(!isError(cli.error)) {
        char* instruction = buildInstructionForGrid(cli.grid);
        fputs(instruction, stdout);
        fputc('\n', stdout);
        free(instruction);
    }

    ActionParseResult result = listenPlayerAction(cli.grid.currentPlayer, stdin);
    if(isError(result.error)) {
        fprintf(stdout, "Error: %d\n", result.error);
        return start((CLI) {cli.grid, result.error});
    }

    Grid gridNextTurn = applyActionOnGrid(result.action, cli.grid);

    if(isGameOver(gridNextTurn)) {
        char* finalInstruction = buildInstructionForGrid(gridNextTurn);
        fputs(finalInstruction, stdout);
        free(finalInstruction);
        return (CLI){gridNextTurn};
    } else {
        CLI cliNextTurn = {gridNextTurn};
        return start(cliNextTurn);
    }
}


InitParseResult init(FILE* stream) {
    char* request = readJson(stream);
    InitParseResult result = fromJson(request);

    free(request);
    return result;
}

Grid applyActionOnGrid(Action action, Grid grid) {
    grid = placeOnGrid(grid, action.player, action.x, action.y);
    grid = switchPlayer(grid);
    return grid;
}


void printGrid(Grid g) {
    printf(" %c | %c | %c \n"
            "---+---+---\n"
           " %c | %c | %c \n"
            "---+---+---\n"
           " %c | %c | %c \n",
           markToChar(g.marks[0][0]), markToChar(g.marks[0][1]), markToChar(g.marks[0][2]),
           markToChar(g.marks[1][0]), markToChar(g.marks[1][1]), markToChar(g.marks[1][2]),
           markToChar(g.marks[2][0]), markToChar(g.marks[2][1]), markToChar(g.marks[2][2])
           );
}

char markToChar(Mark m) {
    switch (m) {
        case EMPTY: return ' ';
        case X: return 'X';
        case O: return 'O';
    }
}