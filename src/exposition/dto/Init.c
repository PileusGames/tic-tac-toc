
//
// Created by Theo OMNES on 12/06/2023.
//

#include <stdbool.h>
#include <string.h>

#define JSMN_HEADER
#include "../json/json.h"
#include "Init.h"


// TODO move to CLI
InitParseResult KO(enum ParseErr err);
InitParseResult OK(Init init);

InitParseResult fromJson(const char* json) {
    jsmn_parser p;
    jsmntok_t t[6];

    jsmn_init(&p);
    int needed = jsmn_parse(&p, json, strlen(json), NULL, 6);
    if(needed < 5) return KO(MISSING_ARGUMENT);

    jsmn_init(&p);
    jsmn_parse(&p, json, strlen(json), t, 5);

    if(!isTokenEquals(json, t[1], "init")) return KO(BAD_FORMAT);
    if(!isTokenEquals(json, t[3], "players")) return KO(MISSING_ARGUMENT);
    if(!isTokenEquals(json, t[4], "2")) return KO(INCORRECT_VALUE);
    if(needed > 5) return KO(UNEXPECTED_ARGUMENT);

    Init init = {2};
    return OK(init);
}


InitParseResult KO(enum ParseErr err) {
    InitParseResult res = {{0},err};
    return res;
}

InitParseResult OK(Init init) {
    InitParseResult res = {init, NO_ERROR};
    return res;
}