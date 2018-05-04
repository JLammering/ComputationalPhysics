CC=g++
OPT= -std=c++11 -o3

build: aufgabe1/aufgabe1.cpp aufgabe1/plot.py aufgabe2/aufgabe2_a.cpp aufgabe2/aufgabe2_b.cpp aufgabe2/b2.py aufgabe2/b2b.py
	mkdir -p build
	${CC} ${OPT} aufgabe1/aufgabe1.cpp -o blatt2.out
	./blatt2.out #>blatt2_ausgabe.txt
	${CC} ${OPT} aufgabe2/aufgabe2_a.cpp -o blatt2_2a.out
	./blatt2_2a.out
	${CC} ${OPT} aufgabe2/aufgabe2_b.cpp -o blatt2_2b.out
	./blatt2_2b.out
	python aufgabe1/plot.py
	python aufgabe2/b2.py
	python aufgabe2/b2b.py
