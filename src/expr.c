#include <stdlib.h>
#include "expr.h"

Literal *new_literal(int n) {
    Literal *self = malloc(sizeof(Literal));

    ((Expr *)self)->kind = LITERAL;
    self->num = n;

    return self;
}

Var *new_var(char *name) {
    Var *self = malloc(sizeof(Var));

    ((Expr *)self)->kind = VAR;
    self->name = name;

    return self;
}

Lambda *new_lambda(char *x, Expr *e) {
    Lambda *self = malloc(sizeof(Lambda));

    ((Expr *)self)->kind = LAMBDA;
    self->x = x;
    self->e = e;

    return self;
}

Apply *new_apply(Expr *f, Expr *e) {
    Apply *self = malloc(sizeof(Apply));

    ((Expr *)self)->kind = APPLY;
    self->f = f;
    self->e = e;

    return self;
}
