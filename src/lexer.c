/* tokenize all characters into Tokens (fields listed in token.h)
 * no external libraries used, everything written by myself from scratch.
 *
 * brief rules:
 *  - spaces get ignored.
 *  - multiple periods in one sequence (e.g., 1.23.45.67) return TKN_ERROR on the second period. Count starts from scratch afterward.
 *  - identifiers must start with a character in the English alphabet. After the first character numbers and underscores are counted.
 *  - something I most likely forgot.
 */
#include "lexer.h"

void lexerInitialize(Lexer *lexer, const char *source) {
    // initialize the lexer fields
    lexer->input_string = source;
    lexer->index = 0;
}

static int isAlpha(char ch) {
    // return 1 if ch is a character from a-z or A-Z, return 0 otherwise
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) return 1;
    return 0;
}

static int isDigit(char ch) {
    // return 1 if ch is a digit, return 0 otherwise
    if (ch >= '0' && ch <= '9') return 1;
    return 0;
}

static int countAlphaSequence(const Lexer *lexer) {
    // return the length of identifier sequence
    int i = 0;

    while (1) {
        char currentChar = lexer->input_string[lexer->index + i];
        if (isAlpha(currentChar) || isDigit(currentChar) || currentChar == '_') {
            i++;
        }
        else break;
    }
    return i;
}

static int analyzeDigitSequence(const Lexer *lexer,double *value) {
    // read through the current sequence of digits, return its length and pass a pointer of its numerical value
    int hasPeriodOccurred = 0;
    int i = 0;
    double total = 0;
    double divisor = 1.0;

    while (1) {
        const char loopLetter = lexer->input_string[lexer->index + i];

        if (isDigit(loopLetter)) {
            int loopNumber = loopLetter - '0';  // this converts character to integer. eg '7' - '0' = 7
            total = total * 10.0 + loopNumber;
            if (hasPeriodOccurred) {    // period has occurred, increase divisor by a factor of one.
                divisor *= 10;
            }
            i++;
        }
        else if (loopLetter == '.' && hasPeriodOccurred == 0) { // period occurred, update hasPeriodOccurred.
            hasPeriodOccurred = 1;
            i++;
        }
        else break;
    }
    *value = total / divisor; //change value to (total/divisor) through pointer
    return i;   // return digit sequence length
}

Token lexerGetNextToken(Lexer *lexer) {
    int noWhitespacesRemaining = 0;
    while (noWhitespacesRemaining == 0) {
        char lexerch = lexer->input_string[lexer->index];
        if (lexerch == ' ' || lexerch == '\t' || lexerch == '\n') lexer->index += 1;
        else noWhitespacesRemaining = 1;
    }

    const char letter = lexer->input_string[lexer->index];
    Token returnedToken;
    returnedToken.index = lexer->index;

    if (letter == '\0') {
        returnedToken.length = 0;
        returnedToken.kind = TKN_END;
        returnedToken.value = 0;
        return returnedToken;
    }
    if (isAlpha(letter)) {
        returnedToken.length = countAlphaSequence(lexer);
        returnedToken.value = 0;
        lexer->index = lexer->index + returnedToken.length;
        returnedToken.kind = TKN_IDENTIFIER;
        return returnedToken;
    }
    if (isDigit(letter)) {
        double total = 0;
        const int i = analyzeDigitSequence(lexer, &total);
        returnedToken.value = total;
        returnedToken.length = i;
        lexer->index = lexer->index + i;
        returnedToken.kind = TKN_NUMBER;
        return returnedToken;
    }
    switch (letter) {
        case '+':
            returnedToken.kind = TKN_PLUS;
            break;
        case '-':
            returnedToken.kind = TKN_MINUS;
            break;
        case '(':
            returnedToken.kind = TKN_LPAREN;
            break;
        case ')':
            returnedToken.kind = TKN_RPAREN;
            break;
        case '*':
            returnedToken.kind = TKN_MULTIPLY;
            break;
        case '/':
            returnedToken.kind = TKN_DIVIDE;
            break;
        case '^':
            returnedToken.kind = TKN_POWER;
            break;
        default:
            returnedToken.kind = TKN_ERROR;
            break;
    }
    returnedToken.length = 1;
    returnedToken.value = 0;
    lexer->index = lexer->index + 1;
    return returnedToken;
}

const char *tokenKindToName(const TokenKind tokenKind) {
    switch (tokenKind) {
        case TKN_NUMBER: return "NUMBER";
        case TKN_IDENTIFIER: return "IDENTIFIER";
        case TKN_LPAREN: return "LPAREN";
        case TKN_RPAREN: return "RPAREN";
        case TKN_PLUS: return "PLUS";
        case TKN_MINUS: return "MINUS";
        case TKN_MULTIPLY: return "MULTIPLY";
        case TKN_DIVIDE: return "DIVIDE";
        case TKN_POWER: return "POWER";
        case TKN_ERROR: return "ERROR";
        case TKN_END: return "END";
        default: return "UNKNOWN";
    }
}