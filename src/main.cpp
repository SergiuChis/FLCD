#include "SymbolTable.h"
#include "Token.h"
#include "LexicalAnalyzer.h"

#define USAGE "Usage:\n    ./lexer INPUT_FILE_PATH TOKEN_FILE_PATH"
#define DEBUG true


int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << USAGE << std::endl;
        return 0;
    }

    std::string code_path{argv[1]};
    std::string token_path{argv[2]};

    LexicalAnalyzer tokenizer(code_path, token_path);
    std::list<Token> results = tokenizer.getTokens();
    tokenizer.writeTables();

    if (DEBUG)
    {
        for (auto& tok : results)
        {
            std::cout << tok.value << " -> " << tok.type << std::endl;
        }
    }

    return 0;
}