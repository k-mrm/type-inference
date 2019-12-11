#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

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
        num = num * 10 + *n - '0'; 
        n++;
    }

    vec_push(token, new_number_token(num));

    return n;
}

static char *ident(Vector *token, char *i) {
    int len = 1;

    while(!isblank(i[len]) && !strchr("()", i[len])) {
        len++;
    }

    char *name = malloc(sizeof(char) * (len + 1));
    strncpy(name, i, len);

    vec_push(token, new_ident_token(name));

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
        else if(strchr("()", *src)) {
            char *name = malloc(sizeof(char) * 1);
            strncpy(name, src, 1);
            vec_push(token, new_ident_token(name));
            src++;
            continue;
        }
        else {  // var
            src = ident(token, src);
            continue;
        }
    }

    vec_push(token, token_end());
    vec_push(token, NULL);
}
