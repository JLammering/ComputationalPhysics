CC=g++
OPT= -std=c++11 -o3 -I/usr/include/eigen3

all: build/main.pdf

build/paras.txt: aufgabe1/aufgabe1.cpp
	${CC} ${OPT} aufgabe1/aufgabe1.cpp -o aufgabe1.out
	./aufgabe1.out

build/md_sim.mp4.pdf: aufgabe1/plot.py
	mkdir -p build/plots
	python aufgabe1/plot.py




build/main.pdf: build/paras.txt build/md_sim.mp4.pdf


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
