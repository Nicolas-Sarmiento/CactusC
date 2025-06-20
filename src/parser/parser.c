#include <stdlib.h>
#include <string.h>
#include "parser/parser.h"
#include "parser/tokenstream.h"
#include "error_handler/error_handler.h"

#include<stdio.h>
#include "lexer/token.h"

ParseResult parse_block( TokenStream* stream);
ParseResult parse_stmt( TokenStream* stream);
ParseResult parse_var_init( TokenStream* stream);
ParseResult parse_var_decl( TokenStream* stream);
ParseResult parse_if( TokenStream* stream);
ParseResult parse_while( TokenStream* stream);
ParseResult parse_return( TokenStream* stream);
ParseResult parse_print( TokenStream* stream);
ParseResult parse_expr( TokenStream* stream);
ParseResult parse_expr_or( TokenStream* stream);
ParseResult parse_expr_and( TokenStream* stream);
ParseResult parse_equality( TokenStream* stream);
ParseResult parse_factor( TokenStream* stream);
ParseResult parse_term( TokenStream* stream);
ParseResult parse_unary( TokenStream* stream);
ParseResult parse_primary( TokenStream* stream);


ParseResult parse_program(TokenStream* stream){
    //expect int ID () <block>
    ParseResult p_result;
    Result result_subparse;
    char* name;
    Token_type tokens[] = { TOKEN_INT, TOKEN_ID, TOKEN_LP, TOKEN_RP };
    for (size_t i = 0; i < 4; i++ ){
        result_subparse = expect( stream, tokens[i] );
        if ( result_subparse.code != OK ){
            p_result.result = result_subparse;
            return p_result;
        }
        if ( tokens[i] == TOKEN_ID ){
            name = strdup(peek(stream).value);
        }
        advance(stream);
    }

    ParseResult block_ast = parse_block(stream);

    if ( block_ast.result.code != OK ){
        p_result.result = block_ast.result;
        return p_result;
    }
    p_result.result.code = OK;
    ASTNode* node = new_fun_def(name, block_ast.node);
    p_result.node = node;
    return p_result;
}

ParseResult parse_block( TokenStream* stream){
    // Expect { <stmts> }
    ParseResult p_result;
    Result result_subparse;
    result_subparse = expect( stream, TOKEN_LB );
    if ( result_subparse.code != OK ){
        p_result.result = result_subparse;
        return p_result;
    }
    advance(stream);

    size_t capacity = 8;
    ASTNode** stmts = malloc(capacity * sizeof(ASTNode*));
    size_t count = 0;

    while (peek(stream).type != TOKEN_RB && peek(stream).type != TOKEN_EOF) {

        ParseResult stmt_result = parse_stmt(stream);
        if (stmt_result.result.code != OK) {

            for (size_t i = 0; i < count; i++) {
                free_ast(stmts[i]);
            }
            free(stmts);
            return stmt_result;
        }

        if (count >= capacity) {
            capacity *= 2;
            stmts = realloc(stmts, capacity * sizeof(ASTNode*));
        }

        stmts[count++] = stmt_result.node;
    }

    result_subparse = expect( stream, TOKEN_RB );
    if ( result_subparse.code != OK ){
        p_result.result = result_subparse;
        return p_result;
    }
    advance(stream);
    p_result.result.code = OK;
    ASTNode* node = new_block_stmt(stmts, count);
    p_result.node = node;
    return p_result;
}

ParseResult parse_stmt( TokenStream* stream){
    switch ( peek(stream).type)
    {
    case TOKEN_ID:
        if (strcmp(peek(stream).value, "print") == 0) {
            return parse_print(stream);
        }
        return parse_var_decl(stream);

    case TOKEN_INT:
        return parse_var_init(stream);

    case TOKEN_IF:
        return parse_if(stream);    

    case TOKEN_WHILE:
        return parse_while(stream);
    
    case TOKEN_RETURN:
        return parse_return(stream);
    default:
        break;
    }

    ParseResult error = {
        
        .result = { .code = ERR_SYNTAX, .message = "Invalid statement! xd"}
    };
    return error;
}

ParseResult parse_var_init( TokenStream* stream){
    ParseResult p_result;
    Result res;
    res = expect(stream, TOKEN_INT);
    if (res.code != OK) {
        p_result.result = res;
        return p_result;
    }
    advance(stream);
    res = expect(stream, TOKEN_ID);
    if (res.code != OK) {
        p_result.result = res;
        return p_result;
    }
    char* name = strdup(peek(stream).value);
    advance(stream);

    ASTNode* init_expr = NULL;

    if (peek(stream).type == TOKEN_ASSG) {
        advance(stream);
        ParseResult expr_res = parse_expr(stream); 
        if (expr_res.result.code != OK) {
            p_result.result = expr_res.result;
            return p_result;
        }
        init_expr = expr_res.node;
    }

    res = expect(stream, TOKEN_SMCL);
    if (res.code != OK) {
        p_result.result = res;
        return p_result;
    }
    advance(stream);

    ASTNode* node = new_var_decl(name, init_expr);

    p_result.result.code = OK;
    p_result.node = node;
    return p_result;
}

