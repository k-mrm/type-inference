#include <stdio.h>
#include <assert.h>

#include "infer.h"
#include "type.h"

Type *analyze(Env *env, Expr *e) {
    assert(e);

    switch(e->kind) {
    case INTEGER:
        return type_int();
    case VAR:
    case LAMBDA:
    case APPLY:
    case LET:
    case LETREC:
    default:
        printf("internal error");
    }

    return NULL;
}
