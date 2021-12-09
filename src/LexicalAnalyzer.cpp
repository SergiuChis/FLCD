#include "LexicalAnalyzer.h"
#include <iostream>


LexicalAnalyzer::LexicalAnalyzer(std::string CodePath, std::string TokenPath)
{
    std::ifstream code_file(CodePath);
    std::string Code((std::istreambuf_iterator<char>(code_file)), (std::istreambuf_iterator<char>()));
    code = Code;

    readTokens(TokenPath);
}

std::list<Token> LexicalAnalyzer::getTokens()
{
    std::list<Token> Tokens;
    int Current_line = 1;

    for (int i = 0; i < code.size(); ++i)
    {
        if (code[i] == '\n')
        {
            Current_line++;
        }
        std::list<Token> Tokens_found;
        for (auto const& Tok : operators)
        {
            if (code.find(Tok, i) == i)
            {
                Tokens_found.push_back(Token(OPERATOR, Tok, Current_line));
            }
        }
        for (auto const& Tok : separators)
        {
            if (code.find(Tok, i) == i)
            {
                Tokens_found.push_back(Token(SEPARATOR, Tok, Current_line));
            }
        }
        for (auto const& Tok : reserved_words)
        {
            if (code.find(Tok, i) == i && (isWhiteSpace(code[i + Tok.size()]) || isOperatorOrSeparator(code[i + Tok.size()])))
            {
                Tokens_found.push_back(Token(RESERVED_WORD, Tok, Current_line));
            }
        }

        if (Tokens_found.size() > 1)
        {
            Token Longest{"", "", -1};
            int Biggest_size = 0;
            for (auto& Tok : Tokens_found)
            {
                if (Tok.value.size() > Biggest_size)
                {
                    Biggest_size = Tok.value.size();
                    Longest.type = Tok.type;
                    Longest.value = Tok.value;
                }
            }
            Tokens.push_back(Longest);
            pif.push_back(std::make_pair(Longest.value, -1));
            i = i + Longest.value.size() - 1;
        }
        else if (Tokens_found.size() == 1)
        {
            Tokens.push_back(*(Tokens_found.begin()));
            pif.push_back(std::make_pair((*(Tokens_found.begin())).value, -1));
            i = i + (*(Tokens_found.begin())).value.size() - 1;
        }
        else if (!isWhiteSpace(code[i]) && !isOperatorOrSeparator(code[i]))
        {
            std::string Tok_value;
            bool Has_letters = false;
            bool Starts_with_quotes = (code[i] == '\"');
            bool Ends_with_quotes = false;

            if (Starts_with_quotes)
            {
                Tok_value = code[i++];
                while (code[i] != '\"' && code[i] != '\n' && i < code.size())
                {
                    Tok_value += code[i];
                    i++;
                }
            }
            else
            {
                while (!isWhiteSpace(code[i]) && !isOperatorOrSeparator(code[i]) && i < code.size())
                {
                    Tok_value += code[i];
                    if (!isdigit(code[i]))
                    {
                        Has_letters = true;
                    }
                    i++;
                }
                i--;
            }
            Ends_with_quotes = (code[i] == '\"');
            Tok_value += (Starts_with_quotes && Ends_with_quotes ? "\"" : "");

            if ((Starts_with_quotes && Ends_with_quotes) || (!Has_letters && !Starts_with_quotes))
            {
                Token To_add{CONSTANT, Tok_value, Current_line};
                Tokens.push_back(To_add);
                int pos = symbolTable.add(To_add.value);
                pif.push_back(std::make_pair(To_add.value, pos));
            }
            else
            {
                Token To_add{IDENTIFIER, Tok_value, Current_line};
                if (isLexicallyCorrect(To_add))
                {
                    Tokens.push_back(To_add);
                    int pos = symbolTable.add(To_add.value);
                    pif.push_back(std::make_pair(To_add.value, pos));
                }
                else
                {
                    std::cout << "Lexical error: " << To_add.value << " at line " << To_add.line << std::endl;
                    return Tokens;
                }
            }
        }
    }

    std::cout << "Lexically correct" << std::endl;
    return Tokens;
}

bool LexicalAnalyzer::isWhiteSpace(char C)
{
    return C == ' ' || C == '\t' || C == '\n';
}

bool LexicalAnalyzer::isOperatorOrSeparator(char C)
{
    for (auto& Operator : operators)
    {
        for (int i = 0; i < Operator.size(); ++i)
        {
            if (C == Operator[i])
            {
                return true;
            }
        }
    }
    for (auto& Separator : separators)
    {
        for (int i = 0; i < Separator.size(); ++i)
        {
            if (C == Separator[i])
            {
                return true;
            }
        }
    }
    return false;
}

bool LexicalAnalyzer::isLexicallyCorrect(Token Tok)
{
    if (Tok.type == OPERATOR || Tok.type == SEPARATOR || Tok.type == CONSTANT)
    {
        return true;
    }

    if (Tok.type == IDENTIFIER)
    {
        for (int i = 0; i < Tok.value.size(); ++i)
        {
            if (!isalnum(Tok.value[i]))
            {
                return false;
            }
        }
    }
    
    return true;
}

void LexicalAnalyzer::writeTables()
{
    std::ofstream ST_OUT("Outputs/ST.out");
    ST_OUT << symbolTable.toString();
    ST_OUT.close();


    std::ofstream PIF_OUT("Outputs/PIF.out");
    for (auto pair : pif)
    {
        PIF_OUT << pair.first << " " << pair.second << "\n";
    }
    PIF_OUT.close();
}

void LexicalAnalyzer::readTokens(const std::string& Path)
{
    std::ifstream tokens_file(Path);

    std::string value;
    std::string type;

    while (tokens_file >> value)
    {
        tokens_file >> type;

        if (type == OPERATOR)
        {
            operators.push_back(value);
        }
        if (type == SEPARATOR)
        {
            separators.push_back(value);
        }
        if (type == RESERVED_WORD)
        {
            reserved_words.push_back(value);
        }
    }

    tokens_file.close();
}

// void LexicalAnalyzer::analyseLexically()
// {
//     std::list<Token> Tokens = getTokens();
//     bool Found_mistakes = false;

//     for (auto& Tok : Tokens)
//     {
//         if (!isLexicallyCorrect(Tok))
//         {
//             std::cout << "Lexically incorrect: " << Tok.value << " at line " << Tok.line << std::endl;
//             Found_mistakes = true;
//         }
//     }

//     if (!Found_mistakes)
//     {
//         std::cout << "Lexically corect" << std::endl;
//     }
// }