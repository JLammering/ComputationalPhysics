//============================================================================
// Name        : uneigentlichesIntegral.h
// Author      : Jasper Karl Lammering, Timo Gräßer, Henning Ptaszyk
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================
// berechnet das uneigentliche Integral der Funktion func

#include <iostream>
#include <cmath>
using namespace std;



// zu integrierende funktion
double func(double x){
	return 1/(sqrt(M_PI)) * 1/(pow(cos(x), 2)) * exp(-pow(tan(x), 2));
}

double simpson_int(double (*function)(double), double lowlim, double uplim, int subints ){
  double h = (uplim - lowlim) / subints; // vorfaktor fuer summierte simspon integration
  double integ = 0.0; // variable zum aufsummieren des integralwerts
  for (int m = 0; m < subints; m++){ // iteriere ueber teilintervalle
    integ += function(lowlim + h * m) + 4 * function(((lowlim + h * m) + h / 2.0)) + function(lowlim + h * m);
  }
  return(h * integ / 6.0); // gib mit summierter simpson-regel berechnetes integral zurueck
}


void uneigentlichesIntegral() {
	double genauigkeit = 1e9; //N
	double a = - M_PI/2; //untere Grenze
	double b[3] = {atan(-1), atan(1.1631), M_PI/2}; //drei verschiedene Werte für die obere Grenze

  mt19937 rng; //erzeugt mersenne twister 19937 generator
	rng.seed(random_device()()); //setzt seed (”startwert”) zufällig

  for(int j=0; j<=2; j++){
  uniform_real_distribution<> dist (a ,b[j]); //erzeugt Verteilung von a bis b

  double integral = 0; // variable fuer integralwert
  double h = (b[j]-a)/genauigkeit; // vorfaktor aus mc-integration
	// berechne integralwert
	for(int i = 0; i < genauigkeit; i++){
		integral += h * func(dist(rng));
	}
	// num integration mit summierter simpson integration
	double res_simpson = simpson_int(&func,  a, b[j], 1e6);

  cout.precision(7);
  cout << "Integral von " << a << " bis "<< b[j]<<  " = " << integral << endl; // prints die 3 Ergebnisse
	cout << "Integral mit Simpsonregel von " << a << " bis "<< b[j]<<  " = " << res_simpson << endl << endl;
}
}
