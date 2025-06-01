cmake_minimum_required(VERSION 3.10)
project(CactusC)

set(CMAKE_C_STANDARD 99)

include_directories(include)
include_directories(src)

#file(GLOB_RECURSE SOURCES "src/*.c")
set(SOURCES
    src/main.c
    src/utils/read_file.c
    src/error_handler/error_handler.c
    src/lexer/lexer.c
    src/lexer/regex.c
    src/lexer/token.c
    src/parser/astNode.c
    src/parser/parser.c
    src/parser/tokenstream.c
    src/semantic_analysis/semantic.c
    src/semantic_analysis/symbol_table.c
    src/codegen/codegen.c
)


add_executable(ctuna ${SOURCES})

