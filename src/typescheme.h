#ifndef TI_TYPESCHEME_H
#define TI_TYPESCHEME_H

#include "type.h"

/*
 *  ex) body: 'a->'b->'a => tyvars['a, 'b] 
 */
struct TypeScheme {
    Type *tyvars[128];
    Type *body;

    int ntyvar;
};

#endif
