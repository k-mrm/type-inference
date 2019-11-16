#include <stdio.h>
#include <assert.h>

#include "infer.h"
#include "type.h"

Type *prune(Type *ty) {
    if(ty == NULL) return NULL;

    if(is_type_variable(ty) && ty->instance != NULL) {
        ty->instance = prune(ty->instance);
        return ty->instance;
    }

    return ty;
}

void unify(Type *t1, Type *t2) {
    ;
}

Type *analyze(Env *env, Expr *e) {
    assert(e);

    switch(e->kind) {
    case INTEGER:
        return type_int();
    case VAR: {
        Type *ty = lookup(env, ((Var *)e)->name);

        if(ty == NULL) {
            printf("unknown: `%s`\n", ((Var *)e)->name);
        }

        return ty;
    }
    case LAMBDA:
    case APPLY: {
        Type *fn = analyze(env, ((Apply *)e)->fn);
        Type *arg = analyze(env, ((Apply *)e)->arg);
        Type *res = type_var(); 
    }
    case LET:
    case LETREC:
    default:
        printf("internal error");
    }

    return NULL;
}
