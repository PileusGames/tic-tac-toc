
//
// Created by Theo OMNES on 17/06/2023.
//

#include "stdbool.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"


// region DOMAIN
enum Mark {
    EMPTY = 0,
    X = 1, // Player 1
    O = 2 // Player 2
};

typedef enum Mark Mark;


typedef struct Grid {
    Mark currentPlayer;
    Mark marks[3][3];
} Grid;


bool isTheWinner(Grid grid, enum Mark mark);




// GRID
Grid emptyGrid(Mark startPlayer) {
    Grid new = {
            startPlayer,
            {
                    {EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY},
                    {EMPTY, EMPTY, EMPTY}
            }
    };

    return new;
}

bool gridsAreEquals(Grid a, Grid b) {
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            if(a.marks[x][y] != b.marks[x][y]) return false;
        }
    }
    return true;
}

Mark getWinner(Grid grid) {
    if(isTheWinner(grid, X)) return X;
    if(isTheWinner(grid, O)) return O;
    return EMPTY;
}

bool isTheWinner(Grid g, Mark mark) {

    //lines
    if(g.marks[0][0] == mark && g.marks[0][1] == mark && g.marks[0][2] == mark) return true;
    if(g.marks[1][0] == mark && g.marks[1][1] == mark && g.marks[1][2] == mark) return true;
    if(g.marks[2][0] == mark && g.marks[2][1] == mark && g.marks[2][2] == mark) return true;

    //columns
    if(g.marks[0][0] == mark && g.marks[1][0] == mark && g.marks[2][0] == mark) return true;
    if(g.marks[0][1] == mark && g.marks[1][1] == mark && g.marks[2][1] == mark) return true;
    if(g.marks[0][2] == mark && g.marks[1][2] == mark && g.marks[2][2] == mark) return true;

    //diagonals
    if(g.marks[0][0] == mark && g.marks[1][1] == mark && g.marks[2][2] == mark) return true;
    if(g.marks[0][2] == mark && g.marks[1][1] == mark && g.marks[2][0] == mark) return true;

    return false;
}

Grid placeOnGrid(Grid grid, Mark mark, int8_t x, int8_t y) {
    if(mark == EMPTY) return grid;
    if(x < 0 || x > 2 || y < 0 || y > 2) return grid;
    if(grid.marks[x][y] != EMPTY) return grid;

    grid.marks[x][y] = mark;
    return grid;
}

bool gridIsFull(Grid grid) {
    for(int x = 0; x < 3; x ++) {
        for(int y = 0; y < 3; y ++) {
            if(grid.marks[x][y] == EMPTY) return false;
        }
    }
    return true;
}

bool isGameOver(Grid grid) {
    return getWinner(grid) || gridIsFull(grid);
}

Grid switchPlayer(Grid grid) {
    if(grid.currentPlayer == EMPTY) return grid;
    Mark nextPlayer = grid.currentPlayer == X ? O : X;
    grid.currentPlayer = nextPlayer;
    return grid;
}

// GRID
// endregion

// region UTILS
// STRING_UTILS
char* concat(char* a, char* b) {
    if(a == NULL) a = "";
    if(b == NULL) b = "";
    size_t sizeA = strlen(a);
    size_t sizeB = strlen(b);
    char* new = malloc( sizeA+ sizeB + 1);
    return strcat(strcat(new, a), b);
}

void append(char** base, char* toAppend) {
    char* old = *base;
    char* new = concat(*base, toAppend);

    free(old);
    *base = new;
}

int8_t countCharInString(char c, const char* string) {
    int8_t i, count;
    for(i = 0, count = 0; string[i]; i+=1) {
        if(string[i] == c) count += 1;
    }
    return count;
}

// STRING_UTILS
// endregion

// region EXPOSITION
// region ERRORS

enum Error {
    NO_ERROR,
    BAD_FORMAT,
    MISSING_ARGUMENT,
    INCORRECT_VALUE,
    UNEXPECTED_ARGUMENT,
    MISSING_ACTION,
    OUT_OF_ZONE
};

bool isError(enum Error e) {
    return e != NO_ERROR;
}
// endregion

// region DTO
// ACTION
typedef struct Action {
    Mark player;
    int8_t x;
    int8_t y;
} Action;

typedef struct ActionParseResult {
    Action action;
    enum Error error;
} ActionParseResult;
//ACTION

