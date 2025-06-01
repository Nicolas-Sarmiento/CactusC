#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser/astNode.h"
#include <stdio.h>

void generate_stmt( ASTNode* node, FILE* out );

#endif //CODEGEN_H