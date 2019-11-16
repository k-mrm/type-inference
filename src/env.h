#ifndef TI_ENV_H
#define TI_ENV_H

#include "type.h"

typedef struct TypeMap TypeMap;
typedef struct Env Env;

struct TypeMap {
    char *key;
    Type *type;
};

struct Env {
    TypeMap ls[128];
    TypeMap *current;
    unsigned int cursor;
};

Env *new_env();
Env *copy_env();
void add_symbol(Env *, char *, Type *);
Type *lookup(Env *, char *);

#endif
