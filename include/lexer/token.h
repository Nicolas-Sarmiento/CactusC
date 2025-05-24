#ifndef TOKEN_H
#define TOKEN_H

typedef enum Token_type_enum {
    TOKEN_EOF,
    TOKEN_ID,
    TOKEN_INT,
    TOKEN_IF,
    TOKEN_WHILE,
    TOKEN_RETURN,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_TIMES,
    TOKEN_DIV,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_LP,
    TOKEN_RP,
    TOKEN_LB,
    TOKEN_RB,
    TOKEN_EQ,
    TOKEN_NEQ,
    TOKEN_GT,
    TOKEN_NOT,
    TOKEN_ASSG,
    TOKEN_LITERAL,
    TOKEN_NUMBER,
    TOKEN_SMCL,
    INVALID_TOKEN,
    TOTAL_TOKENS,
} Token_type;



typedef struct Token_struct {
    Token_type type;
    char * value;
    int number;
} Token;

void printToken( Token token);
const char* typeToStr( Token_type type );
#endif // TOKEN_H