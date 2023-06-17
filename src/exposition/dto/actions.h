
//
// Created by Theo OMNES on 11/06/2023.
//

#ifndef TIC_TAC_TOC_ACTIONS_H
#define TIC_TAC_TOC_ACTIONS_H

#include "stdint.h"
#include "../error/errors.h"
#include "../../domain/mark/Mark.h"

// {"actions":[{"player": 1, "x": 1, "y": 1}]}

typedef struct Action {
    Mark player;
    int8_t x;
    int8_t y;
} Action;

typedef struct ActionParseResult {
    Action action;
    enum Error error;
} ActionParseResult;


#endif //TIC_TAC_TOC_ACTIONS_H
