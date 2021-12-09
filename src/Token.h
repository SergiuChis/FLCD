#ifndef TOKEN_H
#define TOKEN_H

#include <string>

#define OPERATOR "operator"
#define SEPARATOR "separator"
#define RESERVED_WORD "reserved_word"
#define IDENTIFIER "identifier"
#define CONSTANT "constant"


class Token
{
public:
    std::string type;
    std::string value;
    int line;

    Token(std::string Type, std::string Value);
    Token(std::string Type, std::string Value, int Line);

    std::string toString();
};

#endif