// INIT
typedef struct Init {
    int8_t players;
} Init;

typedef struct InitParseResult {
    Init init;
    enum Error error;
} InitParseResult;

// INIT
// endregion

//region JSMN
/*
 * MIT License
 *
 * Copyright (c) 2010 Serge Zaitsev
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef JSMN_H
#define JSMN_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef JSMN_STATIC
#define JSMN_API static
#else
#define JSMN_API extern
#endif

/**
 * JSON type identifier. Basic types are:
 * 	o Object
 * 	o Array
 * 	o String
 * 	o Other primitive: number, boolean (true/false) or null
 */
typedef enum {
    JSMN_UNDEFINED = 0,
    JSMN_OBJECT = 1 << 0,
    JSMN_ARRAY = 1 << 1,
    JSMN_STRING = 1 << 2,
    JSMN_PRIMITIVE = 1 << 3
} jsmntype_t;

enum jsmnerr {
    /* Not enough tokens were provided */
    JSMN_ERROR_NOMEM = -1,
    /* Invalid character inside JSON string */
    JSMN_ERROR_INVAL = -2,
    /* The string is not a full JSON packet, more bytes expected */
    JSMN_ERROR_PART = -3
};

/**
 * JSON token description.
 * type		type (object, array, string etc.)
 * start	start position in JSON data string
 * end		end position in JSON data string
 */
typedef struct jsmntok {
    jsmntype_t type;
    int start;
    int end;
    int size;
#ifdef JSMN_PARENT_LINKS
    int parent;
#endif
} jsmntok_t;

/**
 * JSON parser. Contains an array of token blocks available. Also stores
 * the string being parsed now and current position in that string.
 */
typedef struct jsmn_parser {
    unsigned int pos;     /* offset in the JSON string */
    unsigned int toknext; /* next token to allocate */
    int toksuper;         /* superior token node, e.g. parent object or array */
} jsmn_parser;

/**
 * Create JSON parser over an array of tokens
 */
JSMN_API void jsmn_init(jsmn_parser *parser);

/**
 * Run JSON parser. It parses a JSON data string into and array of tokens, each
 * describing
 * a single JSON object.
 */
JSMN_API int jsmn_parse(jsmn_parser *parser, const char *js, const size_t len,
                        jsmntok_t *tokens, const unsigned int num_tokens);

#ifndef JSMN_HEADER
/**
 * Allocates a fresh unused token from the token pool.
 */
static jsmntok_t *jsmn_alloc_token(jsmn_parser *parser, jsmntok_t *tokens,
                                   const size_t num_tokens) {
    jsmntok_t *tok;
    if (parser->toknext >= num_tokens) {
        return NULL;
    }
    tok = &tokens[parser->toknext++];
    tok->start = tok->end = -1;
    tok->size = 0;
#ifdef JSMN_PARENT_LINKS
    tok->parent = -1;
#endif
    return tok;
}

/**
 * Fills token type and boundaries.
 */
static void jsmn_fill_token(jsmntok_t *token, const jsmntype_t type,
                            const int start, const int end) {
    token->type = type;
    token->start = start;
    token->end = end;
    token->size = 0;
}

/**
 * Fills next available token with JSON primitive.
 */
static int jsmn_parse_primitive(jsmn_parser *parser, const char *js,
                                const size_t len, jsmntok_t *tokens,
                                const size_t num_tokens) {
    jsmntok_t *token;
    int start;

    start = parser->pos;

    for (; parser->pos < len && js[parser->pos] != '\0'; parser->pos++) {
        switch (js[parser->pos]) {
#ifndef JSMN_STRICT
            /* In strict mode primitive must be followed by "," or "}" or "]" */
            case ':':
#endif
            case '\t':
            case '\r':
            case '\n':
            case ' ':
            case ',':
            case ']':
            case '}':
                goto found;
            default:
                /* to quiet a warning from gcc*/
                break;
        }
        if (js[parser->pos] < 32 || js[parser->pos] >= 127) {
            parser->pos = start;
            return JSMN_ERROR_INVAL;
        }
    }
#ifdef JSMN_STRICT
    /* In strict mode primitive must be followed by a comma/object/array */
  parser->pos = start;
  return JSMN_ERROR_PART;
#endif

    found:
    if (tokens == NULL) {
        parser->pos--;
        return 0;
    }
    token = jsmn_alloc_token(parser, tokens, num_tokens);
    if (token == NULL) {
        parser->pos = start;
        return JSMN_ERROR_NOMEM;
    }
    jsmn_fill_token(token, JSMN_PRIMITIVE, start, parser->pos);
#ifdef JSMN_PARENT_LINKS
    token->parent = parser->toksuper;
#endif
    parser->pos--;
    return 0;
}

