//============================================================================
// Name        : aufgabe1.cpp
// Author      : Jasper Lammering, Henning Ptaszyk
// Version     :
// Copyright   :
// Description : MD-Simulation
//============================================================================

#include <iostream>
#include <Eigen/Eigenvalues>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;
using namespace Eigen;

double dist(VectorXd a, VectorXd b){//berechnet abstand zwischen zwei Punkten
	return(sqrt(pow(a(0) - b(0), 2) + pow(a(1) - b(1), 2)));
}

VectorXd kraftfeldLJ(MatrixXd teilchen, int aktueller, double r_C){
	double pot = 0;
	VectorXd kraft(2);
	for (size_t i = 0; i < N; i++) {
		if (i==aktueller) continue;
		double r = dist(teilchen.col(i), teilchen.col(aktueller));
		if (r>r_C) continue;
		VectorXd dir = teilchen.col(aktueller).head(2) - teilchen.col(i).head(2);
		kraft += 48 * dir * (pow(1/r, 14) - 0.5*pow(1/r, 8)); // potential ableitung
	}
	return kraft;
}


VectorXd fvector(VectorXd y, function<VectorXd(VectorXd)> kraftfeld){//allgemeiner fvector
	VectorXd f_rueck(y.rows());
	f_rueck << y.tail(2), kraftfeld(y);//oben die unteren zwei Spalten vom mitgegebenen Vektor. unten die oberen zwei
	return f_rueck;
}

VectorXd verlet(MatrixXd teilchen, int aktuell, double h, int L, function<VectorXd(VectorXd)> kraftfeld){
	double r_C = L/2.0;
	VectorXd r = teilchen.col(aktuell).head(2);
	VectorXd v = teilchen.col(aktuell).segment(3, 2);
	VectorXd a = teilchen.col(aktuell).tail(2);
	VectorXd r_neu = r + h*v + 0.5*a*pow(h, 2);
	VectorXd a_neu = kraftfeld(teilchen, aktuell, r_C);
	VectorXd v_neu = v + 0.5(a_neu + a)*h;
	VectorXd neues << r_neu, v_neu, a_neu;
	return Y_Matrix;
}

int main() {
	const int N = 16;

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	return 0;
}
