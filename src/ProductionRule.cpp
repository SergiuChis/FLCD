#include "ProductionRule.h"

ProductionRule::ProductionRule(std::string LeftSideNonTerminal, std::list<std::string> RightSideResult)
{
    leftSideNonTerminal = LeftSideNonTerminal;
    rightSideResult = RightSideResult;
}

std::string ProductionRule::toString()
{
    std::string Result = leftSideNonTerminal;
    Result += " -> ";
    for (auto& res : rightSideResult)
    {
        Result += res + "|";
    }
    if (Result != "")
    {
        Result.pop_back();
    }
    return Result;
}