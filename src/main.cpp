#include "SymbolTable.h"
#include "Grammar.h"


int main(int argc, char** argv)
{
    Grammar g{"Inputs/Grammar/g1.txt"};
    
    std::cout << "Start symbol: " << g.startSymbol << std::endl;
    std::cout << "\nTerminals\n";
    std::cout << g.terminalsToString() << std::endl;
    std::cout << "\nNon terminals\n";
    std::cout << g.nonTerminalsToString() << std::endl;
    std::cout << "\nProduction rules\n";
    std::cout << g.productionRulesToString() << std::endl;
    std::cout << "\nCheck if CFG: " << (g.checkCFG() ? "true" : "false") << std::endl;

    std::list<std::string> First = g.firstRecursive("stmtlist");
    std::list<std::string> Follow = g.follow("assignstmt");

    for (auto asdf : Follow)
    {
        std::cout << asdf << " ";
    }
    std::cout << std::endl;

    return 0;
}