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

Type *subst(Env *env, Type *t1) {
    ;
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
        TypeScheme *ty = lookup(env, e->name);

        if(ty == NULL) {
            printf("unknown: `%s`\n", e->name);
            return NULL;
        }

        return ty->body;
    }
    case LAMBDA: {
        Type *arg = type_var();

        break;
    }
    case APPLY: {
        Type *fn = analyze(env, e->fn);
        Type *arg = analyze(env, e->arg);
        Type *res = type_var(); 

        unify(fn, type_fn(arg, res));

        break;
    }
    case LET: {
        Type *def = analyze(env, e->ldef);

        break;
    }
    case LETREC: {
        break;
    }
    default:
        printf("internal error");
    }

    return NULL;
}
