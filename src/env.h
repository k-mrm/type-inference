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
    TupleST list[128];
    unsigned int cursor;
};

Env *new_env();
Env *copy_env(Env *);
void add_to_env(Env *, char *, Type *);
Type *lookup(Env *, char *);

#endif
