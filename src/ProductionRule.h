#include <list>
#include <string>


class ProductionRule
{
public:
    std::list<std::string> leftSide;
    std::list<std::string> rightSide;

    ProductionRule(std::list<std::string> LeftSide, std::list<std::string> RightSide);

    std::string toString();
};