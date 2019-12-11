#include <stdio.h>
#include <stdbool.h>

#include "parser.h"
#include "token.h"
#include "expr.h"

#define Step() (++pos)
#define Cur_Token() ((Token *)tokens->data[pos])
#define Get_Step_Token() ((Token *)tokens->data[pos++])
#define Cur_Token_Is(tk) ((Cur_Token()->kind) == (tk))

static Expr *enter(void);
static Expr *expr(void);
static Expr *expr_primary(void);

static void unexpect_token(void);
static bool expect(enum TokenKind);


static int pos;
static Vector *tokens;

Expr *parse(Vector *_token) {
    pos = 0;
    tokens = _token;

    return enter();
}

static Expr *enter() {
    if(tokens->len == 0) return NULL;

    Expr *st = expr();

    return st;
}

static bool expect(enum TokenKind tk) {
    if(Cur_Token()->kind == tk) {
        ++pos;
        return true;
    }
    else {
        unexpect_token();
        return false;
    }
}

static Expr *make_let() {
    // let a = expr in expr
    Step();

    bool is_rec = false;

    if(Cur_Token_Is(TK_REC)) {
        is_rec = true;
        Step();
    }

    char *name = Cur_Token()->name;
    expect(TK_IDENT);

    expect(TK_ASSIGN);

    Expr *def = expr();

    expect(TK_IN);

    Expr *body = expr();

    return is_rec ? letrec(name, def, body)
                  : let(name, def, body);
}

static Expr *make_lambda() {
    Step();

    char *name = Get_Step_Token()->name;

    expect(TK_ARROW);

    Expr *e = expr();

    return lambda(name, e);
}

static Expr *make_apply() {
    Step();

    Expr *f = expr();

    Expr *e = expr();

    expect(TK_RPAREN);

    return apply(f, e);
}

static Expr *make_identifer() {
    char *name = Cur_Token()->name;

    Step();

    return var(name);
}

static Expr *expr() {
    return expr_primary();
}

static Expr *expr_primary() {
    if(Cur_Token_Is(TK_LET)) {
        return make_let();
    }
    else if(Cur_Token_Is(TK_FUN)) {
        return make_lambda();
    }
    else if(Cur_Token_Is(TK_IDENT)) {
        return make_identifer();
    }
    else if(Cur_Token_Is(TK_NUMBER)) {
        Expr *i = integer(Cur_Token()->number); 
        Step();
        return i;
    }
    else if(Cur_Token_Is(TK_LPAREN)) {
        return make_apply();
    }
    else if(Cur_Token_Is(TK_END)) {
        return NULL;
    }

    unexpect_token();

    return NULL;
}

static void unexpect_token() {
    fprintf(stderr, "parse error: ");
    fprintf(stderr, "unexpected token: `%s`\n", Cur_Token()->name);
    Step();
}
