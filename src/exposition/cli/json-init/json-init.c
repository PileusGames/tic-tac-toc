
//
// Created by Theo OMNES on 17/06/2023.
//

#include <string.h>

#define JSMN_HEADER
#include "../../json/json.h"
#include "../../dto/Init.h"
#include "json-init.h"

InitParseResult initKO(enum Error err);
InitParseResult initOK(Init init);

InitParseResult fromJson(const char* json) {
    jsmn_parser p;
    jsmn_init(&p);
    int needed = jsmn_parse(&p, json, strlen(json), NULL, 10);
    if(needed < 5) return initKO(MISSING_ARGUMENT);

    jsmntok_t t[needed];
    jsmn_init(&p);
    jsmn_parse(&p, json, strlen(json), t, needed);

    if(!isTokenEqualsString(json, t[1], "init")) return initKO(BAD_FORMAT);
    if(!isTokenEqualsString(json, t[3], "players")) return initKO(MISSING_ARGUMENT);
    if(!isTokenEqualsString(json, t[4], "2")) return initKO(INCORRECT_VALUE);
    if(needed > 5) return initKO(UNEXPECTED_ARGUMENT);

    Init init = {2};
    return initOK(init);
}


InitParseResult initKO(enum Error err) {
    InitParseResult res = {{0},err};
    return res;
}

InitParseResult initOK(Init init) {
    InitParseResult res = {init, NO_ERROR};
    return res;
}