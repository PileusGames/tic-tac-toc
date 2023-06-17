
//
// Created by Theo OMNES on 15/06/2023.
//

#include <string.h>
#define JSMN_HEADER
#include "json.h"
#include "stdlib.h"
#include "../../utils/string-utils.h"

#define MAX_LINE_SIZE 255

char* readJson(FILE* stream) {
    rewind(stream);
    char* request = malloc(255);

    char* line = malloc(255);;
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

bool isTokenEqualsString(const char *json, jsmntok_t tok, const char *b) {
    int8_t size = (int8_t)(tok.end - tok.start);
    if(size != strlen(b)) return false;

    for(int8_t i = 0; i < size; i++) {
        if(json[tok.start + i] != b[i]) return false;
    }
    return true;
}

const char* boolToString(bool boolean) {
    return boolean
           ? "true"
           : "false";
}

int getIntFromJson(char* json, jsmntok_t tok) {
    if(tok.type != JSMN_PRIMITIVE) return INT8_MIN;
    char first = json[tok.start];
    bool isInteger = first == '-' || (first >= '0' && first <= '9');
    if(!isInteger) return INT8_MIN;
    int size = tok.end - tok.start;
    char* str = malloc(size + 1);
    strncpy(str, json+tok.start, size);
    int integer = atoi(str);
    free(str);
    return integer;
}