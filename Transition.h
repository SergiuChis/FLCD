#ifndef TRANSITION_H
#define TRANSITION_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>

class Transition
{
public:
    std::string startState;
    std::string action;
    std::string resultState;

    Transition(std::string StartState, std::string Action, std::string ResultState);

    std::string toString();
};

#endif