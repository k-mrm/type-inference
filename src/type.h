#ifndef TI_TYPE_H
#define TI_TYPE_H

#define TYPE_BASE Type base;

#include <stdbool.h>

enum TypeKind {
    TINT,
    TBOOL,
    TFN,
    TVAR,       // Type Variable
    TUNKNOWN,
};

struct Type {
    enum TypeKind kind; 
};

typedef struct Type Type;

typedef struct TInt TInt;
typedef struct TBool TBool;
typedef struct TFn TFn;
typedef struct TVar TVar;
typedef struct TUnknown TUnknown;

struct TInt {
    TYPE_BASE;
};

struct TBool {
    TYPE_BASE;
};

struct TFn {
    TYPE_BASE;
    Type *a,
         *result;
};

struct TVar {
    TYPE_BASE;
    int id;
    char n;
    Type *instance;
};

struct TUnknown {
    TYPE_BASE;
};

Type *type_int();
Type *type_bool();
Type *type_unknown();
Type *type_fn(Type *, Type *);
Type *type_var(int);
bool is_type_variable(Type *);
bool is_type_operator(Type *);

void typedump(Type *);
void typedump_core(Type *);

#endif
