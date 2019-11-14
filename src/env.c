#include "env.h"
#include <stdlib.h>

Env *new_env() {
    Env *self = malloc(sizeof(Env));

    self->current = self->ls;
    self->cursor = 0;

    return self;
}

void add_symbol(Env *self, char *sym, Type *type) {
    self->current->key = sym; 
    self->current->type = type;
    self->current++;
    self->cursor++;
}
