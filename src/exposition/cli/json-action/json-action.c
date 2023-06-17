
//
// Created by Theo OMNES on 15/06/2023.
//

#include <string.h>
#include <stdlib.h>
#include "json-action.h"
#define JSMN_HEADER
#include "../../json/json.h"

ActionParseResult actionOK(Action action);
ActionParseResult actionKO(enum Error err);
Mark playerNumberToMark(char n);
ActionParseResult actionFromJson(char* json);

ActionParseResult listenPlayerAction(Mark player, FILE* stream) {
    char* json = readJson(stream);
    ActionParseResult result = actionFromJson(json);
    free(json);

    if(isError(result.error)) return result;
    if(result.action.player != player) return actionKO(MISSING_ACTION);
    Action a = result.action;
    if(a.x < 0 || a.x > 2 || a.y < 0 || a.y > 2) return actionKO(OUT_OF_ZONE);

    return result;
}

ActionParseResult actionFromJson(char* json) {
    jsmn_parser p;
    jsmn_init(&p);
    int needed = jsmn_parse(&p, json, strlen(json), NULL, 15);
    if(needed < 10) return actionKO(MISSING_ARGUMENT);

    jsmntok_t t[needed];
    jsmn_init(&p);
    jsmn_parse(&p, json, strlen(json), t, needed);

    if(!isTokenEqualsString(json, t[1], "actions")) return actionKO(BAD_FORMAT);
    if(t[2].type != JSMN_ARRAY) return actionKO(BAD_FORMAT);
    if(t[2].size != 1) return actionKO(BAD_FORMAT);

    int x = getIntFromJson(json,t[7]);
    int y = getIntFromJson(json,t[9]);

    if(x == INT8_MIN) return actionKO(BAD_FORMAT);
    if(y == INT8_MIN) return actionKO(BAD_FORMAT);

    Action action = {
            playerNumberToMark(json[t[5].start]),
             x / 100,
             y / 100,
    };

    return actionOK(action);
}


ActionParseResult actionKO(enum Error error) {
    ActionParseResult ko = {{0,0,0}, error};
    return ko;
}

ActionParseResult actionOK(Action action) {
    ActionParseResult ok = {action, NO_ERROR};
    return ok;
}

Mark playerNumberToMark(char n) {
    switch (n) {
        case '1': return X;
        case '2': return O;
        default: return EMPTY;
    }
}


