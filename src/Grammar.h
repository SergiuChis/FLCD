#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "ProductionRule.h"


class Grammar
{
public:
    std::list<std::string> nonTerminals;
    std::list<std::string> terminals;
    std::list<ProductionRule> productionRules;
    std::string startSymbol;

    Grammar(std::list<std::string> NonTerminals, std::list<std::string> Terminals, std::list<ProductionRule> ProductionRules, std::string StartSymbol);

    void readFromFile(std::string FilePath);
    std::list<ProductionRule> getProductionRulesFor(std::string NonTerminal);

    std::string nonTerminalsToString();
    std::string terminalsToString();
    std::string productionRulesToString();
};