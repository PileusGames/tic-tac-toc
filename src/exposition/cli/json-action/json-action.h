
//
// Created by Theo OMNES on 15/06/2023.
//

#ifndef TIC_TAC_TOC_JSON_ACTION_H
#define TIC_TAC_TOC_JSON_ACTION_H

#include <stdio.h>
#include "../../dto/actions.h"

/**
 * @param player we are listening for, error MISSING_ACTION if the action received is not from this player
 */
ActionParseResult listenPlayerAction(Mark player, FILE* stream);

#endif //TIC_TAC_TOC_JSON_ACTION_H
