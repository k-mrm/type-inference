#include <stdio.h>

#include "parser.h"
#include "token.h"

#define Step() (++pos)
#define Cur_Token() ((Token *)tokens->data[pos])
#define Get_Step_Token() ((Token *)tokens->data[pos++])
#define Cur_Token_Is(tk) ((Cur_Token()->kind) == (tk))

static Expr *enter(void);
static Expr *expr(void);
static void parse_error(void);

static int pos;
static Vector *tokens;

Expr *parse(Vector *_token) {
    pos = 0;
    tokens = _token;

    return enter();
}

static Expr *enter() {
    Expr *st;

    while(!Cur_Token_Is(TK_END)) {
        st = expr();
    }

    return st;
}

static Expr *expr() {
    if(Cur_Token_Is(TK_LET)) {
        ;
    }
    else if(Cur_Token_Is(TK_FUN)) {
        ;
    }
    else if(Cur_Token_Is(TK_IDENT)) {
        ;
    }
    else if(Cur_Token_Is(TK_NUMBER)) {
        Expr *i = integer(Cur_Token()->number); 
        Step();
        return i;
    }

    parse_error();

    return NULL;
}

static void parse_error() {
    fprintf(stderr, "parse error: ");
    fprintf(stderr, "unexpected %s\n", Cur_Token()->name);
    Step();
}
