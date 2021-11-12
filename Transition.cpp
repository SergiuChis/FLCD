#include "Transition.h"

Transition::Transition(std::string StartState, std::string Action, std::string ResultState)
{
    startState = StartState;
    action = Action;
    resultState = ResultState;
}

std::string Transition::toString()
{
    return "(" + startState + ", " + action + ") = " + resultState;
}