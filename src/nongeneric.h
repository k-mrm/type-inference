#ifndef TI_NONGENERIC_H
#define TI_NONGENERIC_H

#include "type.h"

typedef struct NonGeneric NonGeneric;

struct NonGeneric {
    Type *list[128];
    int cursor;
};

NonGeneric *new_non_generic(void);
void add_to_non_generic(NonGeneric *, Type *);
NonGeneric *copy_non_generic(NonGeneric *);

#endif
