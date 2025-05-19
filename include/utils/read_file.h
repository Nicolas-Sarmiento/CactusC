
#ifndef READ_FILE_H
#define READ_FILE_H
#include <stdio.h>

char **read_file(const char *filename, size_t *lines);
void free_lines(char **source, size_t lines);

#endif // READ_FILE_H
