cmake_minimum_required(VERSION 3.10)
project(CactusC)

set(CMAKE_C_STANDARD 99)

include_directories(include)
include_directories(src)

file(GLOB_RECURSE SOURCES "src/main.c" "src/**/*.c")

add_executable(ctuna ${SOURCES})