/**
 * Fills next token with JSON string.
 */
static int jsmn_parse_string(jsmn_parser *parser, const char *js,
                             const size_t len, jsmntok_t *tokens,
                             const size_t num_tokens) {
    jsmntok_t *token;

    int start = parser->pos;

    /* Skip starting quote */
    parser->pos++;

    for (; parser->pos < len && js[parser->pos] != '\0'; parser->pos++) {
        char c = js[parser->pos];

        /* Quote: end of string */
        if (c == '\"') {
            if (tokens == NULL) {
                return 0;
            }
            token = jsmn_alloc_token(parser, tokens, num_tokens);
            if (token == NULL) {
                parser->pos = start;
                return JSMN_ERROR_NOMEM;
            }
            jsmn_fill_token(token, JSMN_STRING, start + 1, parser->pos);
#ifdef JSMN_PARENT_LINKS
            token->parent = parser->toksuper;
#endif
            return 0;
        }

        /* Backslash: Quoted symbol expected */
        if (c == '\\' && parser->pos + 1 < len) {
            int i;
            parser->pos++;
            switch (js[parser->pos]) {
                /* Allowed escaped symbols */
                case '\"':
                case '/':
                case '\\':
                case 'b':
                case 'f':
                case 'r':
                case 'n':
                case 't':
                    break;
                    /* Allows escaped symbol \uXXXX */
                case 'u':
                    parser->pos++;
                    for (i = 0; i < 4 && parser->pos < len && js[parser->pos] != '\0';
                         i++) {
                        /* If it isn't a hex character we have an error */
                        if (!((js[parser->pos] >= 48 && js[parser->pos] <= 57) ||   /* 0-9 */
                              (js[parser->pos] >= 65 && js[parser->pos] <= 70) ||   /* A-F */
                              (js[parser->pos] >= 97 && js[parser->pos] <= 102))) { /* a-f */
                            parser->pos = start;
                            return JSMN_ERROR_INVAL;
                        }
                        parser->pos++;
                    }
                    parser->pos--;
                    break;
                    /* Unexpected symbol */
                default:
                    parser->pos = start;
                    return JSMN_ERROR_INVAL;
            }
        }
    }
    parser->pos = start;
    return JSMN_ERROR_PART;
}

/**
 * Parse JSON string and fill tokens.
 */
