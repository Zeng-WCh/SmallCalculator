#include "parser.h"
#include "lexer.h"

void log_error(const char *fmt, int pos) {
    fprintf(stderr, "An Error Occured %s while parsing near by <%d>", fmt, pos);
}

Parser::Parser() {
    this->lexer = new Lexer();
    this->root = nullptr;
}

Parser::~Parser() {
    if (this->lexer) {
        delete this->lexer;
    }
    this->lexer = nullptr;
    if (this->root) {
        delete this->root;
    }
    this->root = nullptr;
}

void Parser::parse() {
    this->root = parseExpr();
}

AST* Parser::parseExpr() {
    AST *lhs = this->parseTerm();
    return this->parseExpr_(lhs);
}

AST *Parser::parseTerm() {
    AST *lhs = this->parseFactor();
    return this->parseTerm_(lhs);
}

AST *Parser::parseFactor() {
    int t = this->lexer->next();

    if (t == Token::tok_num) {
        return new numAST(std::stod(this->lexer->getWord()));
    }
    else if (t == Token::tok_lparen) {
        AST *expr = this->parseExpr();
        t = this->lexer->next();
        if (t != Token::tok_rparen) {
            log_error("Expecting ')'", this->lexer->getPos());
            exit(1);
        }
        return expr;
    }

    else {
        log_error("Expecting '(' or num", this->lexer->getPos());
    }
}

AST *Parser::parseTerm_(AST *lhs) {
    int op = this->lexer->next();

    if (op == Token::tok_star || op == Token::tok_slash) {
        char operators = (op == Token::tok_star?'*':'/');
        AST *rhs = this->parseTerm();
        AST *node = new opAST(operators, lhs, rhs);
        return this->parseTerm_(node);
    }
    else {
        this->lexer->hold();
        return lhs;
    }
}

AST *Parser::parseExpr_(AST *lhs) {
    int op = this->lexer->next();

    if (op == Token::tok_plus || op == Token::tok_minus) {
        char operators = (op == Token::tok_plus?'+':'-');
        AST *rhs = this->parseExpr();
        AST *node = new opAST(operators, lhs, rhs);
        return this->parseExpr_(node);
    }
    else {
        this->lexer->hold();
        return lhs;
    }
}

AST *Parser::getAST() {
    return this->root;
}

void Parser::clean() {
    delete this->root;
    this->root = nullptr;
    delete this->lexer;
    this->lexer = new Lexer();
}