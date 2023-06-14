
//
// Created by Theo OMNES on 11/06/2023.
//

#ifndef TIC_TAC_TOC_CLI_H
#define TIC_TAC_TOC_CLI_H

#include <stdio.h>
#include "../../domain/grid/Grid.h"
#include "../dto/Init.h"

#define MAX_INPUT_SIZE 255
#define MAX_LINE_SIZE 50
#define MAX_OUTPUT_SIZE 255
#define MAX_INSTRUCTION_SIZE 2600


#define IN stdin


typedef struct CLI {
    Grid grid;
} CLI;

CLI newCLI(Grid grid);
CLI start(CLI cli);
InitParseResult init(FILE* stream);
char* readJson(FILE* stream);
int8_t countCharInString(char c, const char* string);
char* concat(char* a, char* b);
char* getInstructionForGrid(Grid grid);
const char* boolToString(bool boolean);
const char* getScoreJson(Mark winner);
char* getJsonAction(Grid grid);
char* getJsonZones(Grid grid);
char* getJsonZone(int8_t x, int8_t y);

#endif //TIC_TAC_TOC_CLI_H
