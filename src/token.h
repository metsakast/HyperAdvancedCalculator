#ifndef CALCULATOR_PROJECT_TOKEN_H
#define CALCULATOR_PROJECT_TOKEN_H

typedef enum TokenKind {
    TKN_NUMBER,
    TKN_IDENTIFIER,
    TKN_LPAREN,
    TKN_RPAREN,
    TKN_PLUS,
    TKN_MINUS,
    TKN_MULTIPLY,
    TKN_DIVIDE,
    TKN_POWER,
    TKN_ERROR,
    TKN_END
} TokenKind;

typedef struct Token {
    TokenKind kind; // token kind
    double value; // numerical value (only for TKN_NUMBER)
    int length; // how long is the token
    int index; // at which index does the token start
} Token;

#endif //CALCULATOR_PROJECT_TOKEN_H
