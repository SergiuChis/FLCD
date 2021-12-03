#include <list>
#include <string>
#include "Grammar.h"


class LL_ParsingTable
{
public:
    std::list<std::string> nonTerminals;
    std::list<std::string> terminals;

    LL_ParsingTable(Grammar Gr)
    {
        nonTerminals = Gr.nonTerminals;
        terminals = Gr.terminals;
    }
};