#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "error_handler/error_handler.h"
#include "lexer/lexer.h"
#include "lexer/regex.h"

#define N_TOKENS 1024


Result lexer(char** lines,const int line_count,  Token** tokenList, size_t* size ){
   
    size_t token_pos = 0;
    size_t tokenListSize = N_TOKENS;
    *tokenList = ( Token * ) malloc( tokenListSize * sizeof( Token) );
    size_t char_i, token_i, token_size;
    int literal_flag = 0;
    for(int i = 0; i < line_count; ++i ){
        char* line = lines[i];
        token_i = 0;
        char_i = 0;
        token_size = 1024;
        char* next_token = (char * ) malloc( token_size );
        literal_flag = 0;
        while ( line[char_i] != '\0') {

            if( token_i >= token_size ){
                token_size *= 2;
                next_token = (char * ) realloc(next_token, token_size);
            }
            if( token_pos >= tokenListSize ){
                tokenListSize *= 2;
                *tokenList = (Token * ) realloc(*tokenList, tokenListSize);
            }

            if( is_not_sep(line[char_i]) || literal_flag){
                next_token[token_i] = line[char_i];
                if (next_token[token_i] == '"') literal_flag = !literal_flag;
                ++token_i;
                ++char_i;
                continue;
            }
            if (token_i > 0) {
                next_token[token_i] = '\0';                
                Token_type tokenType = getTokenType(next_token);
                if( tokenType == INVALID_TOKEN ){
                    Result r;
                    r.code = ERR_LEXICAL;
                    char * base = "Unexpectede token at line ";
                    sprintf(r.message, "%s%d", base, i+1);
                    return r;
                }
                (*tokenList)[token_pos].type = tokenType;
                if ( tokenType == TOKEN_LITERAL || tokenType == TOKEN_ID){
                    (*tokenList)[token_pos].value = strdup(next_token);
                }else if( tokenType == TOKEN_NUMBER ){
                    (*tokenList)[token_pos].number = atoi(next_token);
                }
                token_pos++;
            }
            

            if( line[char_i] != ' ' && line[char_i] != '\n' && line[char_i] != '\t'){
                char tmp[3];
                int ix = 0;
                tmp[ix++] = line[char_i];
                if( is_double_op(line[char_i]) && line[char_i+1] != '\0' ){
                    if( (line[char_i] == '!' && line[char_i+1] == '=') || (line[char_i] != '!' && (line[char_i] == line[char_i + 1]))){
                        tmp[ix++] = line[char_i+1];
                        char_i++;
                    }
                }
                tmp[ix] = '\0';
                Token_type type = getTokenType(tmp);
                if( type == INVALID_TOKEN ){
                    Result r;
                    r.code = ERR_LEXICAL;
                    char * base = "Unexpectede token at line ";
                    sprintf(r.message, "%s%d", base, i+1);
                    return r;
                }
                (*tokenList)[token_pos++].type = type;

            }
            next_token[0] = '\0';
            token_i = 0;
            ++char_i;
        }

        if( token_i > 0 ){
            next_token[token_i] = '\0';
            Token_type tokenType = getTokenType(next_token);
            if( tokenType == INVALID_TOKEN ){
                    Result r;
                    r.code = ERR_LEXICAL;
                    char * base = "Unexpectede token at line ";
                    sprintf(r.message, "%s%d", base, i);
                    return r;
            }
            (*tokenList)[token_pos].type = tokenType;
            if ( tokenType == TOKEN_LITERAL || tokenType == TOKEN_ID){
                (*tokenList)[token_pos].value = strdup(next_token);
            }else if( tokenType == TOKEN_NUMBER ){
                (*tokenList)[token_pos].number = atoi(next_token);
            }
            token_pos++;
        }


        free(next_token);
    
    }
    Token end = { .type= TOKEN_EOF };
    (*tokenList)[token_pos++] = end;
    *size = token_pos;
    Result result = { .code = OK };
    return result;
}