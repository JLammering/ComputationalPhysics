//============================================================================
// Name        : compuational_physics_b2_2.cpp
// Author      : henning
// Version     :
// Copyright   : Your copyright notice
// Description : Blatt2 in C++, Ansi-style
//============================================================================


#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
using namespace std;


int main() {
	// fuer zufallszahlen gleichverteilt auf 0,1
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_real_distribution<> dist1(0,1);
	std::uniform_real_distribution<> dist2(0,1);

	int number = 1e6; // anzahl zu generierender zufallszahlen

	double mu  = 3.0; // geforderter mittelwert
	double si  = 2.0; // geforderte  standardabweichung

	ofstream file;
	file.open("build/gauss.txt");

	for(int i = 0; i <= number; i++){
		// ziehe 2 unabhaengige zufallszahlen
		double ran1 = dist1(rng);
		double ran2 = dist2(rng);
		// box muller methode generiert zwei unabhaengige standardnormalverteilte zufallszahlen
		double x = cos(2.0 * M_PI * ran1) * sqrt(-2.0 * log(ran2));
		double y = cos(2.0 * M_PI * ran1) * sqrt(-2.0 * log(ran2)); // wird spaeter nicht verwendet, da nur eine 1D normalverteilung erzeugt werden soll
		// transformiere standardnormalverteilte zufallszahl in verteilung mit gewuenschter standardabweichung "si"  und mittelwert "mu"
		double z = x * si + mu;
		// in .txt schreiben
		file << z << endl;
		}
	file.close();
	return(0);
}
