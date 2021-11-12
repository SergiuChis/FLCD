#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "MenuFA.h"


int main()
{
    FA fa{"FA.in"};

    MenuFA menu{&fa};
    menu.ui();

    return 0;
}