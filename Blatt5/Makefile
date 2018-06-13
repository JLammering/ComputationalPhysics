CC=g++
OPT= -std=c++11 -o3

all: build/main.pdf

build/plots/perHand.pdf: aufgabe1/aufgabe1.cpp aufgabe1/plot.py
	mkdir -p build/plots
	${CC} ${OPT} aufgabe1/aufgabe1.cpp -o aufgabe1.out
	./aufgabe1.out
	python3 aufgabe1/plot.py

build/plots/matrix.pdf: aufgabe2/aufgabe2.cpp# aufgabe2/plot.py

	${CC} ${OPT} aufgabe2/aufgabe2.cpp -o aufgabe2.out
	./aufgabe2.out
	#python3 aufgabe1/plot.py

# build/plots/matrix.pdf: aufgabe2/aufgabe2.cpp# aufgabe2/plot.py
#
# 	${CC} ${OPT} aufgabe2/aufgabe2.cpp -o aufgabe2.out
# 	./aufgabe2.out


build/main.pdf: FORCE | build build/plots/perHand.pdf build/plots/matrix.pdf
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
