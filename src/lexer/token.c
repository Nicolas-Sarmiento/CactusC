#include <stdio.h>
#include "lexer/token.h"

const char* tokentypes[] = {
    "TOKEN_EOF",
    "TOKEN_ID",
    "TOKEN_INT",
    "TOKEN_IF",
    "TOKEN_WHILE",
    "TOKEN_RETURN",
    "TOKEN_PLUS",
    "TOKEN_MINUS",
    "TOKEN_TIMES",
    "TOKEN_AND",
    "TOKEN_OR",
    "TOKEN_LP",
    "TOKEN_RP",
    "TOKEN_LB",
    "TOKEN_RB",
    "TOKEN_EQ",
    "TOKEN_NEQ",
    "TOKEN_GT",
    "TOKEN_NOT",
    "TOKEN_ASSG",
    "TOKEN_LITERAL",
    "TOKEN_NUMBER",
    "TOKEN_SMCL",
    "INVALID_TOKEN"
};
void printToken( Token token){
    printf("<%s, %s, %d >\n", tokentypes[token.type], token.value, token.number);
}