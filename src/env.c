#include "env.h"
#include <stdlib.h>
#include <string.h>

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

Type *lookup(Env *self, char *key) {
    for(int i = 0; i < self->cursor; i++) {
        if(strcmp(key, self->ls[i].key) == 0) {
            return self->ls[i].type;
        }
    }

    return NULL;
}
