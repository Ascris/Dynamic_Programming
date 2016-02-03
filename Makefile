KS: main.o
	g++ -o KS main.o

main.o: main.c
	g++ -c main.c -Wall -std=c++11

clean:
	rm -rf *.o
