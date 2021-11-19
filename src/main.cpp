#include "SymbolTable.h"
#include "Token.h"
#include "LexicalAnalyzer.h"
#include "Grammar.h"

#define USAGE "Usage:\n    ./lexer INPUT_FILE_PATH TOKEN_FILE_PATH"
#define DEBUG true


int main(int argc, char** argv)
{
    Grammar::readFromFile("Inputs/Grammar/g1.txt");

    return 0;
}