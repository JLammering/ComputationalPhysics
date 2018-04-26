CC=g++
OPT= -std=c++11 -o3

build: aufgabe1/aufgabe1.cpp aufgabe1/plot.py
	mkdir -p build
	${CC} ${OPT} aufgabe1/aufgabe1.cpp -o blatt2.out
	./blatt2.out #>blatt2_ausgabe.txt
	python aufgabe1/plot.py
