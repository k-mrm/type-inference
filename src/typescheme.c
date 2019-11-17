#include <stdlib.h>

#include "typescheme.h"

TypeScheme *new_tyscheme(Vector *vars, Type *body) {
    TypeScheme *self = malloc(sizeof(TypeScheme));

    self->tyvars = vars;
    self->body = body;

    return self;
}
