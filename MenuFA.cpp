#include "MenuFA.h"

MenuFA::MenuFA(FA* Fa)
{
    fa = Fa;
}

void MenuFA::ui()
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

        else if (Input == 7)
        {
            if (!fa->isDFA())
            {
                std::cout << "Not DFA" << std::endl;
            }
            else
            {
                std::list<std::string> Sequence = {"1", "2"};
                std::cout << "Sequence: ";
                for (auto Input : Sequence)
                {
                    std::cout << Input << " ";
                }
                std::cout << std::endl;
                std::cout << (fa->isSequenceAccepted(Sequence) ? "It is accepted" : "It is not accepted") << std::endl;
            }
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

void MenuFA::printMenu()
{
    std::cout << "1. Display the states" << std::endl;
    std::cout << "2. Display the alphabet" << std::endl;
    std::cout << "3. Display the initial state" << std::endl;
    std::cout << "4. Display the final states" << std::endl;
    std::cout << "5. Display the transitions" << std::endl;
    std::cout << "6. Display all" << std::endl;
    std::cout << "7. Check if sequence is accepted" << std::endl;
    std::cout << "0. Exit" << std::endl;
}