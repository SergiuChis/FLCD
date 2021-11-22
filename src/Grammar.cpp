#include "Grammar.h"

Grammar::Grammar(std::string FilePath)
{
    readFromFile(FilePath);
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

        std::list<std::string> LeftSide;
        std::list<std::string> RightSide;
        std::string Word;
        std::string CurrentResult;
        ss >> Word;
        while (Word != "::=")
        {
            if (Word[0] == '\"' && Word[Word.size() - 1] == '\"')
            {
                terminals.push_back(Word);
            }
            else
            {
                nonTerminals.push_back(Word);
            }
            LeftSide.push_back(Word);
            ss >> Word;
        }
        while (ss >> Word)
        {
            if (Word[0] == '\"' && Word[Word.size() - 1] == '\"')
            {
                terminals.push_back(Word);
                // RightSideResult.push_back(Word);
                CurrentResult += Word + " ";
            }
            else if (Word != "|")
            {
                nonTerminals.push_back(Word);
                // RightSideResult.push_back(Word);
                CurrentResult += Word + " ";
            }
            else
            {
                RightSide.push_back(CurrentResult);
                CurrentResult = "";
            }
        }
        RightSide.push_back(CurrentResult);

        productionRules.push_back(ProductionRule{LeftSide, RightSide});

        eliminateDuplicates(terminals);
        eliminateDuplicates(nonTerminals);
    }

    Input.close();
}

std::list<ProductionRule> Grammar::getProductionRulesFor(std::string NonTerminal)
{
    std::list<ProductionRule> Results;

    for (auto pr : productionRules)
    {
        if (*pr.leftSide.begin() == NonTerminal)
        {
            Results.push_back(pr);
        }
    }

    return Results;
}

bool Grammar::checkCFG()
{
    for (auto& pr: productionRules)
    {
        if (pr.leftSide.size() != 1)
        {
            return false;
        }

        std::string Element = *pr.leftSide.begin();
        if (Element[0] == '\"' && Element[Element.size() - 1] == '\"')
        {
            return false;
        }
    }
    return true;
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
        Result += nt.toString() + "\n";
    }

    if (Result != "")
    {
        Result.pop_back();
        Result.pop_back();
    }
    return Result;
}

void Grammar::eliminateDuplicates(std::list<std::string>& List)
{
    std::set<std::string> Set;

    for (auto element : List)
    {
        Set.insert(element);
    }

    List.clear();
    for (auto element: Set)
    {
        List.push_back(element);
    }
}