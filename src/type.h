#ifndef TI_TYPE_H
#define TI_TYPE_H

#define TYPE_BASE Type base;

#include <stdbool.h>

enum TypeKind {
    /* Type Operator */
    TINT,
    TBOOL,
    TFN,
    /* Type Variable  */
    TVAR,
};

typedef struct Type Type;

struct Type {
    enum TypeKind kind; 
    int ntype;
    Type *types[2];

    union {
        /* Function */
        struct {
            Type *arg;
            Type *result;
        };

        /* Type Variable */
        struct {
            int id;
            char name;
            Type *instance;
        };
    };
};

Type *type_int(void);
Type *type_bool(void);
Type *type_fn(Type *, Type *);
Type *type_var(void);
bool is_type_variable(Type *);
bool is_type_operator(Type *);

void typedump(Type *);
void typedump_core(Type *);

#endif
