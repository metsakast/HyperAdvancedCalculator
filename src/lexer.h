#ifndef CALCULATOR_PROJECT_LEXER_H
#define CALCULATOR_PROJECT_LEXER_H

#include "token.h"

typedef struct Lexer {
    const char *input_string;
    int index;
} Lexer;

//declaration functions
void lexerInitialize(Lexer *, const char *);  // pointer to input string

Token lexerGetNextToken(Lexer *);

const char *tokenKindToName(TokenKind);

#endif //CALCULATOR_PROJECT_LEXER_H
