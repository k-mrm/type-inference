#include <stdio.h>
#include <string.h>

#include "type.h"
#include "expr.h"
#include "env.h"
#include "infer.h"
#include "util.h"
#include "lexer.h"
#include "parser.h"

Type *Int;
Type *Bool;

void init(Env *env) {
    Int = type_int();
    Bool = type_bool();

    Type *var1 = type_var();
    Type *var2 = type_var();

    add_to_env(env, "true", Bool);
    add_to_env(env, "false", Bool);
    add_to_env(env, "+", type_fn(Int, type_fn(Int, Int)));
    add_to_env(env, "-", type_fn(Int, type_fn(Int, Int)));
    add_to_env(env, "*", type_fn(Int, type_fn(Int, Int)));
    add_to_env(env, ">", type_fn(Int, type_fn(Int, Bool)));
    add_to_env(env, "<", type_fn(Int, type_fn(Int, Bool)));

    add_to_env(env, "pair", type_fn(
                                var1,
                                type_fn(var2, type_pair(var1, var2))
                            )
    );

    Type *var3 = type_var();
    Type *var4 = type_var();
    add_to_env(env, "fst", type_fn(type_pair(var3, var4), var3));
    Type *var5 = type_var();
    Type *var6 = type_var();
    add_to_env(env, "snd", type_fn(type_pair(var5, var6), var6));

    Type *var7 = type_var();
    add_to_env(env, "if", type_fn(Bool, type_fn(var7, type_fn(var7, var7))));
}

int main(void) {
    Env *env = new_env();

    init(env);

    /*
    Expr *els[] = {
        integer(200),
        var("choko"),   // error
        var("+"),
        var("true"),
        var("pair"),
        var("fst"),
        var("snd"),
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
        lambda("n", lambda("m", integer(300))),
        let(
            "f",
            lambda("x", var("x")),
            apply(
                apply(
                    var("pair"),
                    apply(var("f"), integer(200))
                ),
                apply(var("f"), var("true"))
            )
        ),
        apply(
            var("fst"),
            apply(
                apply(var("pair"), var("false")),
                integer(100000)
            )
        ),
        apply(
            var("snd"),
            apply(
                apply(var("pair"), var("false")),
                integer(100000)
            )
        ),
        letrec(     // let rec fibo n = if n < 2 then n else fibo(n - 2) + fibo(n - 1)
            "fibo",
            lambda(
                "n",
                apply(
                    apply(
                        apply(
                            var("if"),
                            binary(var("n"), "<", integer(2))
                        ),
                        var("n")
                    ),
                    binary(
                        apply(
                            var("fibo"),
                            binary(var("n"), "-", integer(2))
                        ),
                        "+",
                        apply(
                            var("fibo"),
                            binary(var("n"), "-", integer(1))
                        )
                    )
                )
            ),
            var("fibo")
        ),
    };

    int nels = sizeof(els) / sizeof(els[0]);

    for(int i = 0; i < nels; i++) {
        exprdump(els[i]);
        printf(" : ");
        printf("\e[1m");
        typedump(prune(analyze(env, els[i], NULL)));
        printf("\e[0m");
    } */

    char src[256] = {0};
    int cursor;
    char c;

    for(;;) {
        printf(">> ");
        memset(src, 0, 256);
        cursor = 0;

        while((c = getchar()) != '\n') {
            if(c == EOF) return 0;

            src[cursor++] = c;
        }
        typedump(analyze(env, parse(lex(src)), NULL));
    }

    return 0;
}
