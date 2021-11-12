#ifndef MENUFA_H
#define MENUFA_H

#include "FA.h"

class MenuFA
{
public:
    FA* fa;

    MenuFA(FA* Fa);

    void ui();
    void printMenu();
};

#endif