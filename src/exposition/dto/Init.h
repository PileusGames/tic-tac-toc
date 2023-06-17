
//
// Created by Theo OMNES on 11/06/2023.
//

#ifndef TIC_TAC_TOC_INIT_H
#define TIC_TAC_TOC_INIT_H

#include "stdint.h"
#include "stdbool.h"
#include "../error/errors.h"

typedef struct Init {
    int8_t players;
} Init;

typedef struct InitParseResult {
    Init init;
    enum Error error;
} InitParseResult;

#endif //TIC_TAC_TOC_INIT_H
