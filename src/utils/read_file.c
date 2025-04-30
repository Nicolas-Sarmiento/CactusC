#include "utils/read_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **read_file(const char *filename, size_t *lines) {
    FILE *source_file = fopen(filename, "r");
    if (source_file == NULL ){
        printf("Error opening the source file %s\n", filename);
        return NULL;
    }

    size_t buffer_capacity = 10;
    size_t line_counter = 0;
    char **line_buffer = malloc(buffer_capacity * sizeof(char *));
    char *line = NULL;
    size_t len = 0;
    size_t readed_chars;

    while ((readed_chars = getline(&line, &len, source_file)) != -1) {
        if ( line_counter >= buffer_capacity ){
            buffer_capacity *= 2;
            line_buffer = realloc(line_buffer, buffer_capacity * sizeof( char *));
        }

        line_buffer[line_counter] = malloc( (readed_chars + 1) * sizeof(char));
        strcpy(line_buffer[line_counter], line);
        line_counter++;
    }

    free(line);
    *lines = line_counter;
    fclose(source_file);

    return line_buffer;
}

void free_lines(char **source, size_t lines){
    for(size_t i = 0; i < lines; i++){
        free(source[i]);
    }
    free(source);
}