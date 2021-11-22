#include "SymbolTable.h"
#include "Token.h"
#include "LexicalAnalyzer.h"
#include "Grammar.h"

#define USAGE "Usage:\n    ./lexer INPUT_FILE_PATH TOKEN_FILE_PATH"
#define DEBUG true


int main(int argc, char** argv)
{
    Grammar g{"Inputs/Grammar/g1.txt"};
    
    std::cout << "Terminals\n";
    std::cout << g.terminalsToString() << std::endl;
    std::cout << "\nNon terminals\n";
    std::cout << g.nonTerminalsToString() << std::endl;
    std::cout << "\nProduction rules\n";
    std::cout << g.productionRulesToString() << std::endl;
    std::cout << "\nCheck if CFG: " << (g.checkCFG() ? "true" : "false") << std::endl;

    return 0;
}