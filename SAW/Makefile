
CC=g++
OPT= -std=c++11 -o3
Files= saw.cpp plot.pdf

build: ${Files}
	${CC} ${OPT} ${Files} -o Nr1.out
	./Nr1.out>>Nr1.txt
	python plotRN.py