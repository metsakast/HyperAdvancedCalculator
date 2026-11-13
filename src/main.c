#include <stdio.h>
#include "mathlib.h"
#include "lexer.h"
#include "token.h"
#include "parser.h"

// this part was written by claude - testing only
void printTokens(const char *input, Lexer lexer, Token token) {
    int count = 0;
    lexerInitialize(&lexer, input);
    do {
        token = lexerGetNextToken(&lexer);
        printf("%-10s at %2d, length %d", tokenKindToName(token.kind), token.index, token.length);
        if (token.kind == TKN_NUMBER) {
            printf(", value %.15g", token.value);
        }
        printf("\n");
        count++;
    } while (token.kind != TKN_END && count < 50);
}

int main(void) {
    Lexer lexer;
    Token token;

    char line[256];
    while (1) {
        printf("> ");
        fflush(stdout);
        if (fgets(line, sizeof line, stdin) == NULL) break;
        if (line[0] == '\n') break;
        printTokens(line, lexer, token);
    }
}