JSMN_API int jsmn_parse(jsmn_parser *parser, const char *js, const size_t len,
                        jsmntok_t *tokens, const unsigned int num_tokens) {
    int r;
    int i;
    jsmntok_t *token;
    int count = parser->toknext;

    for (; parser->pos < len && js[parser->pos] != '\0'; parser->pos++) {
        char c;
        jsmntype_t type;

        c = js[parser->pos];
        switch (c) {
            case '{':
            case '[':
                count++;
                if (tokens == NULL) {
                    break;
                }
                token = jsmn_alloc_token(parser, tokens, num_tokens);
                if (token == NULL) {
                    return JSMN_ERROR_NOMEM;
                }
                if (parser->toksuper != -1) {
                    jsmntok_t *t = &tokens[parser->toksuper];
#ifdef JSMN_STRICT
                    /* In strict mode an object or array can't become a key */
        if (t->type == JSMN_OBJECT) {
          return JSMN_ERROR_INVAL;
        }
#endif
                    t->size++;
#ifdef JSMN_PARENT_LINKS
                    token->parent = parser->toksuper;
#endif
                }
                token->type = (c == '{' ? JSMN_OBJECT : JSMN_ARRAY);
                token->start = parser->pos;
                parser->toksuper = parser->toknext - 1;
                break;
            case '}':
            case ']':
                if (tokens == NULL) {
                    break;
                }
                type = (c == '}' ? JSMN_OBJECT : JSMN_ARRAY);
#ifdef JSMN_PARENT_LINKS
                if (parser->toknext < 1) {
        return JSMN_ERROR_INVAL;
      }
      token = &tokens[parser->toknext - 1];
      for (;;) {
        if (token->start != -1 && token->end == -1) {
          if (token->type != type) {
            return JSMN_ERROR_INVAL;
          }
          token->end = parser->pos + 1;
          parser->toksuper = token->parent;
          break;
        }
        if (token->parent == -1) {
          if (token->type != type || parser->toksuper == -1) {
            return JSMN_ERROR_INVAL;
          }
          break;
        }
        token = &tokens[token->parent];
      }
#else
                for (i = parser->toknext - 1; i >= 0; i--) {
                    token = &tokens[i];
                    if (token->start != -1 && token->end == -1) {
                        if (token->type != type) {
                            return JSMN_ERROR_INVAL;
                        }
                        parser->toksuper = -1;
                        token->end = parser->pos + 1;
                        break;
                    }
                }
                /* Error if unmatched closing bracket */
                if (i == -1) {
                    return JSMN_ERROR_INVAL;
                }
                for (; i >= 0; i--) {
                    token = &tokens[i];
                    if (token->start != -1 && token->end == -1) {
                        parser->toksuper = i;
                        break;
                    }
                }
#endif
                break;
            case '\"':
                r = jsmn_parse_string(parser, js, len, tokens, num_tokens);
                if (r < 0) {
                    return r;
                }
                count++;
                if (parser->toksuper != -1 && tokens != NULL) {
                    tokens[parser->toksuper].size++;
                }
                break;
            case '\t':
            case '\r':
            case '\n':
            case ' ':
                break;
            case ':':
                parser->toksuper = parser->toknext - 1;
                break;
            case ',':
                if (tokens != NULL && parser->toksuper != -1 &&
                    tokens[parser->toksuper].type != JSMN_ARRAY &&
                    tokens[parser->toksuper].type != JSMN_OBJECT) {
#ifdef JSMN_PARENT_LINKS
                    parser->toksuper = tokens[parser->toksuper].parent;
#else
                    for (i = parser->toknext - 1; i >= 0; i--) {
                        if (tokens[i].type == JSMN_ARRAY || tokens[i].type == JSMN_OBJECT) {
                            if (tokens[i].start != -1 && tokens[i].end == -1) {
                                parser->toksuper = i;
                                break;
                            }
                        }
                    }
#endif
                }
                break;
#ifdef JSMN_STRICT
                /* In strict mode primitives are: numbers and booleans */
    case '-':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case 't':
    case 'f':
    case 'n':
      /* And they must not be keys of the object */
      if (tokens != NULL && parser->toksuper != -1) {
        const jsmntok_t *t = &tokens[parser->toksuper];
        if (t->type == JSMN_OBJECT ||
            (t->type == JSMN_STRING && t->size != 0)) {
          return JSMN_ERROR_INVAL;
        }
      }
#else
                /* In non-strict mode every unquoted value is a primitive */
            default:
#endif
                r = jsmn_parse_primitive(parser, js, len, tokens, num_tokens);
                if (r < 0) {
                    return r;
                }
                count++;
                if (parser->toksuper != -1 && tokens != NULL) {
                    tokens[parser->toksuper].size++;
                }
                break;

#ifdef JSMN_STRICT
                /* Unexpected char in strict mode */
    default:
      return JSMN_ERROR_INVAL;
#endif
        }
    }

    if (tokens != NULL) {
        for (i = parser->toknext - 1; i >= 0; i--) {
            /* Unmatched opened object or array */
            if (tokens[i].start != -1 && tokens[i].end == -1) {
                return JSMN_ERROR_PART;
            }
        }
    }

    return count;
}

/**
 * Creates a new parser based over a given buffer with an array of tokens
 * available.
 */
JSMN_API void jsmn_init(jsmn_parser *parser) {
    parser->pos = 0;
    parser->toknext = 0;
    parser->toksuper = -1;
}

#endif /* JSMN_HEADER */

#ifdef __cplusplus
}
#endif

#endif /* JSMN_H */
//endregion

// region JSON
#define MAX_LINE_SIZE 255
char* readJson(FILE* stream) {
    rewind(stream);
    char* request = malloc(255);

    char* line = malloc(255);;
    int8_t opened, closed;

    fgets(request, MAX_LINE_SIZE, stream);
    opened = countCharInString('{', request);
    closed = countCharInString('}', request);

    while (opened < 1 || closed < opened) {
        fgets(line, MAX_LINE_SIZE, stream);
        char* tmp = concat(request, line);
        free(request);
        request = tmp;
        opened = countCharInString('{', request);
        closed = countCharInString('}', request);
    }

    free(line);
    return request;
}

