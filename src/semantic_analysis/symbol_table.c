#include <stdlib.h>
#include <string.h>
#include "semantic_analysis/symbol_table.h"

void insert_symbol( Symbol** table, char* name, SymbolType type){
    Symbol* new_symbol = (Symbol*) malloc( sizeof(Symbol));
    new_symbol->name = strdup(name);
    new_symbol->type = type;
    new_symbol->next = table;
    *table = new_symbol;
}

SymbolType look_up_symbol( Symbol* table, char* name ){
    for( Symbol* symbol = table; symbol != NULL; symbol = symbol->next){
        if ( strcmp(symbol->name, name)){
            return symbol->type;
        }
    }
    return NULL;
}
