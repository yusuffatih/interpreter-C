#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "token.h"
#include "lexer.h"
#include "hash.h"

H_Table *htable;

Lexer *New(char *input) {
    Lexer *l = (Lexer *)malloc(sizeof(Lexer));
    l->input = input;
    l->position = 0;
    l->readPosition = 0;
    l->ch = 0;
    htable = keywords();

    readChar(l);
    return l;
}  

void endLexer(Lexer *l) {
    free(l);
}

static char *appendChars(char ch1, char ch2) {
    // return value should be freed
    
    char *str = (char *)malloc(sizeof(char) * 3);
    str[0] = ch1;
    str[1] = ch2;
    str[2] = '\0';
    return str;
}

static int isLetter(char ch) {
    return (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'));
}

static int isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

char peekChar(Lexer *l) {
    if (l->readPosition >= strlen(l->input)) {
        return 0;
    } else {
        return l->input[l->readPosition];
    }
}

static void substring(char *input, char *dest, int start, int stop, int length) {
    int s = start;

    for (int i = 0; i < length; i++) {
        if (s >= stop) {
            break;
        }
        dest[i] = input[s];
        s += 1;
    }
    dest[length] = '\0';
}

char *readNumber(Lexer *l) {
    int position = l->position;

    while(isDigit(l->ch)) {
        readChar(l);
    }
    int length = l->position - position;
    char *ident = (char *)malloc(sizeof(char) * (length + 1));
    if(ident == NULL) {
        //exit(1); // MALLOC FAILED!
        printf("MALLOC ERROR OCCURED (lexer.c)");
    }
    substring(l->input, ident, position, l->position, length);
    return ident;    
}

static void skipWhitespace(Lexer *l) {
    while (l->ch  == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
        readChar(l);
    }
}

Token NextToken(Lexer *l) {
    Token tok;
    
    skipWhitespace(l);

    switch (l->ch) {
        case '=':
            if (peekChar(l) == '=') {
                char prevch = l->ch;
                readChar(l);
                char *literal = appendChars(prevch, l->ch);
                // free !
                tok = (Token){EQ, literal};
            } else {
                tok = newToken(ASSIGN, l->ch);
            }
            break;
        case ';':
            tok = newToken(SEMICOLON, l->ch);
            break;
        case '-':
            tok = newToken(MINUS, l->ch);
            break;
        case '!':
            if (peekChar(l) == '=') {
                char prevch = l->ch;
                readChar(l);
                // free !
                char *literal = appendChars(prevch, l->ch);
                tok = (Token) {NOT_EQ, literal};
            } else {
                tok = newToken(BANG, l->ch);
            }
            break;
        case '<':
            tok = newToken(LT, l->ch);
            break;
        case '>':
            tok = newToken(GT, l->ch);
            break;
        case '*':
            tok = newToken(ASTERISK, l->ch);
            break;
        case '/':
            tok = newToken(SLASH, l->ch);
            break; 
        case '(':
            tok = newToken(LPAREN, l->ch);
            break;
        case ')':
            tok = newToken(RPAREN, l->ch);
            break;
        case ',':
            tok = newToken(COMMA, l->ch);
            break;
        case '+':
            tok = newToken(PLUS, l->ch);
            break;
        case '{':
            tok = newToken(LBRACE, l->ch);
            break;
        case '}':
            tok = newToken(RBRACE, l->ch);
            break;
        case 0:
            tok.Literal = "";
            tok.Type = EOF_STR;
            break;
        default:
            if (isLetter(l->ch)) {
                tok.Literal = readIdentifier(l);
                tok.Type = lookUpIdent(htable, tok.Literal);
                return tok;
            } else if (isDigit(l->ch)) {
                tok.Type = INT;
                tok.Literal = readNumber(l);
            } 
            else {
                tok = newToken(ILLEGAL, l->ch);
            }
  
    }
    readChar(l);
    return tok;
}

Token newToken(TokenType tokenType, char ch) {
    char newStr[1];
    newStr[0] = ch;
    Token tok = {tokenType, newStr};
    return tok;
}

char *readIdentifier(Lexer *l) {
   
    int position = l->position;
    while (isLetter(l->ch)) {
        readChar(l);
    }  
    int length = l->position - position;
    char *ident = (char *)malloc((length + 1) * sizeof(char));
    if (ident == NULL) {
        //exit(1); // MALLOC FAILED!
        printf("MALLOC ERROR OCCURED! (lexer.c)");
    }

    substring(l->input, ident, position, l->position, length);
    
    return ident;
}

void readChar(Lexer *l) {
    if (l->readPosition >= strlen(l->input)) {
        l->ch = 0;
    } else {
        l->ch = l->input[l->readPosition];
    }
    l->position = l->readPosition;
    l->readPosition += 1;
}


