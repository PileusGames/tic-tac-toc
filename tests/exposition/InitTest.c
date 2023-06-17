
//
// Created by Theo OMNES on 12/06/2023.
//

#include <stdlib.h>
#include <printf.h>
#include "string.h"
#include "../minunit.h"
#define JSMN_HEADER
#include "../../src/exposition/json/json.h"
#include "../../src/exposition/dto/Init.h"

int tests_run = 0;

static char* test_isTokenEquals() {
    jsmn_parser p;
    jsmntok_t t[5];

    jsmn_init(&p);

    // {"init": {"players" : 2}}
    const char* s = "{\"init\": {\"players\" : 2}}";
    jsmn_parse(&p, s, strlen(s), t, 5);

    mu_assert("error, t[1] should be 'init'", isTokenEqualsString(s, t[1], "init"));

    mu_assert("error, t[1] should not be 'inzt'", !isTokenEqualsString(s, t[1], "inzt"));
    mu_assert("error, t[1] should not be 'a'", !isTokenEqualsString(s, t[1], "a"));

    return EXIT_SUCCESS;
}

static char* should_parse_init() {
    jsmn_parser p;
    jsmntok_t t[5];
    jsmn_init(&p);

    // {"init": {"players" : 2}}
    const char* s = "{\"init\": {\"players\" : 2}}";
    jsmn_parse(&p, s, strlen(s), t, 5);
    InitParseResult actual = fromJson(s);

    mu_assert("error, should have parsed valid init", actual.error == NO_ERROR && actual.init.players == 2);
    return EXIT_SUCCESS;
}

static char* should_miss_arguments() {
    jsmn_parser p;
    jsmntok_t t[5];
    jsmn_init(&p);

    // {"init": 2}
    const char* s = "{\"init\": 2}";
    jsmn_parse(&p, s, strlen(s), t, 5);
    InitParseResult actual = fromJson(s);

    mu_assert("error, should miss arguments", actual.error == MISSING_ARGUMENT);
    return EXIT_SUCCESS;
}

static char* should_miss_argument_players() {
    jsmn_parser p;
    jsmntok_t t[5];
    jsmn_init(&p);

    // {"init": {"bad" : 2}}
    const char* s = "{\"init\": 2}";
    jsmn_parse(&p, s, strlen(s), t, 5);
    InitParseResult actual = fromJson(s);

    mu_assert("error, should miss arguments", actual.error == MISSING_ARGUMENT);
    return EXIT_SUCCESS;
}

static char* should_unexpect_arguments() {
    jsmn_parser p;
    jsmntok_t t[10];
    jsmn_init(&p);

    // {"init": {"players": 2, "x": 3}
    const char* s = "{\"init\": {\"players\": 2, \"x\": 3}";
    jsmn_parse(&p, s, strlen(s), t, 10);
    InitParseResult actual = fromJson(s);

    mu_assert("error, should have too much arguments", actual.error == UNEXPECTED_ARGUMENT);
    return EXIT_SUCCESS;
}

static char * all_tests() {
    mu_run_test(test_isTokenEquals);
    mu_run_test(should_parse_init);
    mu_run_test(should_miss_arguments);
    mu_run_test(should_miss_argument_players);
    mu_run_test(should_unexpect_arguments);

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