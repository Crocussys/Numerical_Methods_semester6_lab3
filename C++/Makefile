all: main.o matrix.o
	g++ main.o matrix.o -o run

main.o: main.cpp
	g++ -g -c main.cpp

matrix.o: matrix.cpp
	g++ -g -c matrix.cpp

clean:
	rm -rf *.o