#ifndef TI_TOKEN_H
#define TI_TOKEN_H

typedef struct Token Token;

enum TokenKind {
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
};

#endif
