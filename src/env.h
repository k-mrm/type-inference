#ifndef TI_ENV_H
#define TI_ENV_H

#include "util.h"

struct TypeMap {
    Env *parent;

    char *key;
    Type *type;
};

struct Env {
    TypeMap ls[128];
    TypeMap *current;
    unsigned int cur;
};

Env *new_env();

#endif
