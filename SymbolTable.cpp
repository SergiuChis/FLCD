#include "SymbolTable.h"

SymbolTable::SymbolTable(int Size)
{
    size = Size;
    hash_table = new std::string[size];

    for (int i = 0; i < size; ++i)
    {
        hash_table[i] = "";
    }
}

int SymbolTable::hash(std::string Element)
{
    int sum_of_ascii_codes = 0;

    for (int i = 0; i < Element.size(); ++i)
    {
        sum_of_ascii_codes += (int)Element[i];
    }

    return sum_of_ascii_codes % size;
}

int SymbolTable::add(std::string Element)
{
    // std::cout << "Adding: " << Element << std::endl;
    int hash_value = hash(Element);
    // std::cout << "Hash value starting: " << hash_value << std::endl;
    int hv_copy = hash_value;
    int cycle = 0;

    while (hash_table[hash_value] != "")
    {
        if (hash_table[hash_value] == Element)
        {
            std::cout << "Already existing" << std::endl;
            return hash_value;
        }
        if (hash_value == hv_copy)
        {
            cycle++;
        }
        if (cycle == 2)
        {
            std::cout << "Table full" << std::endl;
            return hash_value;
        }
        hash_value = (hash_value + 1) % size;
    }

    hash_table[hash_value] = Element;
    // std::cout << "Added at index: " << hash_value << std::endl;
    return hash_value;
}


std::string SymbolTable::toString()
{
    std::string result;
    bool parsed_first = false;

    result += "{";
    for (int i = 0; i < size; ++i)
    {
        if (hash_table[i] != "")
        {
            if (parsed_first == false)
            {
                parsed_first = true;
                result += std::to_string(i) + ": " + hash_table[i];
            }
            else
            {
                result += ", " + std::to_string(i) + ": " + hash_table[i];
            }
        }
    }
    result += "}";

    return result;
}

SymbolTable::~SymbolTable()
{
    delete[] hash_table;
}