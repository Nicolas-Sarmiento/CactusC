#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef enum symbol_type{
    INT,
    TOTAL_SYMBOLS,
} SymbolType;

typedef struct symbol {
    char* name;
    SymbolType type;
    Symbol* next;
} Symbol;

void insert_symbol( Symbol* table, char* name, SymbolType type);
SymbolType look_up_symbol( Symbol* table, char* name );

#endif 