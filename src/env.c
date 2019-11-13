#include "env.h"
#include <stdlib.h>

Env *new_env() {
    Env *self = malloc(sizeof(Env));

    self->current = self->ls;
    self->cur = 0;

    return self;
}

