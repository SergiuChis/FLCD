#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>

#include "ProductionRule.h"


class Grammar
{
public:
    std::list<std::string> nonTerminals;
    std::list<std::string> terminals;
    std::list<ProductionRule> productionRules;
    std::string startSymbol;

    Grammar(std::string FilePath);

private:
    void readFromFile(std::string FilePath);
    void eliminateDuplicates(std::list<std::string>& List);

public:
    std::list<ProductionRule> getProductionRulesFor(std::string NonTerminal);
    bool checkCFG();

    std::string nonTerminalsToString();
    std::string terminalsToString();
    std::string productionRulesToString();
};