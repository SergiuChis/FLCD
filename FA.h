#ifndef FA_H
#define FA_H

#include "Transition.h"

class FA
{
public:
    std::list<std::string> states;
    std::list<std::string> alphabet;
    std::string initialState;
    std::list<std::string> finalStates;
    std::list<Transition> transitions;

    FA(std::string InputFilePath);

    void readContents(std::string InputFilePath);
    bool isDFA();
    bool isSequenceAccepted(std::list<std::string> Sequence);
    std::string statesToString();
    std::string alphabetToString();
    std::string finalStatesToString();
    std::string transitionsToString();
    std::string allToString();
};

#endif