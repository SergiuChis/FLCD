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
    getline(Input, Line);
    startSymbol = Line;

    while (getline(Input, Line))
    {
        std::stringstream ss;
        ss << Line;

        std::list<std::string> LeftSide;
        std::list<std::string> OneElementRightSide;
        std::list<std::list<std::string>> RightSide;
        std::string Word;
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
                // CurrentResult += Word + " ";
                OneElementRightSide.push_back(Word);
            }
            else if (Word != "|")
            {
                nonTerminals.push_back(Word);
                // RightSideResult.push_back(Word);
                // CurrentResult += Word + " ";
                OneElementRightSide.push_back(Word);
            }
            else
            {
                RightSide.push_back(OneElementRightSide);
                // CurrentResult = "";
                OneElementRightSide.clear();
            }
        }
        RightSide.push_back(OneElementRightSide);

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

std::list<std::string> Grammar::firstRecursive(std::string NonTerminal)
{
    std::list<ProductionRule> ProdRulesForGivenNonTerminal = getProductionRulesFor(NonTerminal);
    std::list<std::string> Result;
    std::list<std::string> TempFirstStore;

    for (auto Pr : ProdRulesForGivenNonTerminal)
    {
        for (auto El : Pr.rightSide)
        {
            for (auto FirstElement : El)
            {
                if ((FirstElement[0] == '\"' && FirstElement[FirstElement.size() - 1] == '\"') || FirstElement == "eps")
                {
                    Result.push_back(FirstElement);
                    break;
                }
                else
                {
                    TempFirstStore = first(FirstElement);
                    auto Found = std::find(TempFirstStore.begin(), TempFirstStore.end(), "eps");
                    if (Found != TempFirstStore.end())
                    {
                        TempFirstStore.erase(Found);
                        Result.splice(Result.end(), TempFirstStore);
                    }
                    else
                    {
                        Result.splice(Result.end(), TempFirstStore);
                        break;
                    }
                }
            }
        }
    }

    eliminateDuplicates(Result);
    return Result;
}

std::list<std::string> Grammar::first(std::string NonTerminal)
{
    std::list<std::string> Result = firstRecursive(NonTerminal);
    auto Found = std::find(Result.begin(), Result.end(), "eps");
    if (Found != Result.end())
    {
        Result.erase(Found);
    }
    return Result;
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