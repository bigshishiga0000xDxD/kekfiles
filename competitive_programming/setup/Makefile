all: main

main.o: main.cpp
	g++ -g -c main.cpp -o main.o -DLOCAL -Wall -Wextra -std=c++17 -O2

main: main.o
	g++ main.o -o main.out
