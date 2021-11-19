#include "Grammar.h"

Grammar::Grammar(std::list<std::string> NonTerminals, std::list<std::string> Terminals, std::list<ProductionRule> ProductionRules, std::string StartSymbol)
{
    nonTerminals = NonTerminals;
    terminals = Terminals;
    productionRules = ProductionRules;
    startSymbol = StartSymbol;
}

void Grammar::readFromFile(std::string FilePath)
{
    std::fstream Input;
    Input.open(FilePath);

    std::string Line;
    while (getline(Input, Line))
    {
        std::stringstream ss;
        ss << Line;

        std::string Word;
        ss >> Word;
        std::cout << Word << std::endl;
    }
}

std::list<ProductionRule> Grammar::getProductionRulesFor(std::string NonTerminal)
{
    std::list<ProductionRule> Results;

    for (auto pr : productionRules)
    {
        if (pr.leftSideNonTerminal == NonTerminal)
        {
            Results.push_back(pr);
        }
    }

    return Results;
}

std::string Grammar::nonTerminalsToString()
{
    std::string Result;

    for (auto& nt : nonTerminals)
    {
        Result += nt + ", ";
    }

    if (Result != "")
    {
        Result.pop_back();
        Result.pop_back();
    }
    return Result;
}

std::string Grammar::terminalsToString()
{
    std::string Result;

    for (auto& nt : terminals)
    {
        Result += nt + ", ";
    }

    if (Result != "")
    {
        Result.pop_back();
        Result.pop_back();
    }
    return Result;
}

std::string Grammar::productionRulesToString()
{
    std::string Result;

    for (auto& nt : productionRules)
    {
        Result += nt.toString() + ", ";
    }

    if (Result != "")
    {
        Result.pop_back();
        Result.pop_back();
    }
    return Result;
}