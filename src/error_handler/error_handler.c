#include <stdio.h>
#include "error_handler/error_handler.h"
 
void print_error_message(struct result status){

    switch (status.code){
    case OK :
        printf("OK\n");
        return;
    case ERR_SYNTAX:
        printf("Syntax Error!\n");
        break;
    case ERR_LEXICAL:
        printf("Lexical error!\n");
        break;
    case ERR_SEMANTICAL:
        printf("Semantical error!\n");
        break;
    default:
        printf("Err: No ERROR CODE found!\n");
        return;
    }
    printf("message: %s \n", status.message);
}