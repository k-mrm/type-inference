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

static char *number(Vector *token, char *n) {
    int num;

    while(isdigit(*n)) {
        num = num * 10 + *n++ - '0'; 
    }

    vec_push(token, new_number_token(num));

    return n;
}

static char *ident(Vector *token, char *i) {
    int len = 1;

    while(!isblank(i[len])) {
        len++;
    }

    vec_push(token, new_ident_token(i));

    return i + len;
}

static void scan(Vector *token, char *src) {
    while(*src) {
        if(isdigit(*src)) {
            src = number(token, src);
            continue;
        }
        else if(isblank(*src)) {
            src++;
            continue;
        }
        else {  // var
            src = ident(token, src);
            continue;
        }
    }

    token_end();
}
