#include "lexer/token.h"
#ifndef REGEX_H
#define REGEX_H

typedef struct token_pair {
    char* key;
    Token_type value;
} TokenPair;

Token_type getTokenType(const char* key);
int is_not_sep(char c);
int is_double_op(char c);

#endif // REGEX_H