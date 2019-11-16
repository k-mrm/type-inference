#include <stdlib.h>
#include "expr.h"

Expr *integer(int n) {
    Integer *self = malloc(sizeof(Integer));

    ((Expr *)self)->kind = INTEGER;
    self->num = n;

    return (Expr *)self;
}

Expr *var(char *name) {
    Var *self = malloc(sizeof(Var));

    ((Expr *)self)->kind = VAR;
    self->name = name;

    return (Expr *)self;
}

Expr *lambda(char *x, Expr *e) {
    Lambda *self = malloc(sizeof(Lambda));

    ((Expr *)self)->kind = LAMBDA;
    self->x = x;
    self->e = e;

    return (Expr *)self;
}

Expr *apply(Expr *f, Expr *e) {
    Apply *self = malloc(sizeof(Apply));

    ((Expr *)self)->kind = APPLY;
    self->fn = f;
    self->arg = e;

    return (Expr *)self;
}

Expr *let(char *name, Expr *d, Expr *b) {
    Let *self = malloc(sizeof(Let));

    ((Expr *)self)->kind = LET;
    self->name = name;
    self->def = d;
    self->body = b;

    return (Expr *)self;
}

Expr *letrec(char *name, Expr *d, Expr *b) {
    Letrec *self = malloc(sizeof(Letrec));

    ((Expr *)self)->kind = LETREC;
    self->name = name;
    self->def = d;
    self->body = b;

    return (Expr *)self;
}

Expr *binary(Expr *left, char *op, Expr *right) {
    return apply(apply(var(op), left), right);
}
