
//
// Created by Theo OMNES on 15/06/2023.
//

#include "string-utils.h"
#include "stdlib.h"
#include "string.h"

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

