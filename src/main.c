#include <stdio.h>
#include <stdlib.h>
#include "utils/read_file.h"
#include "lexer/lexer.h"


int main(int argc, char * argv[]){
  if( argc != 3 ){
    printf("Ctuna compiler usage: %s <source_code.cct> <bytecode_output> \n", argv[0]);
    return 1;
  }

  char *source_name = argv[1];
  char *output_name = argv[2];

  printf("1. Compiling %s to %s\n", source_name, output_name);

  size_t lines = 0;
  char **source_lines = read_file(source_name, &lines);
  if( source_lines == NULL ){
    printf("Error reading source file\n");
    return 1;
  }

  for( size_t i = 0; i < lines; i++ ){
    printf("%s", source_lines[i]);
  }

  lexer(source_lines, lines);

  free_lines(source_lines, lines);

  return 0;
}
