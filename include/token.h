#ifndef TI_TOKEN_H
#define TI_TOKEN_H

typedef struct Token Token;

enum TokenKind {
    TK_END,
    TK_NUMBER, 
    TK_IDENT,
    /* keyword */
    TK_LET,
    TK_REC,
    TK_FUN,
    TK_IN,
};

struct Token {
    enum TokenKind kind;
    /* TK_NUMBER */
    int number;
    /* TK_IDENT */
    char *name;
};

#endif
