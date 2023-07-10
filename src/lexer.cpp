#include <vector>
#include <string>

#include "lexer.h"

void Lexer::read() {
    this->LastChar = getchar();
    // 由于只需要一个一行的表达式，当读取到换行的时候，结束即可
    if (this->LastChar == EOF ||this->LastChar == '\n' || this->LastChar == '\r') {
        this->LastChar = EOF;
        return;
    }
    this->Input.push_back(this->LastChar);
    ++this->CurPos;
}

Lexer::Lexer() {
    this->CurPos = 0;
    this->Hold = false;
    this->CurToken = tok_unknown;
    this->read();
}

// 获取当前的 Token
int Lexer::next() {
    // 如果已经停止读取，直接返回
    if (this->Hold) {
        this->Hold = false;
        return this->CurToken;
    }

    // 跳过空格
    while (isspace(this->LastChar)) {
        this->read();
    }

    // 如果是数字，读取完整的数字
    if (isdigit(this->LastChar)) {
        this->Word.clear();
        while (isdigit(this->LastChar)) {
            this->Word += this->LastChar;
            this->read();
        }
        this->CurToken = tok_num;
        return tok_num;
    }

    // 如果是运算符，直接返回
    if (this->LastChar == '+') {
        this->CurToken = tok_plus;
        this->read();
        return tok_plus;
    }

    if (this->LastChar == '-') {
        this->CurToken = tok_minus;
        this->read();
        return tok_minus;
    }

    if (this->LastChar == '*') {
        this->CurToken = tok_star;
        this->read();
        return tok_star;
    }

    if (this->LastChar == '/') {
        this->CurToken = tok_slash;
        this->read();
        return tok_slash;
    }

    if (this->LastChar == '(') {
        this->CurToken = tok_lparen;
        this->read();
        return tok_lparen;
    }

    if (this->LastChar == ')') {
        this->CurToken = tok_rparen;
        this->read();
        return tok_rparen;
    }

    // 未知的 Token
    this->read();
    this->CurToken = tok_unknown;
    return tok_unknown;
}

// 获取当前的数字
const std::string& Lexer::getWord() {
    return this->Word;
}

// 获取当前的位置
int Lexer::getPos() {
    return this->CurPos;
}

void Lexer::hold() {
    this->Hold = true;
}
