#ifndef TI_EXPR_H
#define TI_EXPR_H

#define EXPR_BASE Expr base

enum ExprKind {
    INTEGER,
    VAR,
    LAMBDA,
    APPLY,
    LET,
};

struct Expr {
    enum ExprKind kind;
};

typedef struct Expr Expr;

typedef struct Integer Integer;
typedef struct Var Var;
typedef struct Lambda Lambda;
typedef struct Let Let;
typedef struct Apply Apply;
typedef struct Let Let;

struct Integer {
    EXPR_BASE;
    int num;
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

struct Let {
    EXPR_BASE;
    char *name;
    Expr *def,
         *body;
};

Expr *integer(int);
Expr *var(char *);
Expr *lambda(char *, Expr *);
Expr *apply(Expr *, Expr *);
Expr *let(char *, Expr *, Expr *);
Expr *binary(Expr *, char *, Expr *);


#endif
