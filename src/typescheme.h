#ifndef TI_TYPESCHEME_H
#define TI_TYPESCHEME_H

#include "type.h"
#include "util.h"

typedef struct TypeScheme TypeScheme;

/*
 *  ex) body: 'a->'b->'a => tyvars['a, 'b] 
 */
struct TypeScheme {
    Vector *tyvars;     // Vec<Type *>
    Type *body;
};

TypeScheme *new_tyscheme(Vector *, Type *);

#endif
