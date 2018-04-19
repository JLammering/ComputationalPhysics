
CC=g++
OPT= -std=c++11 -o3
Files= src/blatt1.cpp

build: ${Files}
	${CC} ${OPT} ${Files} -o blatt1.out
	./blatt1.out>blatt1_ausgabe.txt
	python plotRN.py
