CC=g++
OPT= -std=c++11 -o3

all: build/main.pdf

build/magnetisierung.pdf: aufgabe1/aufgabe1.cpp aufgabe1/plot.py
	mkdir -p build
	${CC} ${OPT} aufgabe1/aufgabe1.cpp -o blatt3.out
	./blatt3.out #>blatt2_ausgabe.txt
	python aufgabe1/plot.py


build/main.pdf: build/magnetisierung.pdf


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
