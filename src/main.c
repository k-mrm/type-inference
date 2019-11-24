#include <stdio.h>

#include "type.h"
#include "expr.h"
#include "env.h"
#include "infer.h"
#include "util.h"

Type *Int;
Type *Bool;

void init(Env *env) {
    Int = type_int();
    Bool = type_bool();

    add_to_env(env, "true", Bool);
    add_to_env(env, "false", Bool);
    add_to_env(env, "+", type_fn(Int, type_fn(Int, Int)));
    add_to_env(env, "*", type_fn(Int, type_fn(Int, Int)));
    add_to_env(env, ">", type_fn(Int, type_fn(Int, Bool)));
    add_to_env(env, "<", type_fn(Int, type_fn(Int, Bool)));
    add_to_env(env, "test", type_fn(Int, type_fn(Bool, Int)));
}

int main(void) {
    Env *env = new_env();

    init(env);

    Expr *els[] = {
        integer(200),
        var("choko"),
        var("<"),
        let("x", integer(10), var("x")),
        let("y", var("false"), var("y")),
        let("z", integer(200), binary(var("z"), "+", integer(210))),
        lambda(
            "a",
            lambda(
                "b",
                binary(var("a"), ">", var("b"))
            )
        ),
        let(
            "add",
            lambda(
                "a",
                lambda(
                    "b",
                    binary(var("a"), "+", var("b"))
                )
            ),
            apply(
                apply(
                    var("add"),
                    integer(100)
                ),
                integer(200)
            )
        ),
        lambda("x", var("x")),
        let(
            "f",
            lambda("x", var("x")),
            binary(
                apply(var("f"), integer(200)),
                "test",
                apply(var("f"), var("true"))
            )
        ),
    };

    int nels = sizeof(els) / sizeof(els[0]);

    for(int i = 0; i < nels; i++) {
        exprdump(els[i]);
        printf(" : ");
        printf("\e[1m");
        typedump(prune(analyze(env, els[i], NULL)));
        printf("\e[0m");
    }

    return 0;
}
