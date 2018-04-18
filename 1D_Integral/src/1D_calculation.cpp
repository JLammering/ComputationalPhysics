//============================================================================
// Name        : 1D_calculation.cpp
// Author      : Jasper Karl Lammering
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include <cmath>
using namespace std;

double func(double x){
	double y = pow(x, 2);
	return y;
}

int main() {
	double a, b;
	double genauigkeit = 10000;
	double integral = 0;
	a = 0;
	b = 2;

	for(int i = 0; i < genauigkeit; i++){
		integral += (b - a)/genauigkeit * func((double)i*(b-a)/genauigkeit + a);
	}

	cout.precision(17);
	cout << "Timo ist ein Hurensohn = " << integral << endl; // prints !!!Hello World!!!
	return 0;
}
