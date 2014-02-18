CC = g++ -Wall -pedantic -O2

all: Analyze 

Analyze: Play.o cputime.o main.o List.o HashTable.o 
	$(CC) -o Analyze Play.o List.o HashTable.o cputime.o main.o  

cputime.o: cputime.c
	$(CC) -c cputime.c

HashTable.o: HashTable.cpp
	$(CC) -c HashTable.cpp

List.o:	List.cpp
	$(CC) -c List.cpp

Play.o: Play.cpp
	$(CC) -c Play.cpp

main.o: main.cpp
	$(CC) -c main.cpp

clean:
	rm -rf *.o *~ *.x
	rm -rf Analyze
