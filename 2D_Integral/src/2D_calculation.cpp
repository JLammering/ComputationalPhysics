//============================================================================
// Name        : 2D_calculation.cpp
// Author      : Jasper Karl Lammering
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include <cmath>
using namespace std;

double func(double x, double y){
	double z = pow(x, 2) + pow(y, 2);
	return z;
}

double f_schlange(double x, double y){
	int R = 1;
	if(pow(x, 2) + pow(y, 2) < pow(R, 2)){
		return func(x, y);
	}else{
		return 0;
	}
}

int main() {
	double a_x, a_y, b_x, b_y;
	double genauigkeit = 10000;
	double integral = 0;
	a_x = 0;
	b_x = 2;
	a_y = 0;
	b_y = 2;
	double V_schlange = (b_x - a_x)*(b_y - a_y);
	for(int i = 0; i < genauigkeit; i++){
		double x = a_x + (b_x - a_x)*drand48();
		double y = a_y + (b_y - a_y)*drand48();
		integral += V_schlange/genauigkeit * f_schlange(x, y);
	}

	cout.precision(17);
	cout << "Timo ist ein Hurensohn = " << integral << endl; // prints !!!Hello World!!!
	return 0;
}
