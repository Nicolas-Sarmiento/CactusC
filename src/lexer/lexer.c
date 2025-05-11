#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lexer/lexer.h"
#include "error_handler/error_handler.h"
#include "lexer/token.h"

#define N_TOKENS 1024

Result lexer(char** lines,const int line_count,  Token** tokenList, size_t* size ){
    *tokenList = ( Token * ) malloc( N_TOKENS * sizeof( Token) );
    size_t token_pos = 0;
    size_t char_i;
    for(int i = 0; i < line_count; ++i ){
        char* line = lines[i];
        char_i = 0;

        while ( line[char_i] != '\0') {
            printf("%c ", line[char_i]);
            //CONTINUE ...
            ++char_i;
        }
    }
    Result result = { .code = OK };
    return result;
}