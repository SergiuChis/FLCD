#include "SymbolTable.h"

int main()
{
    {
        SymbolTable ST{80};
        ST.add("asdf");
        ST.add("fdsa");
        ST.add("24");
        ST.add("3");
        std::cout << ST.toString() << std::endl;
    }

    return 0;
}