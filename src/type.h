#ifndef TI_TYPE_H
#define TI_TYPE_H

#include <stdbool.h>

enum TypeKind {
    /* Type Operator */
    TINT,
    TBOOL,
    TFN,
    TPAIR,
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

        /* Pair */
        struct {
            Type *fst;
            Type *snd;
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
Type *type_pair(Type *, Type *);
bool is_type_variable(Type *);
bool is_type_operator(Type *);
bool same_type(Type *, Type *);

Type *type_operator0(enum TypeKind);
Type *type_operator2(enum TypeKind, Type *, Type *);

void typedump(Type *);
void typedump_core(Type *);

#endif
