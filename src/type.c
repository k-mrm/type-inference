#include <stdlib.h>
#include "type.h"

TInt *type_int() {
    TInt *self = malloc(sizeof(TInt));

    ((Type *)self)->kind = TINT; 

    return self;
}

TBool *type_bool() {
    TBool *self = malloc(sizeof(TBool));

    ((Type *)self)->kind = TBOOL;

    return self;
}

TFn *type_fn(Type *a, Type *r) {
    TFn *self = malloc(sizeof(TFn));

    ((Type *)self)->kind = TFN;
    self->a = a;
    self->result = r;

    return self;
}

TVar *type_var(int id) {
    TVar *self = malloc(sizeof(TFn));

    ((Type *)self)->kind = TVAR;
    self->id = id;

    return self;
}
