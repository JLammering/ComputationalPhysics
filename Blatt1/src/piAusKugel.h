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
	double x, y;
	int genauigkeit = 12000000;
	int i;
	int n = 0;
	for(i=0; i<genauigkeit; i++){
		x = drand48();
		y = drand48();
		if(pow(x, 2) + pow(y, 2) < 1){
			n++;
		};
	};

	double pi_est = ((double)4*(double)n/(double)genauigkeit);
	cout.precision(17);
	cout << "Pi ~ " << pi_est << endl; // prints !!!Hello World!!!
}
