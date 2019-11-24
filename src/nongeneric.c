#include <stdlib.h>

#include "nongeneric.h"

NonGeneric *new_non_generic() {
    NonGeneric *self = malloc(sizeof(NonGeneric));

    self->cursor = 0;

    return self;
}

void add_to_non_generic(NonGeneric *self, Type *s) {
    self->list[self->cursor++] = s;
}

NonGeneric *copy_non_generic(NonGeneric *src) {
    NonGeneric *dst = malloc(sizeof(NonGeneric));

    *dst = *src;

    return dst;
}