bool isTokenEqualsString(const char *json, jsmntok_t tok, const char *b) {
    int8_t size = (int8_t)(tok.end - tok.start);
    if(size != strlen(b)) return false;

    for(int8_t i = 0; i < size; i++) {
        if(json[tok.start + i] != b[i]) return false;
    }
    return true;
}

const char* boolToString(bool boolean) {
    return boolean
           ? "true"
           : "false";
}

int getIntFromJson(char* json, jsmntok_t tok) {
    if(tok.type != JSMN_PRIMITIVE) return INT8_MIN;
    char first = json[tok.start];
    bool isInteger = first == '-' || (first >= '0' && first <= '9');
    if(!isInteger) return INT8_MIN;
    int size = tok.end - tok.start;
    char* str = malloc(size + 1);
    strncpy(str, json+tok.start, size);
    int integer = atoi(str);
    free(str);
    return integer;
}
// endregion

//region JSON-ACTION
ActionParseResult actionOK(Action action);
ActionParseResult actionKO(enum Error err);
Mark playerNumberToMark(char n);
ActionParseResult actionFromJson(char* json);

ActionParseResult listenPlayerAction(Mark player, FILE* stream) {
    char* json = readJson(stream);
    ActionParseResult result = actionFromJson(json);
    free(json);

    if(isError(result.error)) return result;
    if(result.action.player != player) return actionKO(MISSING_ACTION);
    Action a = result.action;
    if(a.x < 0 || a.x > 2 || a.y < 0 || a.y > 2) return actionKO(OUT_OF_ZONE);

    return result;
}

ActionParseResult actionFromJson(char* json) {
    jsmn_parser p;
    jsmn_init(&p);
    int needed = jsmn_parse(&p, json, strlen(json), NULL, 15);
    if(needed < 10) return actionKO(MISSING_ARGUMENT);

    jsmntok_t t[needed];
    jsmn_init(&p);
    jsmn_parse(&p, json, strlen(json), t, needed);

    if(!isTokenEqualsString(json, t[1], "actions")) return actionKO(BAD_FORMAT);
    if(t[2].type != JSMN_ARRAY) return actionKO(BAD_FORMAT);
    if(t[2].size != 1) return actionKO(BAD_FORMAT);

    int x = getIntFromJson(json,t[7]);
    int y = getIntFromJson(json,t[9]);

    if(x == INT8_MIN) return actionKO(BAD_FORMAT);
    if(y == INT8_MIN) return actionKO(BAD_FORMAT);

    Action action = {
            playerNumberToMark(json[t[5].start]),
            x / 100,
            y / 100,
    };

    return actionOK(action);
}


ActionParseResult actionKO(enum Error error) {
    ActionParseResult ko = {{0,0,0}, error};
    return ko;
}

ActionParseResult actionOK(Action action) {
    ActionParseResult ok = {action, NO_ERROR};
    return ok;
}

Mark playerNumberToMark(char n) {
    switch (n) {
        case '1': return X;
        case '2': return O;
        default: return EMPTY;
    }
}
//endregion

// region JSON-INIT
InitParseResult initKO(enum Error err);
InitParseResult initOK(Init init);

InitParseResult fromJson(const char* json) {
    jsmn_parser p;
    jsmn_init(&p);
    int needed = jsmn_parse(&p, json, strlen(json), NULL, 10);
    if(needed < 5) return initKO(MISSING_ARGUMENT);

    jsmntok_t t[needed];
    jsmn_init(&p);
    jsmn_parse(&p, json, strlen(json), t, needed);

    if(!isTokenEqualsString(json, t[1], "init")) return initKO(BAD_FORMAT);
    if(!isTokenEqualsString(json, t[3], "players")) return initKO(MISSING_ARGUMENT);
    if(!isTokenEqualsString(json, t[4], "2")) return initKO(INCORRECT_VALUE);
    if(needed > 5) return initKO(UNEXPECTED_ARGUMENT);

    Init init = {2};
    return initOK(init);
}


InitParseResult initKO(enum Error err) {
    InitParseResult res = {{0},err};
    return res;
}

InitParseResult initOK(Init init) {
    InitParseResult res = {init, NO_ERROR};
    return res;
}
// endregion

// region JSON-INSTRUCTION

