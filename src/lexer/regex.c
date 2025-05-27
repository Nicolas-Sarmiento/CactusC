#include "lexer/regex.h"
#include "string.h"
#include <ctype.h>
#include <stdio.h>

const TokenPair tokenTable[] ={
    {"if", TOKEN_IF},
    {"while", TOKEN_WHILE},
    {"int", TOKEN_INT},
    {"return", TOKEN_RETURN},
    {"+", TOKEN_PLUS},
    {"-", TOKEN_MINUS},
    {"*", TOKEN_TIMES},
    {"/", TOKEN_DIV},
    {">", TOKEN_GT},
    {"&&", TOKEN_AND},
    {"||", TOKEN_OR},
    {"=", TOKEN_ASSG},
    {"==", TOKEN_EQ},
    {"!=", TOKEN_NEQ},
    {"!", TOKEN_NOT},
    {"(", TOKEN_LP},
    {")", TOKEN_RP},
    {"{", TOKEN_LB},
    {"}", TOKEN_RB},
    {";",TOKEN_SMCL }
};

const size_t size = sizeof(tokenTable)/sizeof(tokenTable[0]);

int valid_char( char c );

Token_type getTokenType(const char* key) {

    if (key[0] == '"') {
        size_t len = strlen(key);
        if (key[len - 1] == '"') {
            return TOKEN_LITERAL;
        } else {
            return INVALID_TOKEN;  
        }
    }

    for (const char* k = key; *k; ++k) {
        if (!valid_char(*k)) return INVALID_TOKEN;
    }

    for (size_t i = 0; i < size; i++) {
        if (strcmp(tokenTable[i].key, key) == 0) {
            return tokenTable[i].value;
        }
    }

    int is_number = 1;  
    for (size_t i = 0; i < strlen(key); i++) {
        if (!isdigit(key[i])) {
            is_number = 0;
            break;
        }
    }

    if (is_number) {
        return TOKEN_NUMBER;
    } else {
        return TOKEN_ID; 
    }
}

int valid_char(char c )  {
    return isalnum(c) || c == '(' || c == ')' ||
           c == '{' || c == '}' ||
           c == ',' || c == ';' ||
           c == '=' || c == '|' ||
           c == '&' || c == '!' || 
           c == '+' || c == '*' || 
           c == ';' || c =='"'  || 
           c == '>' || c == '/' || c == '-';
}

int is_not_sep(char c){
    char specialChars[] = {'\n', '+', '-', '*', '/', ' ', '&', '|', '=', ';', '(', ')', '!', '>','{', '}', '\t'};
    for (size_t i = 0; i < sizeof(specialChars); ++i) {
        if (c == specialChars[i]) {
            return 0; 
        }
    }
    return 1;
}

int is_double_op(char c){
    char specialChars[] = { '&', '|', '=', '!'};
    for (size_t i = 0; i < sizeof(specialChars); ++i) {
        if (c == specialChars[i]) {
            return 1; 
        }
    }
    return 0;
}