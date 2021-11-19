#include <list>
#include <string>


class ProductionRule
{
public:
    std::string leftSideNonTerminal;
    std::list<std::string> rightSideResult;

    ProductionRule(std::string LeftSideNonTerminal, std::list<std::string> RightSideResult);

    std::string toString();
};