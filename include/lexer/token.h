#include <string.h>
#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_EOF,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_KEYWORD,
    TOKEN_OPERATOR,
    TOKEN_LITERAL
} TokenType;

typedef struct {
    TokenType type;
    char * value;
} Token;

#endif // TOKEN_H