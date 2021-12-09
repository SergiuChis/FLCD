#pragma once

#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>

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

    void pushProductionRule(ProductionRule Pr);
    void popProductionRule(ProductionRule Pr);

    void readFromFile(std::string FilePath);
    void eliminateDuplicates(std::list<std::string>& List);
    public:
    std::list<std::string> firstRecursive(std::string NonTerminal);
    std::list<ProductionRule> getProductionRulesRightSide(std::string NonTerminal);
    public:
    std::list<std::string> follow(std::string NonTerminal);


public:
    std::list<ProductionRule> getProductionRulesFor(std::string NonTerminal);
    std::list<std::string> first(std::string NonTerminal);
    bool checkCFG();

    std::string nonTerminalsToString();
    std::string terminalsToString();
    std::string productionRulesToString();

    ProductionRule getProductionRuleFor(std::string NonTerminal, std::string Terminal);
};