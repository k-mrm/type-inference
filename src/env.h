#ifndef TI_ENV_H
#define TI_ENV_H

#include "type.h"

typedef struct TupleST TupleST;
typedef struct Env Env;

struct TupleST {
    char *key;
    Type *type;
};

struct Env {
    TupleST ls[128];
    TupleST *current;
    unsigned int cursor;
};

Env *new_env();
Env *copy_env(Env *);
void add_symbol(Env *, char *, Type *);
Type *lookup(Env *, char *);

#endif