ParseResult parse_var_decl( TokenStream* stream){
    ParseResult p_result;
    Result res;

    res = expect(stream, TOKEN_ID);
    if (res.code != OK) {
        p_result.result = res;
        return p_result;
    }
    char* name = strdup(peek(stream).value);
    advance(stream);

    ASTNode* init_expr = NULL;

    res = expect(stream, TOKEN_ASSG);
    if (res.code != OK) {
        p_result.result = res;
        return p_result;
    }
    advance(stream);

    ParseResult expr_res = parse_expr(stream); 
    if (expr_res.result.code != OK) {
        p_result.result = expr_res.result;
        return p_result;
    }
    init_expr = expr_res.node;

    res = expect(stream, TOKEN_SMCL);
    if (res.code != OK) {
        p_result.result = res;
        return p_result;
    }
    advance(stream);

    ASTNode* node = new_assign(name, init_expr);

    p_result.result.code = OK;
    p_result.node = node;
    return p_result;
}

ParseResult parse_if( TokenStream* stream){
    ParseResult p_result;
    Result res;

    res = expect(stream, TOKEN_IF);
    if (res.code != OK) {
        p_result.result = res;
        return p_result;
    }
    advance(stream);

    
    res = expect(stream, TOKEN_LP);
    if (res.code != OK) {
        p_result.result = res;
        return p_result;
    }
    advance(stream);
    ASTNode* condition = NULL;
    ParseResult expr_res = parse_expr(stream); 
    if (expr_res.result.code != OK) {
        p_result.result = expr_res.result;
        return p_result;
    }
    condition = expr_res.node;

    res = expect(stream, TOKEN_RP);
    if (res.code != OK) {
        p_result.result = res;
        return p_result;
    }
    advance(stream);

    ASTNode* body = NULL;
    expr_res = parse_block(stream); 
    if (expr_res.result.code != OK) {
        p_result.result = expr_res.result;
        return p_result;
    }

    body = expr_res.node;

    ASTNode* node = new_if_stmt(condition, body);

    p_result.result.code = OK;
    p_result.node = node;
    return p_result;
}

ParseResult parse_while( TokenStream* stream){
    ParseResult p_result;
    Result res;

    res = expect(stream, TOKEN_WHILE);
    if (res.code != OK) {
        p_result.result = res;
        return p_result;
    }
    advance(stream);

    
    res = expect(stream, TOKEN_LP);
    if (res.code != OK) {
        p_result.result = res;
        return p_result;
    }
    advance(stream);
    ASTNode* condition = NULL;
    ParseResult expr_res = parse_expr(stream); 
    if (expr_res.result.code != OK) {
        p_result.result = expr_res.result;
        return p_result;
    }
    condition = expr_res.node;

    res = expect(stream, TOKEN_RP);
    if (res.code != OK) {
        p_result.result = res;
        return p_result;
    }
    advance(stream);

    ASTNode* body = NULL;
    expr_res = parse_block(stream); 
    if (expr_res.result.code != OK) {
        p_result.result = expr_res.result;
        return p_result;
    }

    body = expr_res.node;

    ASTNode* node = new_while_stmt(condition, body);

    p_result.result.code = OK;
    p_result.node = node;
    return p_result;
}

ParseResult parse_return( TokenStream* stream){
    ParseResult p_result;
    Result res;
    res = expect(stream, TOKEN_RETURN);
    if (res.code != OK) {
        p_result.result = res;
        return p_result;
    }
    advance(stream);
    ParseResult expr = parse_expr(stream);
    if ( expr.result.code != OK ){
        p_result.result = expr.result;
        return p_result;
    }

    res = expect(stream, TOKEN_SMCL);
    if (res.code != OK) {
        p_result.result = res;
        return p_result;
    }
    advance(stream);
    ASTNode* expr_node = expr.node;
    ASTNode* return_node = new_return(expr_node);
    p_result.node = return_node;
    p_result.result.code = OK;
    return p_result;
}

// Modify then for all functions
ParseResult parse_print( TokenStream* stream){
    ParseResult p_result;
    Result res;

    res = expect(stream, TOKEN_ID);
    if (res.code != OK) {
        p_result.result = res;
        return p_result;
    }
    char* name = strdup(peek(stream).value);
    if( strcmp(name, "print") != 0){
        res.code = ERR_SEMANTICAL;
        strcpy( res.message,"Only print function is avaliable for now!");
        p_result.result = res;
        return p_result;
    }
    advance(stream);

    
    res = expect(stream, TOKEN_LP);
    if (res.code != OK) {
        p_result.result = res;
        return p_result;
    }
    advance(stream);
    ASTNode* expr;
    Token tk = peek(stream);
    if( tk.type == TOKEN_LITERAL ){
        expr = new_str_literal(tk.value);
        advance(stream);
    }else {
        ParseResult r = parse_expr(stream);
        if( r.result.code != OK ){
            return r;
        }
        expr = r.node;
    }
    
 
    res = expect(stream, TOKEN_RP);
    if (res.code != OK) {
        p_result.result = res;
        return p_result;
    }
    advance(stream);

    res = expect(stream, TOKEN_SMCL);
    if (res.code != OK) {
        p_result.result = res;
        return p_result;
    }
    advance(stream);

    p_result.result.code = OK;
    ASTNode* print_node = new_print(expr);
    p_result.node = print_node;
    return p_result;
}

