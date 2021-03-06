#include <stdio.h>
#include <assert.h>

#include "infer.h"
#include "type.h"
#include "nongeneric.h"
#include "util.h"

static bool is_generic(Type *, NonGeneric *);
static bool occursin(Type *, Type *);
static bool occursin_type(Type *, Type *);

bool error_occurred = false;

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

/*
 *  型変数がgenericかどうかを判定する
 *
 *  型変数がnon-generic型変数のリストに出現するかを見る
 *  出現したらnon-genericなので -> false
 *  しなかったらgenericなので -> true
 */
static bool is_generic(Type *tvar, NonGeneric *nongeneric) {
    for(int i = 0; i < nongeneric->cursor; i++) {
        if(occursin_type(tvar, nongeneric->list[i]))
            return false;
    }

    return true;
}

static bool occursin_type(Type *tvar, Type *texp) {
    texp = prune(texp);

    if(is_type_variable(texp)) {
        return same_type(tvar, texp);
    }
    else if(is_type_operator(texp)) {
        return occursin(tvar, texp);
    }
    else return false;
}


/*
 * 型(第2引数)の中に型変数(第1引数)が出現するかチェックする
 */
static bool occursin(Type *tyvar, Type *tope) {
    for(int i = 0; i < tope->ntype; i++) {
        if(occursin_type(tyvar, tope->types[i])) return true;
    }

    return false;
}

Type *type_map_exist(Map *self, Type *key) {
    for(int i = 0; i < self->key->len; i++) {
        if(same_type((Type *)self->key->data[i], key)) {
            return (Type *)self->value->data[i];
        }
    }

    return NULL;
}

Type *type_get_or_put(Map *self, Type *key, Type *default_value) {
    Type *e = type_map_exist(self, key);

    if(e != NULL) {
        return e;
    }
    else {
        map_push(self, key, default_value);
        return default_value;
    }
}

/*
 *  type_operatorとgeneric変数は複製
 *  non-generic変数は共有
 */
Type *freshrec(Type *ty, NonGeneric *nongeneric, Map *mappings) {
    Type *pty = prune(ty);

    if(is_type_variable(pty)) {
        if(is_generic(pty, nongeneric)) {
            return type_get_or_put(mappings, pty, type_var());
        }
        else return pty;
    }
    else if(is_type_operator(pty)) {
        switch(pty->ntype) {
        case 0: return type_operator0(pty->kind);
        case 2: return type_operator2(
                           pty->kind,
                           freshrec(pty->types[0], nongeneric, mappings),
                           freshrec(pty->types[1], nongeneric, mappings)
                       );
        default:
                puts("????");
        }
    }

    /* unreachable */
    return NULL;
}

Type *fresh(Type *t, NonGeneric *nongeneric) {
    Map *mappings = New_Map();

    return freshrec(t, nongeneric, mappings);
}

void unify(Type *t1, Type *t2) {
    t1 = prune(t1);
    t2 = prune(t2);

    printf("unifying...");
    typedump_core(t1);
    printf(", ");
    typedump_core(t2);
    puts("");

    if(is_type_variable(t1)) {
        if(!same_type(t1, t2)) {
            if(occursin_type(t1, t2)) {
                printf("recursive unification");
                error_occurred = true;
                return;
            }
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

            error_occurred = true;

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

    if(!e) return NULL;

    switch(e->kind) {
    case INTEGER: {
        Type *result = type_int();

        printf("integer %d: ", e->num);
        typedump(result);

        return result;
    }
    case VAR: {
        Type *ty = lookup(env, e->name, nongeneric);

        if(ty == NULL) {
            printf("unknown identifer `%s`\n", e->name);
            return NULL;
        }

        printf("var %s: ", e->name);
        typedump(ty);

        return ty;
    }
    case LAMBDA: {
        Type *argty = type_var();

        Env *copied_env = copy_env(env);
        add_to_env(copied_env, e->x, argty);

        NonGeneric *copied_ng = copy_non_generic(nongeneric);
        add_to_non_generic(copied_ng, argty);

        Type *ret = analyze(copied_env, e->e, copied_ng);

        Type *result = type_fn(argty, ret);

        printf("lambda" );
        exprdump(e);
        printf(": ");
        typedump(result);

        return result;
    }
    case APPLY: {
        Type *fn = analyze(env, e->fn, nongeneric);
        Type *arg = analyze(env, e->arg, nongeneric);
        Type *res = type_var(); 

        unify(fn, type_fn(arg, res));

        printf("apply ");
        exprdump(e);
        printf(": ");
        typedump(res);

        return res;
    }
    case LET: {
        Type *def = analyze(env, e->ldef, nongeneric);

        Env *new = copy_env(env);
        add_to_env(new, e->lname, def);

        Type *result = analyze(new, e->lbody, nongeneric);
        printf("let %s: ", e->lname);
        typedump(result);

        return result;
    }
    case LETREC: {
        Type *new = type_var();

        Env *new_env = copy_env(env);
        NonGeneric *new_nongeneric = copy_non_generic(nongeneric);

        add_to_env(new_env, e->recname, new);
        add_to_non_generic(new_nongeneric, new);

        Type *def = analyze(new_env, e->recdef, new_nongeneric);

        unify(new, def);

        Type *result = analyze(new_env, e->recbody, new_nongeneric);
        printf("letrec %s: ", e->recname);
        typedump(result);

        return result;
    }
    default:
        printf("internal error");
    }

    return NULL;
}
