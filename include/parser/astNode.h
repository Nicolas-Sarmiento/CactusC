#ifndef ASTNODE_H
#define ASTNODE_H
#include <stdlib.h>
typedef enum {
    AST_NUMBER,
    AST_LITERAL,
    AST_VAR_DECL,
    AST_VAR,
    AST_BINARY_OP,
    AST_UNARY_OP,
    AST_ASSIGN,
    AST_IF,
    AST_WHILE,
    AST_PRINT,
    AST_BLOCK,
    AST_FUNCTION_CALL,
    AST_FUNCTION_DEF,
    AST_RETURN,
    AST_EXPR_STMT,
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;

    union {
        // Numeros
        struct {
            int value;
        } int_literal;

        // Literales
        struct {
            char* value;
        } str_literal;

        // x = expr;
        struct {
            char* name;
            struct ASTNode* expr;
        } assign;

        // int x;
        struct {
            char* name;
        } var_decl;


        // usar variable
        struct {
            char* name;
        } var;

        // expr op expr
        struct {
            char* op; // '+', '-', '*', '/', etc.
            struct ASTNode* left;
            struct ASTNode* right;
        } binary_op;

        // -expr o !expr
        struct {
            char op;
            struct ASTNode* operand;
        } unary_op;

        // if (cond) { then_branch } 
        struct {
            struct ASTNode* condition;
            struct ASTNode* then_branch;
           
        } if_stmt;

        // while (cond) { body }
        struct {
            struct ASTNode* condition;
            struct ASTNode* body;
        } while_stmt;

        // print(expr)
        struct {
            struct ASTNode* expr;
        } print_stmt;

        // secuencia de sentencias
        struct {
            struct ASTNode** statements;
            size_t count;
        } block;

        // int main() { ... }
        struct {
            char* name; 
            struct ASTNode* body;
        } function_def;

        //return
        struct {
            struct ASTNode* expr;
        } expr_stmt;
    };
} ASTNode;


//Definir nodos
ASTNode* new_number(int value);
ASTNode* new_str_literal( const char* literal );
ASTNode* new_assign( const char* literal, ASTNode* value );
ASTNode* new_var_decl( const char* name, ASTNode* value );
ASTNode* new_binary_op( const char* op, ASTNode* left, ASTNode* right );
ASTNode* new_unary_op( const char op, ASTNode* operand );
ASTNode* new_if_stmt( ASTNode* condition, ASTNode* body );
ASTNode* new_while_stmt( ASTNode* condition, ASTNode* body);
ASTNode* new_print( ASTNode* expression);
ASTNode* new_block_stmt( ASTNode** staments, size_t count );
ASTNode* new_fun_def( const char* name, ASTNode* body);
ASTNode* new_stmt( ASTNode* expression );
ASTNode* new_return( ASTNode* expression );

void free_ast(ASTNode* node);

#endif