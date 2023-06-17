
//
// Created by Theo OMNES on 15/06/2023.
//

#ifndef TIC_TAC_TOC_ERRORS_H
#define TIC_TAC_TOC_ERRORS_H

#include "stdbool.h"

enum Error {
    NO_ERROR,
    BAD_FORMAT,
    MISSING_ARGUMENT,
    INCORRECT_VALUE,
    UNEXPECTED_ARGUMENT,
    MISSING_ACTION,
    OUT_OF_ZONE
};

bool isError(enum Error e);

#endif //TIC_TAC_TOC_ERRORS_H
