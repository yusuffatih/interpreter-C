#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "ast.h"


static int curTokenIs(Parser *p, TokenType t) {
    return (p->currentToken.Type == t);
}

static int peekTokenIs(Parser *p, TokenType t) {
    return (p->peekToken.Type == t);
}

static int expectPeek(Parser *p, TokenType t) {
    if (peekTokenIs(p, t)) {
        nextToken(p);
        return 1;
    } else {
        return 0;
    }
}

Parser *NewParser(Lexer *l) {
   
    Parser *p = (Parser *p)malloc(sizeof(Parser));

    if (p == NULL) {
        printf("Malloc Error Occured!");
        return NULL;
    }
         
    p->lexer = l;
    p->currentToken = 0;
    p->nextToken = 0;
    
    nextToken(p);
    nextToken(p);

    return p;
}

void nextToken(Parser *p) {

    p->currentToken = p->peekToken;
    p->peekToken = NextToken(p->lexer);
}  

Ast *parseProgram(Parser *p) {

    Ast *program = (Ast *)malloc(sizeof(Ast));

    if (program == NULL)  {
        printf("Malloc Error Occured!");
        return NULL;
    }

    program->tag = PROGRAM;

    program->programStmt.statementCount = 0;
    program->programStmt.statements = NULL;

    while (p->currentToken.Type != EOF_STR) {
        Ast *stmt = parseStatement(p);

        if (stmt != NULL) {
             
        }

        nextToken(p);
    }

    return program;
}

Ast *parseStatement(Parser *p) {

    switch (p->currentToken.Type) {
        case LET:
            return parseLetStatement(p);
            break;
        case RETURN:
            return parseReturnStatement(p);
            break;
        default:
                return parseExpressionStatement(p);
                break;
    }
}

Ast *parseExpression(Parser *p, Precedence precedence) {
    
        


}

Ast *parseExpressionStatement(p) {
   
    Ast *stmt = (Ast *)malloc(sizeof(Ast));

    stmt->tag = EXPRESSION;
    
    stmt-> // later

    if (peekTokenIs(p, SEMICOLON)) {
        nextToken(p);
    }

    return stmt;
}


Ast *parseReturnStatement(Parser *p) {
    Ast *stmt = (Ast *)malloc(sizeof(Ast));

    stmt->tag = RETURN;

    stmt->returnStmt.token = p->currentToken;
    // stmt->returnStmt.value     IMPORTANT! TAKE A LOOK!
    
    nextToken(p);

    while(curTokenIs(p, SEMICOLON)) {
        nextToken(p);:
    }
    
    return stmt;
}

Ast *parseLetStatement(Parser *p) {
    Ast *stmt = (Ast *)malloc(sizeof(Ast));
    
    stmt->tag = LET;
    stmt->letStmt.token = p->currenToken;

    if (!expectPeek(p, IDENT)) {
        return NULL;
    }
    
    Ast *ident= (Ast *)malloc(sizeof(Ast));
    ident->tag = IDENTIFIER;
    ident->identStmt.token = IDENT;
    ident->identStmt.value = p->currentToken.Literal;

    stmt->letStmt.identifier = ident;

    if (expectPeek(p, ASSIGN)) {
        return NULL;
    }

    while (!curTokenIs(p, SEMICOLON)) {
        nextToken(p);
    }
    
    return stmt;    
}














