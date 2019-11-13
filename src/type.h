#ifndef TI_TYPE_H
#define TI_TYPE_H

#define TYPE_BASE Type base;

enum TypeKind {
    TINT,
    TFN,
    TVAR,       // Type Variable
};

struct Type {
    enum TypeKind kind; 
};

typedef struct Type Type;

typedef struct TInt TInt;
typedef struct TFn TFn;
typedef struct TVar TVar;

struct TInt {
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

TInt *new_tint();
TFn *new_tfn(Type *, Type *);
TVar *new_tvar(int);

#endif
