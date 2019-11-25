#include <stdlib.h>
#include <string.h>

#include "env.h"
#include "infer.h"

Env *new_env() {
    Env *self = malloc(sizeof(Env));

    self->cursor = 0;

    return self;
}

Env *copy_env(Env *src) {
    Env *dst = malloc(sizeof(Env));

    *dst = *src;

    return dst;
}

void add_to_env(Env *self, char *sym, Type *type) {
    self->list[self->cursor].key = sym; 
    self->list[self->cursor].type = type;
    self->cursor++;
}

Type *lookup(Env *self, char *key, NonGeneric *nongeneric) {
    for(int i = 0; i < self->cursor; i++) {
        if(strcmp(key, self->list[i].key) == 0) {
            return fresh(self->list[i].type, nongeneric);
        }
    }

    return NULL;
}
