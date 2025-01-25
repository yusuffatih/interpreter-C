#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "token.h"

void startRepl() {
    char line[1024]; 

    for (;;) {
        printf(">> "); 

        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            printf("Problem with Repl!\n");
            break;
        }
        Lexer *l = New(line);
        Token tok = NextToken(l);
        while (strcmp(tok.Type, EOF_STR)) {
            printf("Token Type : %s\n", tok.Type);
            printf("Token Literal : %s\n", tok.Literal);
            tok = NextToken(l);
        }
        endLexer(l);
    }
}

