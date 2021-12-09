#include "LL_ParsingTable.h"

LL_ParsingTable::LL_ParsingTable(Grammar Gr)
{
    nonTerminals = Gr.nonTerminals;
    terminals = Gr.terminals;
    buildTable(Gr);
}

std::string LL_ParsingTable::toString()
{
    std::string result;
    for (auto it : table) {
        //std::cout << "rule for " << it << " " << terminal << ":\n " << g.getProductionRuleFor(it, terminal).toString() << '\n';
        result += "rule for " + it.first.first + " " + it.first.second + ":\n " + it.second.toString() + '\n';
    }

    return result;
}

void LL_ParsingTable::buildTable(Grammar Gr)
{
    for (auto it : Gr.nonTerminals) {
        for (auto terminal : Gr.terminals) {
            if (it != "eps") {
                auto result = Gr.getProductionRuleFor(it, terminal);
                table[std::make_pair(it, terminal)] = result;
            }
        }
    }
}