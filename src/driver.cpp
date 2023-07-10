#include "parser.h"
#include "ast.h"

int main(int argc, const char **argv) {
    Parser p;
    p.parse();
    AST *root = p.getAST();
    root->debug(0);
    fprintf(stderr, "Result: %.2f\n", root->eval());
}