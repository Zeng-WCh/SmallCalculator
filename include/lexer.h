#ifndef __LEXER__
#define __LEXER__

#include <vector>
#include <string>

enum Token {
    tok_eof, 
    tok_num,
    tok_plus,
    tok_minus,
    tok_star,
    tok_slash,
    tok_lparen,
    tok_rparen,
    tok_unknown,
};

class Lexer {
    private:
        // 存储上一个字符
        int LastChar;
        // 存储当前字符的位置，用于报错
        int CurPos;
        // 存储当前的 Token
        Token CurToken;
        // 是否停止读取
        bool Hold;
        // 存储当前的数字
        std::string Word;
        // 存储输入的字符串，用于报错
        std::vector<char> Input;
    protected:
        void read();
    public:
        Lexer();
        ~Lexer() = default;
        int next();
        const std::string& getWord();
        int getPos();
        void hold();
};

#endif