#include "parser/tokenstream.h"
#include <stdio.h>

Token advance( TokenStream * stream){
    if( stream->pos < stream->lenght){
        return stream->tokens[stream->pos++];
    }
    return stream->tokens[stream->lenght-1];
}

Token peek ( TokenStream * stream){
    if( stream->pos < stream->lenght){
        return stream->tokens[stream->pos];
    }
    return stream->tokens[stream->lenght-1];
}

int match (  TokenStream * stream, Token_type type ) {
    if( peek(stream).type == type){
        advance(stream);
        return 1;
    }
    return 0;
}

int check (  TokenStream * stream, Token_type type ) {
    return peek(stream).type == type;
}

Result expect ( TokenStream * stream, Token_type type ) {
    Result r;
    if( !check(stream, type) ){
        r.code = ERR_SYNTAX;
        char * base = "Expected a token of type ";
        const char* strType = typeToStr(type);
        sprintf(r.message, "%s%s", base, strType);
        return r;
    }
    r.code=OK;
    return r;
}