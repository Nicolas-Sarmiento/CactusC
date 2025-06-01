#include <string.h>
#include <stdio.h>
#include "codegen/codegen.h"

int next_label(){
    static int i = 0;
    i++;
    return i-1;
}

void op_to_code(const char *op, char *out, size_t out_size) {
    if (strcmp(op, "+") == 0) {
        snprintf(out, out_size, "ADD");
    } else if (strcmp(op, "-") == 0) {
        snprintf(out, out_size, "SUB");
    } else if (strcmp(op, "*") == 0) {
        snprintf(out, out_size, "MUL");
    } else if (strcmp(op, "/") == 0) {
        snprintf(out, out_size, "DIV");
    } else if (strcmp(op, "&&") == 0) {
        snprintf(out, out_size, "AND");
    } else if (strcmp(op, "||") == 0) {
        snprintf(out, out_size, "OR");
    } else if (strcmp(op, "==") == 0) {
        snprintf(out, out_size, "EQ");
    } else if (strcmp(op, "!=") == 0) {
        snprintf(out, out_size, "NEQ");
    } else if (strcmp(op, ">") == 0) {
        snprintf(out, out_size, "GT");
    } else {
        // Operador no reconocido, cadena vacía
        if (out_size > 0) {
            out[0] = '\0';
        }
    }
}

void generate_expr( ASTNode* node, FILE* out ){
    if (!node ) return;
    switch (node->type)
    {
        case AST_NUMBER:
            fprintf(out, "PUSH %d\n", node->int_literal.value);
            break;
        case AST_LITERAL:
            fprintf(out, "PUSH_STR %s\n", node->str_literal.value);
            break;
        case AST_ID:
            fprintf(out, "LOAD %s\n", node->str_literal.value);
            break;
        case AST_BINARY_OP : {
            generate_expr(node->binary_op.left, out);
            generate_expr(node->binary_op.right, out);
            char s[4];
            op_to_code(node->binary_op.op, s, sizeof(s));
            fprintf(out, "%s\n", s);
            break;
        }
        case AST_UNARY_OP:
            generate_expr(node->unary_op.operand, out);
            fprintf(out, "PUSH 0\n");
            if( node->unary_op.op == '-'){
                fprintf(out, "SUB\n");
            }else if ( node->unary_op.op == '!'){
                fprintf(out,"EQ\n");
            }
            break;
        case AST_EXPR_STMT:
            generate_expr(node->expr_stmt.expr, out);
            break;
        default:
            break;
    }
}

void generate_stmt( ASTNode* node , FILE* out ){
    if ( !node ) return;
    switch (node->type){
        case AST_ASSIGN:
        case AST_VAR_DECL:
            if( node->assign.expr ){
                generate_expr(node->assign.expr, out);
            }else{
                fprintf(out, "PUSH 0\n");
            }
            fprintf(out, "STORE %s\n", node->assign.name);
            break;
        case AST_IF: {
            int lb_num = next_label();
            generate_expr(node->if_stmt.condition, out);
            fprintf(out, "JZ endif_%d\n", lb_num);
            generate_stmt(node->if_stmt.then_branch, out);
            fprintf(out, "LBL endif_%d\n", lb_num);
            break;
        }
        case AST_WHILE:{
            int lb_num = next_label();
            fprintf(out, "LBL while_start_%d\n", lb_num);
            generate_expr(node->while_stmt.condition, out);
            fprintf(out, "JZ while_end_%d\n", lb_num);
            generate_stmt(node->while_stmt.body, out);
            fprintf(out, "JMP while_start_%d\n", lb_num);
            fprintf(out, "LBL while_end_%d\n", lb_num);
            break;
        }
        case AST_PRINT:
            generate_expr(node->print_stmt.expr, out);
            fprintf(out, "PRINT\n");
            break;
        case AST_BLOCK:
            for(size_t i = 0; i < node->block.count; i++){
                generate_stmt(node->block.statements[i], out);
            }
            break;
        case AST_RETURN:
            generate_expr(node->expr_stmt.expr, out);
            fprintf(out, "RET\n");
            break;    
        case AST_FUNCTION_DEF:
            generate_stmt(node->function_def.body, out);
            break;
        case AST_FUNCTION_CALL:
        case AST_VAR:
        default:
            break;
    }
}