build:
	g++ -c src/SymbolTable.cpp -o Build/SymbolTable.o
	g++ -c src/Token.cpp -o Build/Token.o
	g++ -c src/LexicalAnalyzer.cpp -o Build/LexicalAnalyzer.o
	g++ -c src/main.cpp -o Build/main.o
	g++ -o lexer Build/SymbolTable.o Build/Token.o Build/LexicalAnalyzer.o Build/main.o

clean:
	rm Build/*
	rm lexer
