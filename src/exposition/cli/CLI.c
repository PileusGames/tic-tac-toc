
//
// Created by Theo OMNES on 11/06/2023.
//

#include <stdlib.h>
#include "CLI.h"
#include "stdio.h"
#include "string.h"

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


InitParseResult init(FILE* stream) {
    char* request = readJson(stream);
    InitParseResult result = fromJson(request);

    free(request);
    return result;
}

char* readJson(FILE* stream) {
    rewind(stream);
    char* request = malloc(MAX_INPUT_SIZE + 1);

    char* line = malloc(MAX_LINE_SIZE + 1);;
    int8_t opened, closed;

    fgets(request, MAX_LINE_SIZE, stream);
    opened = countCharInString('{', request);
    closed = countCharInString('}', request);

    while (opened < 1 || closed < opened) {
        fgets(line, MAX_LINE_SIZE, stream);
        char* tmp = concat(request, line);
        free(request);
        request = tmp;
        opened = countCharInString('{', request);
        closed = countCharInString('}', request);
    }

    free(line);
    return request;
}

char* concat(char* a, char* b) {
    char* new = malloc(strlen(a) + strlen(b) + 1);
    return strcat(strcat(new, a), b);;
}

int8_t countCharInString(char c, const char* string) {
    int8_t i, count;
    for(i = 0, count = 0; string[i]; i+=1) {
        if(string[i] == c) count += 1;
    }
    return count;
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