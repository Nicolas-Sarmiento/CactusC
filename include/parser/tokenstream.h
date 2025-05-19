
#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H
#include <stdlib.h>
#include "lexer/token.h"
#include "error_handler/error_handler.h"



typedef struct tokenstream{
    Token *tokens;
    size_t pos;
    size_t lenght;
} TokenStream;

Token advance( TokenStream * stream);
Token peek ( TokenStream * stream);
int match (  TokenStream * stream, Token_type type );
int check (  TokenStream * stream, Token_type type );
Result expect ( TokenStream * stream, Token_type type );

#endif 