
//
// Created by Theo OMNES on 15/06/2023.
//

#include <string.h>
#include "json-instruction.h"
#include "stdlib.h"
#include "stdio.h"
#include "../../../domain/grid/Grid.h"
#include "../../../utils/string-utils.h"
#include "../../json/json.h"


const char * const instructionFormat =   "{\n"
                                         "    \"displays\":[{%s, \"player\":1},{%s, \"player\":2}],\n"
                                         "    \"requested_actions\":[%s],\n"
                                         "    \"game_state\":{\n"
                                         "        \"scores\": %s,\n"
                                         "        \"game_over\": %s\n"
                                         "    }\n"
                                         "}";
char* buildInstructionForGrid(Grid grid) {
    char* instruction = malloc(MAX_INSTRUCTION_SIZE);
    char* display = getJsonDisplay(grid);
    char* action = getJsonAction(grid);
    sprintf(instruction, instructionFormat,
            display, display,
            action,
            getScoreJson(getWinner(grid)),
            boolToString(isGameOver(grid))
    );

    free(display);
    free(action);
    return instruction;
}

const char* const displaysFormat = "\n"
                                   "      \"width\": \"300\",\n"
                                   "      \"height\": \"300\",\n"
                                   "      \"content\": [\n"
                                   "        {\n"
                                   "          \"tag\": \"style\",\n"
                                   "          \"content\": \"line{stroke:black;stroke-width:4;}\"\n"
                                   "        },\n"
                                   "        {\n"
                                   "          \"tag\": \"line\",\n"
                                   "          \"x1\": \"0\",\n"
                                   "          \"y1\": \"100\",\n"
                                   "          \"x2\": \"300\",\n"
                                   "          \"y2\": \"100\"\n"
                                   "        },\n"
                                   "        {\n"
                                   "          \"tag\": \"line\",\n"
                                   "          \"x1\": \"100\",\n"
                                   "          \"y1\": \"0\",\n"
                                   "          \"x2\": \"100\",\n"
                                   "          \"y2\": \"300\"\n"
                                   "        },\n"
                                   "        {\n"
                                   "          \"tag\": \"line\",\n"
                                   "          \"x1\": \"0\",\n"
                                   "          \"y1\": \"200\",\n"
                                   "          \"x2\": \"300\",\n"
                                   "          \"y2\": \"200\"\n"
                                   "        },\n"
                                   "        {\n"
                                   "          \"tag\": \"line\",\n"
                                   "          \"x1\": \"200\",\n"
                                   "          \"y1\": \"0\",\n"
                                   "          \"x2\": \"200\",\n"
                                   "          \"y2\": \"300\"\n"
                                   "        }\n"
                                   "      ]%s";
char* getJsonDisplay(Grid grid) {
    char* display = malloc(1900);
    char* marks = getJsonMarksDisplayFromGrid(grid);
    snprintf(display, 1900, displaysFormat, marks);

    free(marks);
    return display;
}

char *getJsonMarksDisplayFromGrid(Grid grid) {
    char* json = NULL;
    for(int8_t x = 0; x < 3; x += 1) {
        for(int8_t y = 0; y < 3; y += 1) {
            if(!grid.marks[y][x]) continue;

            char* markJson = getJsonMarkDisplayForMarkAtPosition(grid.marks[y][x], x, y);
            append(&json, markJson);
        }
    }
    return json;
}

const char* const markDisplayJsonFormat = ",\n"
                                          "        {\n"
                                          "          \"tag\": \"circle\",\n"
                                          "          \"cx\": \"%d\",\n"
                                          "          \"cy\": \"%d\",\n"
                                          "          \"r\": \"33\",\n"
                                          "          \"fill\": \"%s\"\n"
                                          "        }";
char *getJsonMarkDisplayForMarkAtPosition(Mark mark, int8_t x, int8_t y) {
    char* json = malloc(150);
    strcpy(json,"");

    if(mark == EMPTY) return json;

    const char* const color = mark == X ? "blue" : "red";
    snprintf(json, 150, markDisplayJsonFormat,
             (int) ((0.5+x) * 100),
             (int) ((0.5+y) * 100),
             color);

    return json;
}

const char* const actionFormat = "{\n"
                                 "      \"type\": \"CLICK\",\n"
                                 "      \"player\": %d,\n"
                                 "      \"zones\": [%s]\n"
                                 "    }";
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
            if(grid.marks[y][x] != EMPTY) continue;

            char* zone = getJsonZone(x, y);
            append(&zones, zone);
            if(x != 2 || y != 2) append(&zones, ",");
            append(&zones, "\n");

            free(zone);
        }
    }
    return zones;
}


const char* const zoneFormat = "        {\n"
                               "          \"x\": %d,\n"
                               "          \"y\": %d,\n"
                               "          \"width\": 100,\n"
                               "          \"height\": 100\n"
                               "        }";
char* getJsonZone(int8_t x, int8_t y) {
    char* zone = malloc(128);
    sprintf(zone, zoneFormat, x * 100, y * 100);
    return zone;
}

const char* getScoreJson(Mark winner) {
    switch (winner) {
        case X: return "[1,0]";
        case O: return "[0,1]";
        default: return "[0,0]";
    }
}

