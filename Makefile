build:
	g++ -c main.cpp -o main.o

	g++ main.o -o lab4

clean:
	rm *.o lab4