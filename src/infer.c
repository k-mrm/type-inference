#include <stdio.h>
#include <assert.h>

#include "infer.h"
#include "type.h"

Type *prune(Type *ty) {
    if(ty == NULL) return NULL;

    if(is_type_variable(ty)) {
        if(ty->instance != NULL) {
            ty->instance = prune(ty->instance);
            return ty->instance;
        }
    }

    return ty;
}

void unify(Type *t1, Type *t2) {
    t1 = prune(t1);
    t2 = prune(t2);

    if(is_type_variable(t1)) {
        ;
    }
    else if(is_type_operator(t1) &&
            is_type_variable(t2)) {
        unify(t2, t1);
    }
    else if(is_type_operator(t1) &&
            is_type_operator(t2)) {
        if(t1->kind != t2->kind || t1->ntype != t2->ntype) {
            printf("type error: ");
            typedump(t1);
            printf(", ");
            typedump(t2);
            puts("");

            return;
        }
        
        for(int i = 0; i < t1->ntype; i++) {
            unify(t1->types[i], t2->types[i]);
        }
    }
    else {
        printf("cannot infer");
    }
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
        break;
    }
    case LET:
    case LETREC:
    default:
        printf("internal error");
    }

    return NULL;
}
