#include <stdio.h>
#include <assert.h>

#include "infer.h"
#include "type.h"

Type *analyze(Env *env, Expr *e) {
    assert(e);

    switch(e->kind) {
    case INTEGER:
        return type_int();
    case VAR: {
        Type *ty = lookup(env, ((Var *)e)->name);

        if(ty == NULL) {
            printf("unknown: `%s`", ((Var *)e)->name);
        }

        return ty;
    }
    case LAMBDA:
    case APPLY:
    case LET:
    case LETREC:
    default:
        printf("internal error");
    }

    return NULL;
}
