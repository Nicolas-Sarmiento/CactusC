#include <parser/astNode.h>
#include <stdlib.h>
#include <string.h>

ASTNode* new_number(int value){
    ASTNode* node = ( ASTNode* )malloc(sizeof(ASTNode));
    node->type = AST_NUMBER;
    node->int_literal.value = value;
    return node;
}

ASTNode* new_str_literal( const char* literal ){
    ASTNode* node = ( ASTNode* )malloc(sizeof(ASTNode));
    node->type = AST_LITERAL;
    node->str_literal.value = strdup(literal);
    return node;
}

ASTNode* new_assign( const char* literal, ASTNode* value ){
    ASTNode* node = ( ASTNode* )malloc(sizeof(ASTNode));
    node->type = AST_ASSIGN;
    node->assign.name = strdup(literal);
    node->assign.expr = value;
    return node;
}

ASTNode* new_var_decl( const char* name, ASTNode* value ){
    ASTNode* node = ( ASTNode* )malloc(sizeof(ASTNode));
    node->type = AST_VAR_DECL;
    node->assign.name = strdup(name);
    node->assign.expr = value;
    return node;
}

ASTNode* new_binary_op( const char* op, ASTNode* left, ASTNode* right ){
    ASTNode* node = ( ASTNode* )malloc(sizeof(ASTNode));
    node->type = AST_BINARY_OP;
    node->binary_op.op = strdup(op);
    node->binary_op.left = left;
    node->binary_op.right = right;
    return node;
}

ASTNode* new_unary_op( const char op, ASTNode* operand ){
    ASTNode* node = ( ASTNode* )malloc(sizeof(ASTNode));
    node->type = AST_UNARY_OP;
    node->unary_op.op = op;
    node->unary_op.operand = operand;
    return node;
}

ASTNode* new_if_stmt( ASTNode* condition, ASTNode* body ){
    ASTNode* node = ( ASTNode* )malloc(sizeof(ASTNode));
    node->type = AST_IF;
    node->if_stmt.condition = condition;
    node->if_stmt.then_branch = body;
    return node;
}

ASTNode* new_while_stmt( ASTNode* condition, ASTNode* body){
    ASTNode* node = ( ASTNode* )malloc(sizeof(ASTNode));
    node->type = AST_WHILE;
    node->while_stmt.condition = condition;
    node->while_stmt.body = body;
    return node;
}

ASTNode* new_print( ASTNode* expression){
    ASTNode* node = ( ASTNode* )malloc(sizeof(ASTNode));
    node->type = AST_PRINT;
    node->print_stmt.expr = expression;
    return node;
}

ASTNode* new_block_stmt( ASTNode** staments, size_t count ){
    ASTNode* node = ( ASTNode* )malloc(sizeof(ASTNode));
    node->type = AST_BLOCK;
    node->block.statements = staments;
    node->block.count = count;
    return node;
}

ASTNode* new_fun_def( const char* name, ASTNode* body){
    ASTNode* node = ( ASTNode* )malloc(sizeof(ASTNode));
    node->type = AST_FUNCTION_DEF;
    node->function_def.name = strdup(name);
    node->function_def.body = body;
    return node;
}

ASTNode* new_stmt( ASTNode* expression ){
    ASTNode* node = ( ASTNode* )malloc(sizeof(ASTNode));
    node->type = AST_EXPR_STMT;
    node->expr_stmt.expr = expression;
    return node;
}
ASTNode* new_return( ASTNode* expression ){
    ASTNode* node = ( ASTNode* )malloc(sizeof(ASTNode));
    node->type = AST_RETURN;
    node->expr_stmt.expr = expression;
    return node;
}

void free_ast(ASTNode* node){

}