cmake_minimum_required(VERSION 4.2)
project(calculator_project C)

set(CMAKE_C_STANDARD 11)

add_executable(calculator_project src/main.c
        src/mathlib.c
        src/mathlib.h
        src/lexer.c
        src/lexer.h
        src/ast.h
        src/ast.c
        src/token.h
        src/parser.c
        src/parser.h
        src/eval.c
        src/eval.h
        src/error.h)

target_compile_options(calculator_project PRIVATE -Wall -Wextra)
