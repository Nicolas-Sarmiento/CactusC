#ifndef ASTNODE_H
#define ASTNODE_H

typedef enum {
    AST_INT_LITERAL,
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
    AST_EXPR_STMT
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
        } int_literal;

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
            char op; // '+', '-', '*', '/', etc.
            struct ASTNode* left;
            struct ASTNode* right;
        } binary_op;

        // -expr o !expr
        struct {
            char op;
            struct ASTNode* operand;
        } unary_op;

        // if (cond) { then_branch } else { else_branch }
        struct {
            struct ASTNode* condition;
            struct ASTNode* then_branch;
            struct ASTNode* else_branch;
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
            int count;
        } block;

        // función main() { ... }
        struct {
            char* name; // solo usarás "main"
            struct ASTNode* body;
        } function_def;

        // expresión sola como sentencia: expr;
        struct {
            struct ASTNode* expr;
        } expr_stmt;
    };
} ASTNode;


#endif