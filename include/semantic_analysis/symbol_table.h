#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef enum symbol_type{
    INT,
    FUN,
    NOT_FOUND,
    TOTAL_SYMBOLS,
} SymbolType;

typedef struct symbol {
    char* name;
    SymbolType type;
    struct symbol* next;
} Symbol;


void insert_symbol( Symbol** table, char* name, SymbolType type);
SymbolType look_up_symbol( Symbol* table, char* name );
void free_symbol_table( Symbol* table );

#endif 