#define MAX_INSTRUCTION_SIZE 2600

char *getJsonDisplay(Grid grid);
char* buildInstructionForGrid(Grid grid);
char *getJsonMarksDisplayFromGrid(Grid grid);
char *getJsonMarkDisplayForMarkAtPosition(Mark mark, int8_t x, int8_t y);
const char* getScoreJson(Mark winner);
char* getJsonAction(Grid grid);
char* getJsonZones(Grid grid);
char* getJsonZone(int8_t x, int8_t y);

const char * const instructionFormat =   "{\n"
                                         "    \"displays\":[{%s, \"player\":1},{%s, \"player\":2}],\n"
                                         "    \"requested_actions\":[%s],\n"
                                         "    \"game_state\":{\n"
                                         "        \"scores\": %s,\n"
                                         "        \"game_over\": %s\n"
                                         "    }\n"
                                         "}";
char* buildInstructionForGrid(Grid grid) {
    char* instruction = malloc(MAX_INSTRUCTION_SIZE);
    char* display = getJsonDisplay(grid);
    char* action = getJsonAction(grid);
    sprintf(instruction, instructionFormat,
            display, display,
            action,
            getScoreJson(getWinner(grid)),
            boolToString(isGameOver(grid))
    );

    free(display);
    free(action);
    return instruction;
}

const char* const displaysFormat = "\n"
                                   "      \"width\": \"300\",\n"
                                   "      \"height\": \"300\",\n"
                                   "      \"content\": [\n"
                                   "        {\n"
                                   "          \"tag\": \"style\",\n"
                                   "          \"content\": \"line{stroke:black;stroke-width:4;}\"\n"
                                   "        },\n"
                                   "        {\n"
                                   "          \"tag\": \"line\",\n"
                                   "          \"x1\": \"0\",\n"
                                   "          \"y1\": \"100\",\n"
                                   "          \"x2\": \"300\",\n"
                                   "          \"y2\": \"100\"\n"
                                   "        },\n"
                                   "        {\n"
                                   "          \"tag\": \"line\",\n"
                                   "          \"x1\": \"100\",\n"
                                   "          \"y1\": \"0\",\n"
                                   "          \"x2\": \"100\",\n"
                                   "          \"y2\": \"300\"\n"
                                   "        },\n"
                                   "        {\n"
                                   "          \"tag\": \"line\",\n"
                                   "          \"x1\": \"0\",\n"
                                   "          \"y1\": \"200\",\n"
                                   "          \"x2\": \"300\",\n"
                                   "          \"y2\": \"200\"\n"
                                   "        },\n"
                                   "        {\n"
                                   "          \"tag\": \"line\",\n"
                                   "          \"x1\": \"200\",\n"
                                   "          \"y1\": \"0\",\n"
                                   "          \"x2\": \"200\",\n"
                                   "          \"y2\": \"300\"\n"
                                   "        }\n"
                                   "      ]%s";
char* getJsonDisplay(Grid grid) {
    char* display = malloc(1900);
    char* marks = getJsonMarksDisplayFromGrid(grid);
    snprintf(display, 1900, displaysFormat, marks);

    free(marks);
    return display;
}

char *getJsonMarksDisplayFromGrid(Grid grid) {
    char* json = NULL;
    for(int8_t x = 0; x < 3; x += 1) {
        for(int8_t y = 0; y < 3; y += 1) {
            if(!grid.marks[y][x]) continue;

            char* markJson = getJsonMarkDisplayForMarkAtPosition(grid.marks[y][x], x, y);
            append(&json, markJson);
        }
    }
    return json;
}

const char* const markDisplayJsonFormat = ",\n"
                                          "        {\n"
                                          "          \"tag\": \"circle\",\n"
                                          "          \"cx\": \"%d\",\n"
                                          "          \"cy\": \"%d\",\n"
                                          "          \"r\": \"33\",\n"
                                          "          \"fill\": \"%s\"\n"
                                          "        }";
char *getJsonMarkDisplayForMarkAtPosition(Mark mark, int8_t x, int8_t y) {
    char* json = malloc(150);
    strcpy(json,"");

    if(mark == EMPTY) return json;

    const char* const color = mark == X ? "blue" : "red";
    snprintf(json, 150, markDisplayJsonFormat,
             (int) ((0.5+x) * 100),
             (int) ((0.5+y) * 100),
             color);

    return json;
}

