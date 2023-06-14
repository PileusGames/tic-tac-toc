
//
// Created by Theo OMNES on 14/06/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "Instruction.h"

/*
{
    "displays":[{**display, "player":1},{**display, "player":2}],
    "requested_actions":[self.current_action],
    "game_state":{
        "scores": scores,
        "game_over": game_over
    }
}
 */

const char* instructionToFormat();
const char* getGameOverBooleanString(Grid grid);

char* getInstructionForGrid(Grid grid) {
    char* instruction = malloc(MAX_INSTRUCTION_SIZE);
    sprintf(instruction, instructionToFormat(),
            "**display", "**display",
            "self.current_action",
            "scores",
            getGameOverBooleanString(grid)
            );
    return instruction;
}

const char* instructionToFormat() {
    return "{\n"
           "    \"displays\":[{%s, \"player\":1},{%s, \"player\":2}],\n"
           "    \"requested_actions\":[%s],\n"
           "    \"game_state\":{\n"
           "        \"scores\": %s,\n"
           "        \"game_over\": %s\n"
           "    }\n"
           "}";
}

const char* getGameOverBooleanString(Grid grid) {
    bool winnerExists = getWinner(grid) != _;
    bool gameIsOver = winnerExists || gridIsFull(grid);

    if (gameIsOver) return "true";
    else return "false";
}