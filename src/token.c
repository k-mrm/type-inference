#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "token.h"

Token *new_token(enum TokenKind k) {
    Token *tk = malloc(sizeof(Token));

    tk->kind = k;

    return tk;
}
Token *new_number_token(int n) {
    Token *tk = new_token(TK_NUMBER);

    tk->number = n;

    return tk;
}
Token *new_ident_token(char *i) {
    enum TokenKind k = TK_IDENT;

    if(strcmp(i, "fun") == 0) {
        k = TK_FUN;
    }
    else if(strcmp(i, "in") == 0) {
        k = TK_IN;
    }
    else if(strcmp(i, "let") == 0) {
        k = TK_LET;
    }
    else if(strcmp(i, "rec") == 0) {
        k = TK_REC;
    }

    Token *tk = new_token(k);

    tk->name = i;

    return tk;
}

Token *token_end() {
    Token *tk = new_token(TK_END);

    return tk;
}
