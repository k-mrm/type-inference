#ifndef TI_EXPR_H
#define TI_EXPR_H

#define EXPR_BASE Expr base

enum ExprKind {
    INTEGER,
    VAR,
    LAMBDA,
    APPLY,
    LET,
    LETREC,
};

typedef struct Expr Expr;

struct Expr {
    enum ExprKind kind;

    union {
        /* Integer  */
        struct {
            int num;
        };
        /* Var  */
        struct {
            char *name;
        };
        /* Lambda  */
        struct {
            char *x;
            Expr *e;
        };
        /* Apply  */
        struct {
            Expr *fn,
                 *arg;
        };
        /* Let  */
        struct {
            char *lname;
            Expr *ldef,
                 *lbody;
        };
        /* Letrec  */
        struct {
            char *recname;
            Expr *recdef,
                 *recbody
        };
    };
};


Expr *integer(int);
Expr *var(char *);
Expr *lambda(char *, Expr *);
Expr *apply(Expr *, Expr *);
Expr *let(char *, Expr *, Expr *);
Expr *letrec(char *, Expr *, Expr *);
Expr *binary(Expr *, char *, Expr *);
void exprdump(Expr *); 


#endif
