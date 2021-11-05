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

    Transition(std::string StartState, std::string Action, std::string ResultState)
    {
        startState = StartState;
        action = Action;
        resultState = ResultState;
    }

    std::string toString()
    {
        return "(" + startState + ", " + action + ") = " + resultState;
    }
};


class FA
{
public:
    std::list<std::string> states;
    std::list<std::string> alphabet;
    std::string initialState;
    std::list<std::string> finalStates;
    std::list<Transition> transitions;

    FA(std::string InputFilePath)
    {
        readContents(InputFilePath);
    }

    void readContents(std::string InputFilePath)
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

    bool isDFA()
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

    std::string statesToString()
    {
        std::string Result;

        for (auto& state : states)
        {
            Result += state + " ";
        }
        Result.pop_back();

        return Result;
    }

    std::string alphabetToString()
    {
        std::string Result;

        for (auto& action : alphabet)
        {
            Result += action + " ";
        }
        Result.pop_back();

        return Result;
    }

    std::string finalStatesToString()
    {
        std::string Result;

        for (auto& FinalState : finalStates)
        {
            Result += FinalState + " ";
        }
        Result.pop_back();

        return Result;
    }

    std::string transitionsToString()
    {
        std::string Result;

        for (auto& transition : transitions)
        {
            Result += transition.toString() + "\n";
        }
        Result.pop_back();

        return Result;
    }

    std::string allToString()
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
};


class MenuFA
{
public:
    FA* fa;

    MenuFA(FA* Fa)
    {
        fa = Fa;
    }

    void ui()
    {
        while (true)
        {
            printMenu();

            int Input;
            std::cin >> Input;

            if (Input == 1)
            {
                std::cout << fa->statesToString() << std::endl;
            }

            else if (Input == 2)
            {
                std::cout << fa->alphabetToString() << std::endl;
            }

            else if (Input == 3)
            {
                std::cout << fa->initialState << std::endl;
            }

            else if (Input == 4)
            {
                std::cout << fa->finalStatesToString() << std::endl;
            }

            else if (Input == 5)
            {
                std::cout << fa->transitionsToString() << std::endl;
            }

            else if (Input == 6)
            {
                std::cout << fa->allToString() << std::endl;
            }

            else if (Input == 0)
            {
                break;
            }

            else
            {
                std::cout << "Wrong input" << std::endl;
            }
        }
    }
    
    void printMenu()
    {
        std::cout << "1. Display the states" << std::endl;
        std::cout << "2. Display the alphabet" << std::endl;
        std::cout << "3. Display the initial state" << std::endl;
        std::cout << "4. Display the final states" << std::endl;
        std::cout << "5. Display the transitions" << std::endl;
        std::cout << "6. Display all" << std::endl;
        std::cout << "0. Exit" << std::endl;
    }
};


int main()
{
    FA fa{"FA.in"};
    std::cout << (fa.isDFA() ? "it is dfa" : "NOOOO") << std::endl;

    MenuFA menu{&fa};
    menu.ui();

    return 0;
}