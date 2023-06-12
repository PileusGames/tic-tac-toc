
//
// Created by Theo OMNES on 11/06/2023.
//

#ifndef TIC_TAC_TOC_INIT_H
#define TIC_TAC_TOC_INIT_H

#include "stdint.h"
#include "../../../lib/jsmn.h"
#include "stdbool.h"

// {"init": {"players" : 2}}

typedef struct Init {
    int8_t players;
} Init;

enum ParseErr {
    NO_ERROR,
    BAD_FORMAT,
    MISSING_ARGUMENT,
    INCORRECT_VALUE,
    UNEXPECTED_ARGUMENT,
    MISSING_ACTION,
    WRONG_ACTION,
    OUT_OF_ZONE
};

typedef struct InitParseResult {
    Init init;
    enum ParseErr error;
} InitParseResult;

InitParseResult fromJson(const char* json);
bool isTokenEquals(const char *json, jsmntok_t tok, const char *b);

#endif //TIC_TAC_TOC_INIT_H
