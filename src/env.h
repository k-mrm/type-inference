#ifndef TI_ENV_H
#define TI_ENV_H

#include "type.h"
#include "typescheme.h"

typedef struct TupleST TupleST;
typedef struct Env Env;

struct TupleST {
    char *key;
    TypeScheme *type;
};

struct Env {
    TupleST ls[128];
    TupleST *current;
    unsigned int cursor;
};

Env *new_env();
Env *copy_env(Env *);
void add_symbol(Env *, char *, TypeScheme *);
TypeScheme *lookup(Env *, char *);

#endif