const char* const actionFormat = "{\n"
                                 "      \"type\": \"CLICK\",\n"
                                 "      \"player\": %d,\n"
                                 "      \"zones\": [%s]\n"
                                 "    }";
char* getJsonAction(Grid grid) {
    char* action = malloc(MAX_INSTRUCTION_SIZE);
    char* zones = getJsonZones(grid);

    snprintf(action, MAX_INSTRUCTION_SIZE, actionFormat, grid.currentPlayer, zones);

    free(zones);
    return action;
}

char* getJsonZones(Grid grid) {
    char* zones = malloc(2);
    strlcpy(zones, "\n", 2);

    for(int8_t x = 0; x < 3; x += 1) {
        for(int8_t y = 0; y < 3; y +=1) {
            if(grid.marks[y][x] != EMPTY) continue;

            char* zone = getJsonZone(x, y);
            append(&zones, zone);
            if(x != 2 || y != 2) append(&zones, ",");
            append(&zones, "\n");

            free(zone);
        }
    }
    return zones;
}


const char* const zoneFormat = "        {\n"
                               "          \"x\": %d,\n"
                               "          \"y\": %d,\n"
                               "          \"width\": 100,\n"
                               "          \"height\": 100\n"
                               "        }";
char* getJsonZone(int8_t x, int8_t y) {
    char* zone = malloc(128);
    sprintf(zone, zoneFormat, x * 100, y * 100);
    return zone;
}

const char* getScoreJson(Mark winner) {
    switch (winner) {
        case X: return "[1,0]";
        case O: return "[0,1]";
        default: return "[0,0]";
    }
}
// endregion

// region CLI

typedef struct CLI {
    Grid grid;
    enum Error error;
} CLI;

CLI newCLI(Grid grid);
CLI start(CLI cli);
InitParseResult init(FILE* stream);
char markToChar(Mark m);
void printGrid(Grid g);
Grid applyActionOnGrid(Action action, Grid grid);

CLI newCLI(Grid grid) {
    CLI cli = {grid, NO_ERROR};
    return cli;
}

CLI start(CLI cli) {
    if(!isError(cli.error)) {
        char* instruction = buildInstructionForGrid(cli.grid);
        fputs(instruction, stdout);
        fputc('\n', stdout);
        free(instruction);
    }

    ActionParseResult result = listenPlayerAction(cli.grid.currentPlayer, stdin);
    if(isError(result.error)) {
        fprintf(stdout, "Error: %d\n", result.error);
        return start((CLI) {cli.grid, result.error});
    }

    Grid gridNextTurn = applyActionOnGrid(result.action, cli.grid);

    if(isGameOver(gridNextTurn)) {
        char* finalInstruction = buildInstructionForGrid(gridNextTurn);
        fputs(finalInstruction, stdout);
        free(finalInstruction);
        return (CLI){gridNextTurn};
    } else {
        CLI cliNextTurn = {gridNextTurn};
        return start(cliNextTurn);
    }
}


InitParseResult init(FILE* stream) {
    char* request = readJson(stream);
    InitParseResult result = fromJson(request);

    free(request);
    return result;
}

Grid applyActionOnGrid(Action action, Grid grid) {
    grid = placeOnGrid(grid, action.player, action.x, action.y);
    grid = switchPlayer(grid);
    return grid;
}


void printGrid(Grid g) {
    printf(" %c | %c | %c \n"
           "---+---+---\n"
           " %c | %c | %c \n"
           "---+---+---\n"
           " %c | %c | %c \n",
           markToChar(g.marks[0][0]), markToChar(g.marks[0][1]), markToChar(g.marks[0][2]),
           markToChar(g.marks[1][0]), markToChar(g.marks[1][1]), markToChar(g.marks[1][2]),
           markToChar(g.marks[2][0]), markToChar(g.marks[2][1]), markToChar(g.marks[2][2])
    );
}

char markToChar(Mark m) {
    switch (m) {
        case EMPTY: return ' ';
        case X: return 'X';
        case O: return 'O';
    }
}

// endregion

// endregion

int main(int argc, char* argv[]) {
    Grid grid = emptyGrid(X);
    CLI cli = newCLI(grid);

    InitParseResult initResult = init(stdin);

    if(initResult.error == NO_ERROR) start(cli);
    else printf("ERROR: %d\n", initResult.error);
    return EXIT_SUCCESS;
}
