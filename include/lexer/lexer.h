#ifndef LEXER_H
#define LEXER_H
#include "error_handler/error_handler.h"
#include "lexer/token.h"


Result lexer(char** lines,const int line_count,  Token** tokenList, size_t* size );

#endif // LEXER_H