#include "ProductionRule.h"

ProductionRule::ProductionRule(std::list<std::string> LeftSide, std::list<std::string> RightSide)
{
    leftSide = LeftSide;
    rightSide = RightSide;
}

std::string ProductionRule::toString()
{
    std::string Result;
    for (auto& element: leftSide)
    {
        Result += element + " ";
    }
    Result += "-> ";
    for (auto& res : rightSide)
    {
        Result += res + " | ";
    }
    if (Result != "")
    {
        Result.pop_back();
        Result.pop_back();
        Result.pop_back();
    }
    return Result;
}