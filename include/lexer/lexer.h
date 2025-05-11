#include "error_handler/error_handler.h"
#include "lexer/token.h"
#ifndef LEXER_H
#define LEXER_H

Result lexer(char** lines,const int line_count,  Token** tokenList, size_t* size );

#endif // LEXER_H