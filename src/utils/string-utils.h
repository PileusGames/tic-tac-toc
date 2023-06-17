
//
// Created by Theo OMNES on 15/06/2023.
//

#ifndef TIC_TAC_TOC_STRING_UTILS_H
#define TIC_TAC_TOC_STRING_UTILS_H

#include "stdint.h"

int8_t countCharInString(char c, const char* string);
char* concat(char* a, char* b);
void append(char** base, char* toAppend);

#endif //TIC_TAC_TOC_STRING_UTILS_H
