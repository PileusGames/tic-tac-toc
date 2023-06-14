
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
    size_t sizeA = 0, sizeB = 0;
    if(a != NULL) sizeA = strlen(a);
    if(b != NULL) sizeB = strlen(b);
    char* new = malloc( sizeA+ sizeB + 1);
    return strcat(strcat(new, a), b);;
}

void append(char** base, char* toAppend) {
    if(base == NULL || toAppend == NULL) return;

    char* old = *base;
    char* new = concat(*base, toAppend);

    free(old);
    *base = new;
}

int8_t countCharInString(char c, const char* string) {
    int8_t i, count;
    for(i = 0, count = 0; string[i]; i+=1) {
        if(string[i] == c) count += 1;
    }
    return count;
}


const char * const instructionFormat =   "{\n"
                                         "    \"displays\":[{%s, \"player\":1},{%s, \"player\":2}],\n"
                                         "    \"requested_actions\":[%s],\n"
                                         "    \"game_state\":{\n"
                                         "        \"scores\": %s,\n"
                                         "        \"game_over\": %s\n"
                                         "    }\n"
                                         "}";

const char* const actionFormat = "{\n"
                                 "      \"type\": \"CLICK\",\n"
                                 "      \"player\": %d,\n"
                                 "      \"zones\": [%s]\n"
                                 "    }";

const char* const zoneFormat = "        {\n"
                               "          \"x\": %d,\n"
                               "          \"y\": %d,\n"
                               "          \"width\": 100,\n"
                               "          \"height\": 100\n"
                               "        }";

char* getInstructionForGrid(Grid grid) {
    char* instruction = malloc(MAX_INSTRUCTION_SIZE);
    char* action = getJsonAction(grid);
    sprintf(instruction, instructionFormat,
            "**display", "**display",
            action,
            getScoreJson(getWinner(grid)),
            boolToString(isGameOver(grid))
    );

    free(action);
    return instruction;
}


const char* boolToString(bool boolean) {
    return boolean
           ? "true"
           : "false";
}

const char* getScoreJson(Mark winner) {
    switch (winner) {
        case X: return "[1,0]";
        case O: return "[0,1]";
        default: return "[0,0]";
    }
}

char* getJsonAction(Grid grid) {
    char* action = malloc(MAX_INSTRUCTION_SIZE);
    char* zones = getJsonZones(grid);

    snprintf(action, MAX_INSTRUCTION_SIZE, actionFormat, grid.currentPlayer, zones);

    free(zones);
    return action;
}

char* getJsonZones(Grid grid) {
    char* zones = malloc(2);
    strlcpy(zones, "\n", 2);

    for(int8_t x = 0; x < 3; x += 1) {
        for(int8_t y = 0; y < 3; y +=1) {
            if(grid.marks[x][y] != _) continue;

            char* zone = getJsonZone(x, y);
            append(&zones, zone);
            if(x != 2 || y != 2) append(&zones, ",");
            append(&zones, "\n");

            free(zone);
        }
    }
    return zones;
}

char* getJsonZone(int8_t x, int8_t y) {
    char* zone = malloc(128);
    sprintf(zone, zoneFormat, x * 100, y * 100);
    return zone;
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