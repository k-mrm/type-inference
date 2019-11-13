#ifndef TI_EXPR_H
#define TI_EXPR_H

#define EXPR_BASE Expr base

enum ExprKind {
    LITERAL,
    VAR,
    LAMBDA,
    APPLY,
};

struct Expr {
    enum ExprKind kind;
};

typedef struct Expr Expr;

typedef struct Literal Literal;
typedef struct Var Var;
typedef struct Lambda Lambda;

struct Literal {
    EXPR_BASE;
    union {
        int num;
    };
};

struct Var {
    EXPR_BASE;
    char *name;
};

struct Lambda {
    EXPR_BASE;

    char *x;
    Expr *e;
};

struct Apply {
    EXPR_BASE;

    Expr *f,
         *e;
};

Literal *new_literal(int);
Var *new_var(char *);
Lambda *new_lambda(char *, Expr *);
Apply *new_apply(Expr *, Expr *);


#endif
