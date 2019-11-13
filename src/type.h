#ifndef TI_TYPE_H
#define TI_TYPE_H

#define TYPE_BASE Type base;

enum TypeKind {
    TINT,
    TBOOL,
    TFN,
    TVAR,       // Type Variable
};

struct Type {
    enum TypeKind kind; 
};

typedef struct Type Type;

typedef struct TInt TInt;
typedef struct TBool TBool;
typedef struct TFn TFn;
typedef struct TVar TVar;

struct TInt {
    TYPE_BASE;
};

struct TBool {
    TYPE_BASE;
};

struct TFn {
    TYPE_BASE;

    Type *a;
    Type *result;
};

struct TVar {
    TYPE_BASE;

    int id;
};

TInt *type_int();
TBool *type_bool();
TFn *type_fn(Type *, Type *);
TVar *type_var(int);

#endif
