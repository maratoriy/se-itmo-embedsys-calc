#ifndef AST_H_
#define AST_H

#include <inttypes.h>
#include <stdio.h>

struct AST {
    enum AST_type {
        AST_BINOP, AST_UNOP, AST_LIT
    } type;
    union {
        struct binop {
            enum binop_type {
                BIN_PLUS,
                BIN_MINUS,
                BIN_MUL,
                BIN_DIV,
                BIN_MOD,
                BIN_AND,
                BIN_OR,
                BIN_IMPL,
                BIN_BIC
            } type;
            struct AST *left, *right;
        } as_binop;
        struct unop {
            enum unop_type {
                UN_NEG, UN_FACT, UN_NEGL
            } type;
            struct AST *operand;
        } as_unop;
        struct literal {
            int64_t value;
        } as_literal;
    };
};

struct AST *newnode(struct AST ast);

struct AST _lit(int64_t value);

struct AST *lit(int64_t value);

struct AST _unop(enum unop_type type, struct AST *operand);

struct AST *unop(enum unop_type type, struct AST *operand);

struct AST _binop(enum binop_type type, struct AST *left, struct AST *right);

struct AST *binop(enum binop_type type, struct AST *left, struct AST *right);

#define DECLARE_BINOP(fun, code)                                             \
static struct AST *fun(struct AST *left, struct AST *right) {                \
  return binop(BIN_##code, left, right);                                     \
}

DECLARE_BINOP(add, PLUS)
DECLARE_BINOP(mul, MUL)
DECLARE_BINOP(sub, MINUS)
DECLARE_BINOP(divide, DIV)
DECLARE_BINOP(mod, MOD)
DECLARE_BINOP(and, AND)
DECLARE_BINOP(or, OR)
DECLARE_BINOP(implication, IMPL)
DECLARE_BINOP(bicondition, BIC)

#undef DECLARE_BINOP

#define DECLARE_UNOP(fun, code)                                              \
static struct AST *fun(struct AST *operand) {                                \
  return unop(UN_##code, operand);                                           \
}

DECLARE_UNOP(neg, NEG)
DECLARE_UNOP(negl, NEGL)
DECLARE_UNOP(fact, FACT)

#undef DECLARE_UNOP

void print_ast(FILE *f, struct AST *ast);
void ast_print(struct AST ast);

int64_t calc_ast(struct AST *ast);
void p_print_ast(FILE *f, struct AST *ast);

#endif
