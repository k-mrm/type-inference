#include "type.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

Type *type_fn(Type *a, Type *r) {
    TFn *self = malloc(sizeof(TFn));

    ((Type *)self)->kind = TFN;
    self->a = a;
    self->result = r;

    return (Type *)self;
}

Type *type_var(int id) {
    TVar *self = malloc(sizeof(TFn));

    ((Type *)self)->kind = TVAR;
    self->id = id;

    return (Type *)self;
}

char *type_show(Type *ty) {
    assert(ty);

    switch(ty->kind) {
    case TINT:      return "int";
    case TBOOL:     return "bool";
    case TFN: {
        char *a = type_show(((TFn *)ty)->a);
        char *ret = type_show(((TFn *)ty)->result); 
        
        char *res = malloc(strlen(a) + strlen(ret));

        sprintf(res, "%s -> %s", a, ret);

        return res;
    }
    default:        return "Error";
    }
}
