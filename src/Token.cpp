#include "Token.h"


Token::Token(std::string Type, std::string Value)
{
    type = Type;
    value = Value;
    line = -1;
}

Token::Token(std::string Type, std::string Value, int Line)
{
    type = Type;
    value = Value;
    line = Line;
}

std::string Token::toString()
{
    return value + " -> " + type + " -> " + std::to_string(line);
}