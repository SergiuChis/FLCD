build:
	g++ -c SymbolTable.cpp -o Build/SymbolTable.o
	g++ -c main.cpp -o Build/main.o
	g++ -o lab2 Build/SymbolTable.o Build/main.o

clean:
	rm Build/*
	rm lab2
