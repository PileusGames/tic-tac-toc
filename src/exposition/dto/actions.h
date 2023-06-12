
//
// Created by Theo OMNES on 11/06/2023.
//

#ifndef TIC_TAC_TOC_ACTIONS_H
#define TIC_TAC_TOC_ACTIONS_H

#include "stdint.h"

// {"actions":[{"player": 1, "x": 1, "y": 1}]}

typedef struct Action {
    int8_t player;
    int8_t x;
    int8_t y;
} Action;

typedef struct Actions {
    int8_t size;
    Action* actions;
} Actions;

#endif //TIC_TAC_TOC_ACTIONS_H
