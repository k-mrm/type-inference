#ifndef TI_INFER_H
#define TI_INFER_H

#include "env.h"
#include "expr.h"

Type *prune(Type *);
Type *analyze(Env *, Expr *);


#endif
