build:
	g++ -c main.cpp -o Build/main.o
	g++ -c MenuFA.cpp -o Build/MenuFA.o
	g++ -c FA.cpp -o Build/FA.o
	g++ -c Transition.cpp -o Build/Transition.o

	g++ Build/main.o Build/MenuFA.o Build/FA.o Build/Transition.o -o lab4

clean:
	rm lab4
	rm Build/*