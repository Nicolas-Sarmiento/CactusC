#ifndef SEMANTIC_H
#define SEMANTIC_H
#include "error_handler/error_handler.h"
#include "parser/astNode.h"
#include "semantic_analysis/symbol_table.h"

typedef struct error_list{
    Result status;
    struct error_list* next;
} ErrorList;

typedef struct semantic_result {
    int is_correct;
    Symbol* symbol_table;
    ErrorList* error_list;
} SemanticResult;


SemanticResult semantic_check( ASTNode* node );
void print_error_list( ErrorList* list );
void free_semantic_result( SemanticResult semantic_result );


#endif