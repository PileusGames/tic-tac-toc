
//
// Created by Theo OMNES on 13/06/2023.
//

#ifndef TIC_TAC_TOC_JSON_H
#define TIC_TAC_TOC_JSON_H

// https://github.com/zserge/jsmn
#include "../../../lib/jsmn.h"
#include <stdio.h>
#include "stdbool.h"


bool isTokenEqualsString(const char *json, jsmntok_t tok, const char *b);
char* readJson(FILE* stream);
const char* boolToString(bool boolean);
int getIntFromJson(char* json, jsmntok_t tok);

#endif //TIC_TAC_TOC_JSON_H
