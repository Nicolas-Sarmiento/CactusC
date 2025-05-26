//Definir las reglas gramaticales
#ifndef PARSER_H
#define PARSER_H

#include "parser/astNode.h"
#include "parser/tokenstream.h"
#include "error_handler/error_handler.h"

typedef struct parseresult{
    ASTNode* node;
    Result result;
} ParseResult;


ParseResult parse_program(TokenStream* stream);


#endif