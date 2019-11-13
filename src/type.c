#include <stdlib.h>
#include "type.h"

TInt *new_tint() {
    TInt *self = malloc(sizeof(TInt));

    ((Type *)self)->kind = TINT; 

    return self;
}

TFn *new_tfn(Type *a, Type *r) {
    TFn *self = malloc(sizeof(TFn));

    ((Type *)self)->kind = TFN;
    self->a = a;
    self->result = r;

    return self;
}

TVar *new_tvar(int id) {
    TVar *self = malloc(sizeof(TFn));

    ((Type *)self)->kind = TVAR;
    self->id = id;

    return self;
}
