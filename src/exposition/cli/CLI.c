
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

char *getJsonDisplay(Grid grid);

char *getJsonMarksDisplayFromGrid(Grid grid);
char *getJsonMarkDisplayForMarkAtPosition(Mark mark, int8_t x, int8_t y);

CLI newCLI(Grid grid) {
    CLI cli = {grid};
    return cli;
}

CLI start(CLI cli) {
    char* instruction = getInstructionForGrid(cli.grid);
    fputs(instruction, stdout);

    int8_t x = -1;
    int8_t y = -1;
    char m = 0;
    scanf("%hhd %hhd %c", &x, &y, &m);
    fflush(stdin);

    Grid g = placeOnGrid(cli.grid, charToMark(m), x, y);
    CLI nextTurn = {g};
    if(isGameOver(g)) return nextTurn;

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
    if(a == NULL) a = "";
    if(b == NULL) b = "";
    size_t sizeA = strlen(a);
    size_t sizeB = strlen(b);
    char* new = malloc( sizeA+ sizeB + 1);
    return strcat(strcat(new, a), b);
}

void append(char** base, char* toAppend) {
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
char* getInstructionForGrid(Grid grid) {
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

const char* const markDisplayJsonFormat = ",\n"
                                           "        {\n"
                                           "          \"tag\": \"circle\",\n"
                                           "          \"cx\": \"%d\",\n"
                                           "          \"cy\": \"%d\",\n"
                                           "          \"r\": \"33\",\n"
                                           "          \"fill\": \"%s\"\n"
                                           "        }";
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
        default: return EMPTY;
    }
}

char markToChar(Mark m) {
    switch (m) {
        case EMPTY: return ' ';
        case X: return 'X';
        case O: return 'O';
    }
}