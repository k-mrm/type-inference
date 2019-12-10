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
    /* Symbol */
    TK_ASSIGN,   // =
    TK_ARROW,    // ->
};

struct Token {
    enum TokenKind kind;
    /* TK_NUMBER */
    int number;
    /* TK_IDENT */
    char *name;
};

Token *new_token(enum TokenKind);
Token *new_number_token(int);
Token *new_ident_token(char *);
Token *token_end();

#endif
