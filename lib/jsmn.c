
//
// Created by Theo OMNES on 12/06/2023.
//
#include "jsmn.h"
#include "stdbool.h"
#include "string.h"

bool isTokenEquals(const char *json, jsmntok_t tok, const char *b) {
    int8_t size = (int8_t)(tok.end - tok.start);
    if(size != strlen(b)) return false;

    for(int8_t i = 0; i < size; i++) {
        if(*(json + tok.start + i) != *(b+i)) return false;
    }
    return true;
}