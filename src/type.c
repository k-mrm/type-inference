#include "type.h"
#include "infer.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char unique_name = 'a';
int cur_id = 0;

Type *type_operator0(enum TypeKind k) {
    Type *self = malloc(sizeof(Type));

    self->kind = k; 
    self->ntype = 0;
    self->types[0] = NULL;
    self->types[1] = NULL;

    return self;
}

Type *type_operator2(enum TypeKind k, Type *a1, Type *a2) {
    Type *self = malloc(sizeof(Type));

    self->kind = k;
    self->ntype = 2;
    self->types[0] = a1;
    self->types[1] = a2;

    return self;
}

Type *type_int() {
    return type_operator0(TINT);
}

Type *type_bool() {
    return type_operator0(TBOOL);
}

Type *type_fn(Type *a, Type *r) {
    Type *self = type_operator2(TFN, a, r);

    self->arg = a;
    self->result = r;

    return (Type *)self;
}

Type *type_var() {
    Type *self = malloc(sizeof(Type));

    self->kind = TVAR;
    self->ntype = 0;
    self->types[0] = NULL;
    self->types[1] = NULL;

    self->id = cur_id++;
    self->name = 0;
    self->instance = NULL;

    return (Type *)self;
}

bool is_type_variable(Type *ty) {
    return ty->kind == TVAR;
}

bool is_type_operator(Type *ty) {
    return ty->kind != TVAR;
}

bool same_type(Type *t1, Type *t2) {
    if(t1 == NULL || t2 == NULL) {
        puts("NULL error");
        return false;
    }

    if(t1->kind != t2->kind) {
        return false;
    }

    if(is_type_operator(t1)) {
        for(int i = 0; i < t1->ntype; i++) {
            if(!same_type(t1->types[i], t2->types[i]))
                return false;
        }
    }

    return true;
}

void typedump(Type *ty) {
    if(ty == NULL)  return;

    typedump_core(ty);
    puts("");
}

void typedump_core(Type *ty) {
    if(ty == NULL) {
        printf("null");
        return;
    }

    switch(ty->kind) {
    case TINT:      printf("int");  break;
    case TBOOL:     printf("bool"); break;
    case TFN: {
        typedump_core(ty->arg);
        printf(" -> ");
        typedump_core(ty->result);
        break;
    }
    case TVAR: {
        if(ty->instance != NULL) {
            typedump_core(prune(ty));
        }
        else if(ty->name == 0) {
            printf("%c", ty->name = unique_name++);
        }
        else {
            printf("%c", ty->name);
        }
        break;
    }
    default:        printf("error");
    }
}
