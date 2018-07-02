CC=g++
OPT= -std=c++11 -O3 -I/usr/include/eigen3

all: build/main.pdf

build/plot.pdf: aufgabe1/aufgabe1.cpp aufgabe1/plot.py
	mkdir -p build/plots
	${CC} ${OPT} aufgabe1/aufgabe1.cpp -o aufgabe1.out
	./aufgabe1.out
	python aufgabe1/plot.py

build/main.pdf: build/plot.pdf


build/main.pdf: FORCE | build
	latexmk \
	  --lualatex \
	  --output-directory=build \
	  --interaction=nonstopmode \
	  --halt-on-error \
	main.tex

build:
	mkdir -p build

clean:
	rm -rf build

FORCE:

.PHONY: all clean
