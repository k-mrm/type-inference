#include <stdio.h>
#include "type.h"
#include "expr.h"
#include "env.h"
#include "infer.h"

Type *Int;
Type *Bool;

void init(Env *env) {
    Int = type_int();
    Bool = type_bool();

    add_symbol(env, "true", Bool);
    add_symbol(env, "false", Bool);
    add_symbol(env, "+", type_fn(Int, type_fn(Int, Int)));
    add_symbol(env, "*", type_fn(Int, type_fn(Int, Int)));
    add_symbol(env, ">", type_fn(Int, type_fn(Int, Bool)));
    add_symbol(env, "<", type_fn(Int, type_fn(Int, Bool)));
}

int main(void) {
    Env *env = new_env();

    init(env);

    Type *a = analyze(
        env,
        integer(200)
    );
    typedump(a);

    Type *b = analyze(env, var("true"));
    typedump(b);

    Type *c = analyze(env, var("+"));
    typedump(c);

    return 0;
}
