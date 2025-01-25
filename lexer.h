#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include "hash.h"

typedef struct Lexer{
    char *input;
    int position;
    int readPosition;
    char ch;
} Lexer;

typedef char *TokenType;

Lexer *New(char *input);
void endLexer(Lexer *l);

void readChar(Lexer *l);
char *readIdentifier(Lexer *l);
char *readNumber(Lexer *l);
char peekChar(Lexer *l);

struct Token NextToken(Lexer *l);
struct Token newToken(TokenType tokenType, char ch);

#endif
