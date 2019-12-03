Research: main.o
	g++ -o Research main.o
main.o: main.cpp edgeCover.h
	g++ -c main.cpp -g -std=c++11 -Wall
clean:
	rm -f Research main.o
rebuild:
	make clean
	make
