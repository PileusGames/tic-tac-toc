
//
// Created by Theo OMNES on 13/06/2023.
//

#include <stdlib.h>
#include "../minunit.h"
#include "../../src/exposition/cli/CLI.h"

int tests_run = 0;

/* JSON
static char* should_get_init_request() {
    const char* expected = "{\"init\": {\"players\" : 2}}";
    FILE* tmp = tmpfile();
    fputs(expected, tmp);
    char* actual = readJson(tmp);
    mu_assert("error, should have get inline json", strcmp(expected, actual) == 0);

    free(actual);
    fclose(tmp);
    return EXIT_SUCCESS;
}

static char* should_get_init_request_multilines_json() {
    const char* expected = "{\n \"init\": {\n \"players\" : 2\n }\n}";
    FILE* tmp = tmpfile();
    fputs(expected, tmp);

    char* actual = readJson(tmp);
    mu_assert("error, should have get multilines json", strcmp(expected, actual) == 0);

    free(actual);
    fclose(tmp);
    return EXIT_SUCCESS;
}
*/
static char* should_get_init_with_two_players() {
    const char* json = "{\n \"init\": {\n \"players\" : 2\n }\n}";
    FILE* tmp = tmpfile();
    fputs(json, tmp);

    InitParseResult result = init(tmp);

    mu_assert("error, result result should not have error", result.error == NO_ERROR);
    mu_assert("error, result result should have two players", result.init.players == 2);

    fclose(tmp);
    return EXIT_SUCCESS;
}
/* JSON
static char* should_get_stringified_boolean() {
    mu_assert("error, should be 'true'", strcmp("true", boolToString(true)) == 0);
    mu_assert("error, should be 'false'", strcmp("false", boolToString(false)) == 0);
    return EXIT_SUCCESS;
}
*/

/* INSTRUCTION
static char* should_get_score_when_X_is_winner() {
    mu_assert("error, should be [1,0] when X wins", strcmp("[1,0]", getScoreJson(X)) == 0);

    return EXIT_SUCCESS;
}

static char* should_get_score_when_O_is_winner() {
    mu_assert("error, should be [0,1] when O wins", strcmp("[0,1]", getScoreJson(O)) == 0);

    return EXIT_SUCCESS;
}

static char* should_get_score_when_no_winner() {
    mu_assert("error, should be [0,0] when no winner", strcmp("[0,0]", getScoreJson(EMPTY)) == 0);

    return EXIT_SUCCESS;
}*/


static char * all_tests() {
    mu_run_test(should_get_init_with_two_players);

    return EXIT_SUCCESS;
}


int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != EXIT_SUCCESS;
}