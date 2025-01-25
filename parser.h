#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "lexer.h"
#include "ast.h"

typedef enum Precedence {
    LOWEST,
    EQUALS,
    LESSGREATER,
    SUM,
    PRODUCT,
    PREFIX,
    CALL
} Precedence;

typedef struct Parser {
    Lexer *lexer; 
    
    Token curentToken;
    Token peekToken;

    
    

} Parser;

typedef struct Ast *(*prefixParseFn)(void);
typedef struct Ast *(*infixParseFn)(Ast *);

Parser *NewParser(Lexer *l);
// later implement -> endParser function

void nextToken(Parser *p);

Ast *parseProgram(Parser *p);
Ast *parseStatemtn(Parser *p);

Ast *parseLetStatement(Parser *p);
Ast *parseReturnStatement(Parser *p);
Ast *parseExpressionStatement(Parser *p);
Ast *parseExpression(Parser *p, Precedence precedence);

Ast *prefisParse(Parser *p);
Ast *infizParse(Parser *p);

#endif
