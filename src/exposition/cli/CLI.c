
//
// Created by Theo OMNES on 11/06/2023.
//

#include "CLI.h"
#include "stdbool.h"
#include "stdio.h"

Mark charToMark(char c);
char markToChar(Mark m);
void printGrid(Grid g);

CLI newCLI(Grid grid) {
    CLI cli = {grid};
    return cli;
}

CLI start(CLI cli) {
    printGrid(cli.grid);
    int8_t x = -1;
    int8_t y = -1;
    char m = 0;
    scanf("%hhd %hhd %c", &x, &y, &m);
    fflush(stdin);

    Grid g = placeOnGrid(cli.grid, charToMark(m), x, y);
    CLI nextTurn = {g};
    if(gridIsFull(g) || getWinner(g) != _) return nextTurn;

    return start(nextTurn);
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

Mark charToMark(char c) {
    switch (c) {
        case 'X': return X;
        case 'O': return O;
        default: return _;
    }
}

char markToChar(Mark m) {
    switch (m) {
        case _: return ' ';
        case X: return 'X';
        case O: return 'O';
    }
}