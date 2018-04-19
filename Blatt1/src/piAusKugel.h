//============================================================================
// Name        : piAusKugel.cpp
// Author      : Jasper Karl Lammering
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include <cmath>
using namespace std;

void piAusKugel() {
	double x, y, z;
	int genauigkeit = 1e9;

	mt19937 rng; //erzeugt mersenne twister 19937 generator
	rng.seed(random_device()()); //setzt seed (”startwert”) zufällig
	uniform_real_distribution<> dist (-1 ,1); //erzeugt Verteilung von 0 bis 1

	int n = 0;
	for(int i=0; i<genauigkeit; i++){
		x = dist(rng);
		y = dist(rng);
		z = dist(rng);
		if(pow(x, 2) + pow(y, 2) + pow(z, 2)< 1){
			n++;
		}
	}

	double pi_est = (double)3*2*(double)n/((double)genauigkeit);
	cout.precision(17);
	cout << "Pi ~ " << pi_est << endl; // prints !!!Hello World!!!
}
