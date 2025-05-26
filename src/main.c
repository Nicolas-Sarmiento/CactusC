#include <stdio.h>
#include <stdlib.h>
#include "utils/read_file.h"
#include "error_handler/error_handler.h"
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "parser/tokenstream.h"
#include "parser/parser.h"

int main(int argc, char * argv[]){
  if( argc != 3 ){
    printf("Ctuna compiler usage: %s <source_code.cct> <bytecode_output> \n", argv[0]);
    return 1;
  }

  char *source_name = argv[1];
  char *output_name = argv[2];

  printf("Compiling %s to %s\n", source_name, output_name);

  size_t lines = 0;
  char **source_lines = read_file(source_name, &lines);
  if( source_lines == NULL ){
    printf("Error reading source file\n");
    return 1;
  }

  Token* tokens = NULL;
  size_t num_tokens = 0;
  Result status = lexer(source_lines, lines, &tokens, &num_tokens);
  if( status.code != OK ){
    print_error_message(status);
    free_lines(source_lines, lines);
    return 1;
  }

  TokenStream stream;
  stream.tokens = tokens;
  stream.pos = 0;
  stream.lenght = num_tokens;
  
  
  ParseResult ast = parse_program(&stream);
  if( ast.result.code != OK ){
    print_error_message(ast.result);
  }


  free(tokens); 
  free_lines(source_lines, lines);
  return 0;
}
