#include "FA.h"

FA::FA(std::string InputFilePath)
{
    readContents(InputFilePath);
}

void FA::readContents(std::string InputFilePath)
{
    std::ifstream FAInput(InputFilePath);
    std::string CurrentElement;

    while ((FAInput >> CurrentElement) && CurrentElement != "Alphabet")
    {
        if (CurrentElement != "States")
        {
            states.push_back(CurrentElement);
        }
    }

    while ((FAInput >> CurrentElement) && CurrentElement != "InitialState")
    {
        if (CurrentElement != "Alphabet")
        {
            alphabet.push_back(CurrentElement);
        }
    }

    while ((FAInput >> CurrentElement) && CurrentElement != "FinalStates")
    {
        if (CurrentElement != "InitialState")
        {
            initialState = CurrentElement;
        }
    }

    while ((FAInput >> CurrentElement) && CurrentElement != "Transitions")
    {
        if (CurrentElement != "FinalStates")
        {
            finalStates.push_back(CurrentElement);
        }
    }

    while (FAInput >> CurrentElement)
    {
        std::string StartState;
        std::string Action;
        std::string ResultState;

        StartState = CurrentElement.substr(1, CurrentElement.size() - 2);

        FAInput >> Action;
        Action.pop_back();

        FAInput >> CurrentElement;

        FAInput >> ResultState;

        transitions.push_back(Transition{StartState, Action, ResultState});
    }

    FAInput.close();
}

bool FA::isDFA()
{
    for (auto& transition1 : transitions)
    {
        for (auto& transition2 : transitions)
        {
            if (transition1.startState == transition2.startState &&
                transition1.action == transition2.action &&
                transition1.resultState != transition2.resultState)
                return false;
        }
    }

    return true;
}

bool FA::isSequenceAccepted(std::list<std::string> Sequence)
{
    if (!isDFA())
    {
        return false;
    }
    
    std::string CurrentState = initialState;
    while (!Sequence.empty())
    {
        std::string Action = *Sequence.begin();
        std::cout << Action << std::endl;
        bool Found = false;

        for (auto& tr : transitions)
        {
            if (tr.startState == CurrentState && tr.action == Action)
            {
                CurrentState = tr.resultState;
                Found = true;
            }
        }

        if (!Found)
        {
            return false;
        }

        Sequence.pop_front();
    }

    for (auto& FinalState : finalStates)
    {
        if (CurrentState == FinalState)
        {
            return true;
        }
    }

    return false;
}

std::string FA::statesToString()
{
    std::string Result;

    for (auto& state : states)
    {
        Result += state + " ";
    }
    Result.pop_back();

    return Result;
}

std::string FA::alphabetToString()
{
    std::string Result;

    for (auto& action : alphabet)
    {
        Result += action + " ";
    }
    Result.pop_back();

    return Result;
}

std::string FA::finalStatesToString()
{
    std::string Result;

    for (auto& FinalState : finalStates)
    {
        Result += FinalState + " ";
    }
    Result.pop_back();

    return Result;
}

std::string FA::transitionsToString()
{
    std::string Result;

    for (auto& transition : transitions)
    {
        Result += transition.toString() + "\n";
    }
    Result.pop_back();

    return Result;
}

std::string FA::allToString()
{
    std::string Result;

    Result += "States\n";
    Result += statesToString();
    Result += "\n";

    Result += "Alphabet\n";
    Result += alphabetToString();
    Result += "\n";

    Result += "InitialState\n";
    Result += initialState;
    Result += "\n";

    Result += "FinalStates\n";
    Result += finalStatesToString();
    Result += "\n";

    Result += "Transitions\n";
    Result += transitionsToString();

    return Result;
}