#include <stdio.h>

#include "semantic_analysis/semantic.h"
#include "semantic_analysis/symbol_table.h"

void add_error(ErrorList** error_list, const char* message ){
    Result r;
    r.code = ERR_SEMANTICAL;
    strncpy(r.message, message, sizeof(r.message)-1);
    r.message[sizeof(r.message)-1] = '\0';

    ErrorList* node = malloc(sizeof(ErrorList));
    node->status = r;
    node->next = NULL;

    if( *error_list == NULL ) {
        *error_list = node;
    }else{
        ErrorList* current = *error_list;
        while ( current -> next != NULL ){
            current = current -> next;
        }
        current->next = node;
    }
}


void semantic_check_node(ASTNode* root, Symbol** table , ErrorList** errors){
    if( !root ) return;

    switch (root->type)
    {
    case AST_ID:
        if ( look_up_symbol( *table,root->str_literal.value) == NOT_FOUND ){
            char msg [1023];
            snprintf(msg, sizeof(msg), "Error: %s variable is undefined!", root->str_literal.value);
            add_error(errors, msg );
        }
        break;
    case AST_FUNCTION_DEF:
        if ( look_up_symbol( *table,root->function_def.name) == FUN ){
            char msg [1023];
            snprintf(msg, sizeof(msg), "Error: %s function has been defined before!", root->function_def.name);
            add_error(errors, msg );
        }else{
            insert_symbol(table, root->function_def.name, FUN);
        }

        semantic_check_node(root->function_def.body, table, errors);
        break;
    case AST_ASSIGN:
        if ( look_up_symbol( *table,root->assign.name) == NOT_FOUND ){
            char msg [1023];
            snprintf(msg, sizeof(msg), "Error: %s variable is undefined!", root->assign.name);
            add_error(errors, msg );
        }

        semantic_check_node(root->assign.expr, table, errors);

        break;
    case AST_VAR_DECL:
        if ( look_up_symbol( *table,root->assign.name) == INT ){
            char msg [1023];
            printf("Hello?\n");
            snprintf(msg, sizeof(msg), "Error: %s variable is already defined!", root->assign.name);
            add_error(errors, msg );
        }else{
            insert_symbol(table, root->assign.name, INT);
        }
        if( root->assign.expr ){
            semantic_check_node(root->assign.expr, table, errors);
        }
        break;
    case AST_VAR:
        if ( look_up_symbol( *table,root->var.name) == NOT_FOUND ){
            char msg [1023];
            snprintf(msg, sizeof(msg), "Error: %s variable is undefined!", root->assign.name);
            add_error(errors, msg );
        }
        break;
    case AST_BINARY_OP:
        semantic_check_node(root->binary_op.left, table, errors);
        semantic_check_node(root->binary_op.right, table, errors);
        break;
    case AST_UNARY_OP:
        semantic_check_node(root->unary_op.operand, table, errors);
        break;
    case AST_IF:
        semantic_check_node(root->if_stmt.condition, table, errors);
        semantic_check_node(root->if_stmt.then_branch, table, errors);
        break;
    case AST_WHILE:
        semantic_check_node(root->while_stmt.condition, table, errors);
        semantic_check_node(root->while_stmt.condition, table, errors);
        break;
    case AST_PRINT:
        semantic_check_node(root->print_stmt.expr, table, errors);
        break;
    case AST_BLOCK:
        for(size_t i = 0; i < root->block.count; ++i ){
            semantic_check_node(root->block.statements[i], table, errors);
        }
        break;
    case AST_EXPR_STMT:
    case AST_RETURN:
        semantic_check_node(root->expr_stmt.expr, table, errors);
        break;    
    case AST_FUNCTION_CALL:
    case AST_NUMBER:
    case AST_LITERAL:
    default:
        break;
    }
}

SemanticResult semantic_check( ASTNode* node ){
    SemanticResult result = { .symbol_table = NULL, .error_list = NULL };

    semantic_check_node(node, &(result.symbol_table) ,&(result.error_list));

    result.is_correct = (result.error_list == NULL);
    return result;
}

void print_error_list( ErrorList* list ){
    ErrorList* current = list;
    while( current != NULL ){
        print_error_message(current->status);
        current = current->next;
    }
}

void free_semantic_result( SemanticResult semantic_result ){
    free_symbol_table(semantic_result.symbol_table);

    while ( semantic_result.error_list != NULL ){
        ErrorList* tmp = semantic_result.error_list;
        semantic_result.error_list = semantic_result.error_list->next;
        free(tmp);
    }
    
}