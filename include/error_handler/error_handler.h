#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <string.h>

typedef enum Status{
   OK,
   ERR_SYNTAX,
   ERR_LEXICAL,
   ERR_SEMANTICAL,
} Status_type;

typedef struct result {
    Status_type code;
    char message [1024]; 
} Result;


void print_error_message(Result status);

#endif 