#include <stdlib.h>
#include <string.h>
#include "semantic_analysis/symbol_table.h"

void insert_symbol( Symbol** table, char* name, SymbolType type){
    Symbol* new_symbol = (Symbol*) malloc( sizeof(Symbol));
    new_symbol->name = strdup(name);
    new_symbol->type = type;
    new_symbol->next = *table;
    *table = new_symbol;
}

SymbolType look_up_symbol( Symbol* table, char* name ){
    for( Symbol* symbol = table; symbol != NULL; symbol = symbol->next){
        if ( strcmp(symbol->name, name) == 0){
            return symbol->type;
        }
    }
    return NOT_FOUND;
}

void free_symbol_table( Symbol* table ){
    Symbol* current = table;
    Symbol* next;
    while (current){
        next = current->next;
        free(current->name);
        free(current->next);
        free(current);
        current = next;
    }
}
