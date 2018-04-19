//============================================================================
// Name        : uneigentlichesIntegral.h
// Author      : Jasper Karl Lammering
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================
// berechnet das uneigentliche Integral der Funktion func

#include <iostream>
#include <cmath>
using namespace std;

double func(double x){
	return 1/(sqrt(M_PI)) * 1/(pow(cos(x), 2)) * exp(-pow(tan(x), 2));
}

void uneigentlichesIntegral() {
	double genauigkeit = 1e9; //N
	double a = - M_PI/2; //untere Grenze
	double b[3] = {atan(-1), atan(1.1631), M_PI/2}; //drei verschiedene Werte für die obere Grenze

  mt19937 rng; //erzeugt mersenne twister 19937 generator
	rng.seed(random_device()()); //setzt seed (”startwert”) zufällig

  for(int j=0; j<=2; j++){
  uniform_real_distribution<> dist (a ,b[j]); //erzeugt Verteilung von a bis b

  double integral = 0;
  double h = (b[j]-a)/genauigkeit;
	for(int i = 0; i < genauigkeit; i++){
		integral += h * func(dist(rng));
	}
  cout.precision(4);
  cout << "Integral von " << a << " bis "<< b[j]<<  " = " << integral << endl; // prints !!!Fuck me in the ass!!!
}
}
