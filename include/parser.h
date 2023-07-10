#ifndef __PARSER__
#define __PARSER__

#include "lexer.h"
#include "ast.h"

class Parser {
    private:
        Lexer *lexer;
        AST *root;
    protected:
        AST *parseExpr();
        AST *parseTerm();
        AST *parseFactor();
        AST *parseTerm_(AST *lhs);
        AST *parseExpr_(AST *lhs);

    public:
        Parser();

        ~Parser();

        void parse();

        AST *getAST();

        void clean();
};

#endif