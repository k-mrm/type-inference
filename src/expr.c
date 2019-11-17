#include <stdlib.h>
#include <stdio.h>

#include "expr.h"

Expr *integer(int n) {
    Expr *self = malloc(sizeof(Expr));

    self->kind = INTEGER;
    self->num = n;

    return self;
}

Expr *var(char *name) {
    Expr *self = malloc(sizeof(Expr));

    self->kind = VAR;
    self->name = name;

    return self;
}

Expr *lambda(char *x, Expr *e) {
    Expr *self = malloc(sizeof(Expr));

    self->kind = LAMBDA;
    self->x = x;
    self->e = e;

    return self;
}

Expr *apply(Expr *f, Expr *e) {
    Expr *self = malloc(sizeof(Expr));

    self->kind = APPLY;
    self->fn = f;
    self->arg = e;

    return self;
}

Expr *let(char *name, Expr *d, Expr *b) {
    Expr *self = malloc(sizeof(Expr));

    self->kind = LET;
    self->lname = name;
    self->ldef = d;
    self->lbody = b;

    return self;
}

Expr *letrec(char *name, Expr *d, Expr *b) {
    Expr *self = malloc(sizeof(Expr));

    self->kind = LETREC;
    self->recname = name;
    self->recdef = d;
    self->recbody = b;

    return self;
}

Expr *binary(Expr *left, char *op, Expr *right) {
    return apply(apply(var(op), left), right);
}

void exprdump(Expr *e) {
    switch(e->kind) {
    case INTEGER:
        printf("%d", e->num);
        break;
    case VAR:
        printf("%s", e->name);
        break;
    case LAMBDA:
        printf("\\%s -> ", e->x);
        exprdump(e->e);
        break;
    case APPLY:
        exprdump(e->fn);
        printf(" ");
        exprdump(e->fn);
        break;
    case LET:
        printf("let %s = ", e->lname);
        exprdump(e->ldef);
        printf(" in ");
        exprdump(e->lbody);
        break;
    case LETREC:
        printf("letrec %s = ", e->recname);
        exprdump(e->recdef);
        printf(" in ");
        exprdump(e->recbody);
        break;
    default:
        break;
    }
}
