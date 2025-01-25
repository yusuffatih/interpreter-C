#include <stdlib.h>

#include "token.h"
#include "hash.h"
#include "lexer.h"

H_Table *keywords() {
    H_Table *htable = (H_Table *)malloc(sizeof(H_Table));
    initH_Table(htable);

    H_Value fn = {"fn", FUNCTION};
    H_Value let = {"let", LET};
    H_Value tr = {"true", TRUE};
    H_Value fl = {"false", FALSE};
    H_Value iff = {"if", IF};
    H_Value el = {"else", ELSE};
    H_Value rn = {"return", RETURN};

    set(fn, htable);
    set(let, htable);
    set(tr, htable);
    set(fl, htable);
    set(iff, htable);
    set(el, htable);
    set(rn, htable);

    return htable;
}

TokenType lookUpIdent(H_Table *table, char *ident) {
    if (hasH_Table(ident, table)) {
        Value tok = get(ident, table); 
        return tok;
    } else {
        return IDENT;
    }
} 


