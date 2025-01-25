#ifndef TOKEN_H
#define TOKEN_H

#define ILLEGAL "ILLEGAL"
#define EOF_STR "EOF"
#define IDENT "IDENT"
#define INT "INT"
#define ASSIGN "="
#define PLUS "+"
#define MINUS "-"
#define BANG "!"
#define SLASH "/"
#define ASTERISK "*"
#define LT "<"
#define GT ">"
#define COMMA ","
#define SEMICOLON ";"
#define LPAREN "("
#define RPAREN ")"
#define LBRACE "{"
#define RBRACE "}"
#define FUNCTION "FUNCTION"
#define LET "LET"
#define TRUE "TRUE"
#define FALSE "FALSE"
#define IF "IF"
#define ELSE "ELSE"
#define RETURN "RETURN"
#define EQ "=="
#define NOT_EQ "!="

#include "hash.h"
#include "lexer.h"

typedef char *TokenType;

typedef struct Token { 
    TokenType Type;
    char *Literal;
} Token;


H_Table *keywords();
TokenType lookUpIdent(H_Table *table, char *ident);

#endif
