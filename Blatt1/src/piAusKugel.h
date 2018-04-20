//============================================================================
// Name        : piAusKugel.cpp
// Author      : Jasper Karl Lammering, Timo Gräßer, Henning Ptaszyk
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include <cmath>
using namespace std;

void piAusKugel() {
	double x, y, z; // koordinaten
	int genauigkeit = 1e7;
	double rel_err;

	mt19937 rng; //erzeugt mersenne twister 19937 generator
	rng.seed(random_device()()); //setzt seed (”startwert”) zufällig
	uniform_real_distribution<> dist (-1 ,1); //erzeugt Verteilung von 0 bis 1

	int n = 0; // zaehler fuer "hits" innerhalb der kugel
	for(int i=0; i<genauigkeit; i++){
		// weise koordinaten Zufallszahlen zu
		x = dist(rng);
		y = dist(rng);
		z = dist(rng);
		if(pow(x, 2) + pow(y, 2) + pow(z, 2)< 1){
			n++; // zaehlen
		}
	}

	double pi_est = (double)3*2*(double)n/((double)genauigkeit); // pi naeherungsweise berechnen
	rel_err = 100.0 * (M_PI - pi_est) / (M_PI);
	cout.precision(17);
	cout << "Pi ~ " << pi_est << endl; // prints
	cout << "Relative Abweichung in Prozent: " << rel_err << endl;
}
