build:
	g++ -c src/SymbolTable.cpp -o Build/SymbolTable.o
	g++ -c src/Token.cpp -o Build/Token.o
	g++ -c src/LexicalAnalyzer.cpp -o Build/LexicalAnalyzer.o
	g++ -c src/Grammar.cpp -o Build/Grammar.o
	g++ -c src/ProductionRule.cpp -o Build/ProductionRule.o
	g++ -c src/LL_ParsingTable.cpp -o Build/LL_ParsingTable.o
	g++ -c src/main.cpp -o Build/main.o
	g++ -o lab5 Build/SymbolTable.o Build/Token.o Build/LexicalAnalyzer.o Build/Grammar.o Build/ProductionRule.o Build/LL_ParsingTable.o Build/main.o

clean:
	rm Build/*
	rm lab5
