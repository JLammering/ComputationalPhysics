all: build/Aufgabe2_b.png
	echo Done A2

build/Aufgabe2_b.png: build/A2b
	python A2_plotting.py

build/A2b: A2.o
	./A2.o

A2.o: build A2.cpp
	g++ -std=c++11 -O3 A2.cpp -o A2.o

build:
	mkdir build
