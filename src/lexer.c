#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"
#include "token.h"

static void scan(Vector *, char *);

Vector *lex(char *src) {
    Vector *tokens = New_Vector();

    scan(tokens, src);

    return tokens;
}

static void scan(Vector *token, char *src) {
    for(int i = 0; i < strlen(src); i++) {
        if(isdigit(src[i])) {
            ;
        }
        else if(isalpha(src[i]) || src[i] == '_') {
            ;
        }
        else if(isblank(src[i])) {
            continue;
        }
    }
}
