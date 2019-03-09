all: generator.o mai.o 

generator.o: generator
	gcc -c generator1.c
	gcc -c generator2.c

mai.o:  main
	g++ main.cpp -c main.o
	g++ cache.cpp -c cache.o


generator: generator1.o generator2.o
	gcc -Wall -g -o generator generator1.o
	gcc -Wall -g -o generator2 generator2.o
main: main.o cache.o
	g++ -o main main.o cache.o 