
//
// Created by Theo OMNES on 12/06/2023.
//


#include <printf.h>
#include <string.h>
#include <stdlib.h>
#include "../../minunit.h"
#include "../../../lib/jsmn.h"

int tests_run = 0;

static char* test_parse_foo_bar() {
    jsmn_parser p;
    jsmntok_t t[5];

    jsmn_init(&p);

    // { "foo": "bar", "x": 0.3 }
    const char* s = "{ \"foo\": \"bar\", \"x\": 0.3 }";
    int r = jsmn_parse(&p, s, strlen(s), t, 5);

    mu_assert("error, should have parsed 5 tokens", r == 5);
    mu_assert("error, first token should be the whole object start at 0", t[0].start == 0);
    mu_assert("error, first token should be the whole object ends at 26", t[0].end == strlen(s));
    mu_assert("error, first token should be object type", t[0].type == JSMN_OBJECT);
    mu_assert("error, first token should have 2 nested tokens", t[0].size == 2);

    mu_assert("error, foo should bee a string", t[1].type == JSMN_STRING);
    mu_assert("error, foo token should start at 3", t[1].start == 3);
    mu_assert("error, foo token should end at 6", t[1].end == 6);
    mu_assert("error, foo should have one nested token", t[1].size == 1);

    mu_assert("error, bar should bee a string", t[2].type == JSMN_STRING);
    mu_assert("error, bar token should start at 10", t[2].start == 10);
    mu_assert("error, bar token should end at 13", t[2].end == 13);
    mu_assert("error, bar should not have nested token", t[2].size == 0);

    mu_assert("error, x should bee a string", t[3].type == JSMN_STRING);
    mu_assert("error, x token should start at 17", t[3].start == 17);
    mu_assert("error, x token should end at 18", t[3].end == 18);
    mu_assert("error, x should have one nested token", t[3].size == 1);

    mu_assert("error, 0.3 should bee a string", t[4].type == JSMN_PRIMITIVE);
    mu_assert("error, 0.3 token should start at 10", t[4].start == 21);
    mu_assert("error, 0.3 token should end at 13", t[4].end == 24);
    mu_assert("error, 0.3 should not have nested token", t[4].size == 0);

    return EXIT_SUCCESS;
}

static char* test_parse_init() {
    jsmn_parser p;
    jsmntok_t t[5];

    jsmn_init(&p);

    // {"init": {"players" : 2}}
    const char* s = "{\"init\": {\"players\" : 2}}";
    int r = jsmn_parse(&p, s, strlen(s), t, 5);

    mu_assert("error, should have parsed 3 tokens", r == 5);
    mu_assert("error, first token should be the whole object start at 0", t[0].start == 0);
    mu_assert("error, first token should be the whole object ends at 25", t[0].end == strlen(s));
    mu_assert("error, first token should be object type", t[0].type == JSMN_OBJECT);
    mu_assert("error, first token should have one nested token", t[0].size == 1);

    mu_assert("error, init should bee a string", t[1].type == JSMN_STRING);
    mu_assert("error, init token should start at 3", t[1].start == 2);
    mu_assert("error, init token should end at 6", t[1].end == 6);
    mu_assert("error, init should have one nested token", t[1].size == 1);

    mu_assert("error, players obj should bee an object", t[2].type == JSMN_OBJECT);
    mu_assert("error, players obj token should start at 9", t[2].start == 9);
    mu_assert("error, players obj token should end at 25", t[2].end == 24);
    mu_assert("error, players obj should have one nested token", t[2].size == 1);

    mu_assert("error, players should bee a string", t[3].type == JSMN_STRING);
    mu_assert("error, players token should start at 17", t[3].start == 11);
    mu_assert("error, players token should start at 18", t[3].end == 18);
    mu_assert("error, players should have one nested token", t[3].size == 1);

    mu_assert("error, 2 should bee a primitive", t[4].type == JSMN_PRIMITIVE);
    mu_assert("error, 2 token should start at 22", t[4].start == 22);
    mu_assert("error, 2 token should start at 23", t[4].end == 23);
    mu_assert("error, 2 should not have nested token", t[4].size == 0);

    return EXIT_SUCCESS;
}

static char * all_tests() {
    mu_run_test(test_parse_foo_bar);
    mu_run_test(test_parse_init);

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