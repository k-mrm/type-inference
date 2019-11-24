#include <stdio.h>
#include <assert.h>

#include "infer.h"
#include "type.h"
#include "nongeneric.h"

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

Type *occursin_type() {
    ;
}

Type *occursin() {
    ;
}

Type *fresh(Type *t) {
    ;
}

void unify(Type *t1, Type *t2) {
    t1 = prune(t1);
    t2 = prune(t2);

    if(is_type_variable(t1)) {
        if(!same_type(t1, t2)) {
            t1->instance = t2;
        }
    }
    else if(is_type_operator(t1) &&
            is_type_variable(t2)) {
        unify(t2, t1);
    }
    else if(is_type_operator(t1) &&
            is_type_operator(t2)) {
        if(t1->kind != t2->kind || t1->ntype != t2->ntype) {
            printf("type error: ");
            typedump_core(t1);
            printf(", ");
            typedump_core(t2);
            puts("");

            return;
        }
        
        for(int i = 0; i < t1->ntype; i++) {
            unify(t1->types[i], t2->types[i]);
        }
    }
    else {
        puts("cannot infer");
    }
}

Type *analyze(Env *env, Expr *e, NonGeneric *nongeneric) {
    if(nongeneric == NULL) {
        nongeneric = new_non_generic();
    }

    switch(e->kind) {
    case INTEGER:
        return type_int();
    case VAR: {
        Type *ty = lookup(env, e->name);

        if(ty == NULL) {
            printf("unknown identifer `%s`\n", e->name);
            return NULL;
        }

        return ty;
    }
    case LAMBDA: {
        Type *argty = type_var();

        Env *copied_env = copy_env(env);
        add_to_env(copied_env, e->x, argty);

        NonGeneric *copied_ng = copy_non_generic(nongeneric);
        add_to_non_generic(copied_ng, argty);

        Type *ret = analyze(copied_env, e->e, copied_ng);

        return type_fn(argty, ret);
    }
    case APPLY: {
        Type *fn = analyze(env, e->fn, nongeneric);
        Type *arg = analyze(env, e->arg, nongeneric);
        Type *res = type_var(); 

        unify(fn, type_fn(arg, res));

        return res;
    }
    case LET: {
        Type *def = analyze(env, e->ldef, nongeneric);

        Env *new = copy_env(env);
        add_to_env(new, e->lname, def);

        return analyze(new, e->lbody, nongeneric);
    }
    case LETREC: {
        break;
    }
    default:
        printf("internal error");
    }

    return NULL;
}
