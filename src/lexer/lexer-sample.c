// #include <stdio.h>
// #include <ctype.h>
// #include <string.h>
// #include "lexer/lexer.h"

// #define MAX_TOKEN_LEN 100

// const char* keywords[] = { "int", "float", "if", "for", "while", "return" };
// const int keyword_count = 6;

// int is_keyword(const char* str) {
//     for (int i = 0; i < keyword_count; ++i) {
//         if (strcmp(str, keywords[i]) == 0)
//             return 1;
//     }
//     return 0;
// }

// void print_token(const char* type, const char* value) {
//     printf("<%s, '%s'>\n", type, value);
// }

// void lexer(char** lines, int line_count) {
//     char token[MAX_TOKEN_LEN];
//     int index;

//     for (int l = 0; l < line_count; ++l) {
//         char* line = lines[l];
//         int i = 0;

//         while (line[i] != '\0') {
//             if (isspace(line[i])) {
//                 i++;
//                 continue;
//             }

//             if (isalpha(line[i]) || line[i] == '_') {
//                 index = 0;
//                 while (isalnum(line[i]) || line[i] == '_') {
//                     token[index++] = line[i++];
//                 }
//                 token[index] = '\0';
//                 if (is_keyword(token)) {
//                     print_token("KEYWORD", token);
//                 } else {
//                     print_token("IDENTIFIER", token);
//                 }
//             } else if (isdigit(line[i])) {
//                 index = 0;
//                 while (isdigit(line[i])) {
//                     token[index++] = line[i++];
//                 }
//                 token[index] = '\0';
//                 print_token("NUMBER", token);
//             } else {
//                 token[0] = line[i++];
//                 token[1] = '\0';
//                 print_token("SYMBOL", token);
//             }
//         }
//     }
// }
