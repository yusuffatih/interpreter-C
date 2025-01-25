#ifndef AST_H
#define AST_H

#include "token.h"

typedef enum expr_tag {
    LET,
    IDENT, //       define these
    PROGRAM, //     :D
    EXPRESSION, //  :)
    RETURN
} expr_tag;

typedef struct Ast {
    expr_tag tag;
    
    union {
    
        struct {
            Token token;
            int value;  
        } intExpr;

        struct {
            Token token;
            char *value;
        } stringExpr;
        
        struct {
            Token token;
            char *value;
        } variableExpr;

        struct {
            Ast *statements;
            int statementCount;
        } programStmt;

        struct {
            Token token;
            Ast *identifier;
            Ast *value; // important, maybe change this to expr later
        } letStmt; 
        
        struct {
            Token token;
            char *value;  
        } identStmt;
        
        struct {
            Token token;
            Ast *returnValue // important // same up above
        } returnStmt;

    };
} Ast;





#endif
