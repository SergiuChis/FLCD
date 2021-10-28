#ifndef TOKENIZER_H
#define TOKENIZER_H


#include <list>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include "Token.h"
#include "SymbolTable.h"


class LexicalAnalyzer
{
private:
    std::string code;
    std::list<std::string> operators;
    std::list<std::string> separators;
    std::list<std::string> reserved_words;
    SymbolTable symbolTable{1000};
    std::list<std::pair<std::string, int>> pif;

public:
    LexicalAnalyzer(std::string CodePath, std::string TokenPath);

    std::list<Token> getTokens();
    void writeTables();

private:
    bool isWhiteSpace(char C);
    bool isOperatorOrSeparator(char C);
    bool isLexicallyCorrect(Token Tok);
    void readTokens(const std::string& Path);
};


#endif