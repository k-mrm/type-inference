#include "type.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char tvar_name = 'a';
int cur_id = 0;

Type *type_int() {
    TInt *self = malloc(sizeof(TInt));

    ((Type *)self)->kind = TINT; 

    return (Type *)self;
}

Type *type_bool() {
    TBool *self = malloc(sizeof(TBool));

    ((Type *)self)->kind = TBOOL;

    return (Type *)self;
}

Type *type_unknown() {
    TUnknown *self = malloc(sizeof(TUnknown));

    ((Type *)self)->kind = TUNKNOWN;

    return (Type *)self;
}

Type *type_fn(Type *a, Type *r) {
    TFn *self = malloc(sizeof(TFn));

    ((Type *)self)->kind = TFN;
    self->a = a;
    self->result = r;

    return (Type *)self;
}

Type *type_var() {
    TVar *self = malloc(sizeof(TFn));

    ((Type *)self)->kind = TVAR;
    self->id = cur_id++;
    self->instance = NULL;

    return (Type *)self;
}

bool is_type_variable(Type *ty) {
    return ty->kind == TVAR;
}

bool is_type_operator(Type *ty) {
    return ty->kind != TVAR;
}

void typedump(Type *ty) {
    if(ty == NULL)  return;

    typedump_core(ty);
    puts("");
}

void typedump_core(Type *ty) {
    switch(ty->kind) {
    case TINT:      printf("int");  break;
    case TBOOL:     printf("bool"); break;
    case TFN: {
        typedump_core(((TFn *)ty)->a);
        printf(" -> ");
        typedump_core(((TFn *)ty)->result);
        break;
    }
    default:        printf("error");
    }
}