ParseResult parse_expr( TokenStream* stream){
    return parse_expr_or(stream);
}

ParseResult parse_expr_or( TokenStream* stream){
    ParseResult left = parse_expr_and(stream);
    if (left.result.code != OK) return left;

    while (peek(stream).type == TOKEN_OR) {
        advance(stream);
        ParseResult right = parse_expr_and(stream);
        if (right.result.code != OK) {
            free_ast(left.node);
            return right;
        }
        ASTNode* node = new_binary_op("||", left.node, right.node);
        left.node = node;
    }

    return left;
}

ParseResult parse_expr_and( TokenStream* stream){
    ParseResult left = parse_equality(stream);
    if (left.result.code != OK) return left;

    while (peek(stream).type == TOKEN_AND) {
        advance(stream);
        ParseResult right = parse_equality(stream);
        if (right.result.code != OK) {
            free_ast(left.node);
            return right;
        }
        ASTNode* node = new_binary_op("&&", left.node, right.node);
        left.node = node;
    }

    return left;
}

ParseResult parse_equality( TokenStream* stream){
    ParseResult left = parse_factor(stream);
    if (left.result.code != OK) return left;

    while (1) {
        Token tok = peek(stream);
        char* op;

        if (tok.type == TOKEN_EQ) {
            op = strdup("==");
        } else if (tok.type == TOKEN_NEQ) {
            op = strdup("!=");
        } else if (tok.type == TOKEN_GT) {
            op =  strdup(">");
        } else {
            break; 
        }

        advance(stream);

        ParseResult right = parse_factor(stream);
        if (right.result.code != OK) {
            free_ast(left.node);
            return right;
        }

        ASTNode* node = new_binary_op(op, left.node, right.node);

        left.node = node; 
    }

    return left;
}

ParseResult parse_factor( TokenStream* stream){
    ParseResult left = parse_term(stream);
    if (left.result.code != OK) return left;

    while (1) {
        Token tok = peek(stream);
        char* op;

        if (tok.type == TOKEN_PLUS) {
            op = strdup("+");
        } else if (tok.type == TOKEN_MINUS) {
            op = strdup("-");
        }  else {
            break; 
        }

        advance(stream);

        ParseResult right = parse_term(stream);
        if (right.result.code != OK) {
            free_ast(left.node);
            return right;
        }

        ASTNode* node = new_binary_op(op, left.node, right.node);

        left.node = node; 
    }

    return left;
}

ParseResult parse_term( TokenStream* stream){
    ParseResult left = parse_unary(stream);
    if (left.result.code != OK) return left;

    while (1) {
        Token tok = peek(stream);
        char* op;

        if (tok.type == TOKEN_TIMES) {
            op = strdup("*");
        } else if (tok.type == TOKEN_DIV) {
            op = strdup("/");
        }  else {
            break; 
        }

        advance(stream);

        ParseResult right = parse_unary(stream);
        if (right.result.code != OK) {
            free_ast(left.node);
            return right;
        }

        ASTNode* node = new_binary_op(op, left.node, right.node);

        left.node = node; 
    }

    return left;
}

ParseResult parse_unary( TokenStream* stream){
    Token tok = peek(stream);

    if (tok.type == TOKEN_MINUS || tok.type == TOKEN_NOT) {
        advance(stream);
        
        ParseResult right = parse_unary(stream);
        if (right.result.code != OK) return right;

        char op;
        if (tok.type == TOKEN_MINUS){
            op = '-';
        }
        else{
            op = '!';
        }
        ASTNode* node = new_unary_op(op, right.node);

        ParseResult result = { .result.code = OK, .node = node };
        return result;
    }

    return parse_primary(stream); 
}

ParseResult parse_primary( TokenStream* stream){
    ParseResult p_result;
    Token tk = peek(stream);

    ASTNode* node;
    switch (tk.type)
    {
    case TOKEN_NUMBER :
        node = new_number(tk.number);
        break;
    case TOKEN_ID :
        node = new_id(tk.value);
        break;
    case TOKEN_LP:
        advance(stream);
        ParseResult result = parse_expr(stream);
        if( result.result.code != OK ) return result;
        Result r = expect(stream, TOKEN_RP);
        if ( r.code != OK ){
            p_result.result = r;
            return p_result;
        }
        
        node = new_expr(result.node);
        break;
    default:
        p_result.result.code = ERR_SYNTAX;
        stpcpy(p_result.result.message, "Invalid token found! Expected an ID, Number o valid expression");
        return p_result;
    }
    advance(stream);
    p_result.node = node;
    p_result.result.code = OK;
    return p_result;
}

