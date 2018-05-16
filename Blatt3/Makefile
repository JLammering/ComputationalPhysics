CC=g++
OPT= -std=c++11 -o3

all: build/main.pdf

build/magnetisierung.pdf: aufgabe1/aufgabe1.cpp aufgabe1/plot.py
	${CC} ${OPT} aufgabe1/aufgabe1.cpp -o aufgabe1.out
	./aufgabe1.out #>blatt2_ausgabe.txt
	python aufgabe1/plot.py
     # ${CC} ${OPT} aufgabe2/aufgabe2.cpp -o aufgabe2.out
     # ./aufgabe2.out
     # python aufgabe2/plot.py

build/plots/kbTgleicheins.pdf: aufgabe2/aufgabe2.cpp aufgabe2/plot.py
	mkdir -p build/plots
	${CC} ${OPT} aufgabe2/aufgabe2.cpp -o aufgabe2.out
	./aufgabe2.out
	python aufgabe2/plot.py

build/main.pdf: build/magnetisierung.pdf build/plots/kbTgleicheins.pdf


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
