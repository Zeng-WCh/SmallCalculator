#ifndef __AST__
#define __AST__

#include <string>
class AST {
    public:
        virtual ~AST() = 0;
        virtual double eval() = 0;
        virtual std::string toString() = 0;
        virtual void debug(int) = 0;
};

class opAST : public AST {
    private:
        char op;
        AST *lhs, *rhs;
        bool leftValid;
    public:
        opAST(char op = 0, AST *lhs = nullptr, AST *rhs = nullptr, bool leftValid = true) : op(op), lhs(lhs), rhs(rhs), leftValid(leftValid) {}
        ~opAST();
        double eval() override;
        std::string toString() override;
        void debug(int dep) override;
};

class numAST : public AST {
    private:
        double num;
    public:
        numAST(double num = .0f) : num(num) {}
        ~numAST();
        double eval() override;
        std::string toString() override;
        void debug(int dep) override;
};

#endif