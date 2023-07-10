#include <string>
#include "ast.h"

void printDep(int n) {
    for (int i = 0; i < n; ++i) {
        fprintf(stderr, " ");
    }
}

AST::~AST() {

}

opAST::~opAST() {
    if (this->lhs != nullptr) {
        delete this->lhs;
    }
    this->lhs = nullptr;
    if (this->rhs != nullptr) {
        delete this->rhs;
    }
    this->rhs = nullptr;
    this->op = 0;
    this->leftValid = false;
}

double opAST::eval() {
    double l = this->lhs->eval();
    double r = this->rhs->eval();

    switch (this->op) {
        case '+':
            return l+r;
        case '-':
            return l-r;
        case '*':
            return l*r;
        case '/':
            return l/r;
        default:
            return .0f;
    }
}

void opAST::debug(int dep) {
    printDep(dep);
    fprintf(stderr, "`-- Operator: %c\n", this->op);
    if (this->lhs) {
        this->lhs->debug(dep + 2);
    }
    if (this->rhs) {
        this->rhs->debug(dep + 2);
    }
}

std::string opAST::toString() {
    std::string ret = "";
    if (this->leftValid) {
        ret += this->lhs->toString();
    }
    ret += this->op;
    ret += this->rhs->toString();
    return ret;
}

numAST::~numAST() {
    this->num = 0.0f;
}

double numAST::eval() {
    return this->num;
}

std::string numAST::toString() {
    char buf[64] = {0};
    snprintf(buf, 64, "(%f)", this->num);
    return std::string(buf);
}

void numAST::debug(int dep) {
    printDep(dep);
    fprintf(stderr, "`-- Number: %.2f\n", this->num);
}