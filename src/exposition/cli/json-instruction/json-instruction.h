
//
// Created by Theo OMNES on 15/06/2023.
//

#ifndef TIC_TAC_TOC_JSON_INSTRUCTION_H
#define TIC_TAC_TOC_JSON_INSTRUCTION_H

#define MAX_INSTRUCTION_SIZE 2600

#include "../../../domain/grid/Grid.h"

char *getJsonDisplay(Grid grid);
char* buildInstructionForGrid(Grid grid);
char *getJsonMarksDisplayFromGrid(Grid grid);
char *getJsonMarkDisplayForMarkAtPosition(Mark mark, int8_t x, int8_t y);
const char* getScoreJson(Mark winner);
char* getJsonAction(Grid grid);
char* getJsonZones(Grid grid);
char* getJsonZone(int8_t x, int8_t y);

#endif //TIC_TAC_TOC_JSON_INSTRUCTION_H
