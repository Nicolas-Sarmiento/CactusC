#ifndef TOKEN_H
#define TOKEN_H

typedef enum Token_type_enum {
    TOKEN_EOF,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_KEYWORD,
    TOKEN_OPERATOR,
    TOKEN_LITERAL
} Token_type;

typedef struct Token_struct {
    Token_type type;
    char * value;
} Token;

#endif // TOKEN_H