#include <stdio.h>
#include <assert.h>

#include "infer.h"
#include "type.h"

Type *type_infer(Env *env, Expr *e) {
    assert(e);

    switch(e->kind) {
    case INTEGER:
        return type_int();
    case VAR:
    case LAMBDA:
    case APPLY:
    default:
        printf("internal error");
    }

    return NULL;
}
