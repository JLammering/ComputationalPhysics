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
#include <random>
#include <cmath>
using namespace std;
using namespace Eigen;


double LJAbleitung(double r){
	double kraft = - 48 * (pow(1 / r, 13) - 0.5 * pow(1 / r, 7)); // potential ableitung
	return kraft;
}


MatrixXd forces(MatrixXd teilchen, int L){
	unsigned int N = teilchen.cols(); // # teilchen
	auto r_c = L / 2.0; // auto ist cool

	MatrixXd nMatrix(2, 9);
	nMatrix << -1, -1, -1,  0, 0, 0,  1, 1, 1,
						 -1,  0,  1, -1, 0, 1, -1, 0, 1;
  nMatrix *= L;
	MatrixXd F(2, N);
	F = MatrixXd::Zero(2,N);
	cout << nMatrix << endl;
 // Kraftberechung
	 for(int i = 0; i < N; i++)
   for(int j = i + 1; j < N; j++){
		cout << "r_i = \n"<<teilchen.col(i).head(2) << endl;
		cout << "r_j = \n"<<teilchen.col(j).head(2) << endl;
		VectorXd r_ij = teilchen.col(j).head(2) - teilchen.col(i).head(2);
		cout << "r_ij = \n"<< r_ij << endl;

  	MatrixXd newNMatrix = nMatrix.colwise() + r_ij;
		cout << "Matrix: \n" << newNMatrix <<endl;
 		MatrixXd::Index minRow, minCol;
	 	double r_ij_abs = newNMatrix.colwise().norm().minCoeff(&minRow, &minCol);
	 	r_ij = newNMatrix.col(minCol);
		cout << "r_ij minimal = \n"<< r_ij << endl;
		cout << "r_ij_abs minimal = \n"<< r_ij_abs << endl;
		if(r_ij_abs < r_c){
			cout << "liegt im Bereich\n" <<endl;
			F.col(i) += r_ij * LJAbleitung(r_ij_abs) / r_ij_abs; //
			F.col(j) -= r_ij * LJAbleitung(r_ij_abs) / r_ij_abs; // Newton drei
		}
	}
	return F;
}


MatrixXd integrate(MatrixXd teilchen, double h, int L){
	int N = teilchen.cols();
	teilchen.block(0, 0, 2, N)  = teilchen.block(0, 0, 2, N)  + h*teilchen.block(2, 0, 2, N) + 0.5*teilchen.block(4, 0, 2, N)*pow(h, 2);// neue Positionen
	auto a_nplus1 =	forces(teilchen, L);
	teilchen.block(2, 0, 2, N) = teilchen.block(2, 0, 2, N) + 0.5*(teilchen.block(4, 0, 2, N)+a_nplus1);// neue Geschwindigkeiten
	teilchen.block(4, 0, 2, N) = a_nplus1; // neue Beschleunigungen
	return teilchen;
}

MatrixXd init(int N, int L, double T){
	MatrixXd teilchen(6, N);
	//r
	int i=0;
	for(int n = 0; n < 4; n++)
	for(int m = 0; m < 4; m++){
		teilchen.col(i).head(2) <<  1 + 2 * n, 1 + 2 * m;
		teilchen.col(i).head(2) *= L / 8.0;
		i++;
	}

	//v
	mt19937 rng; //erzeugt mersenne twister 19937 generator
	rng.seed(random_device()()); //setzt seed (”startwert”) zufällig std ::
	normal_distribution<double> distribution(0.0, sqrt(T));
	// double scale = sqrt(T * (2 * (N - 1))); // sqrt(kb * T / m ) mit m = 1 , kb = 1
	for (size_t i = 0; i < N; i++) {
		teilchen.col(i).segment(2, 2) <<  distribution(rng), distribution(rng);
		teilchen.col(i).tail(2) << 0,0;
	}
	cout <<"Schwerpunktsgeschwind vorher = "<< teilchen.block(2, 0, 2, N).rowwise().sum()<<endl;
	teilchen.block(2, 0, 2, N).colwise() -= teilchen.block(2, 0, 2, N).rowwise().sum() / (double)N;
	cout <<"Schwerpunktsgeschwind nachher = "<< teilchen.block(2, 0, 2, N).rowwise().sum()<<endl;

	//a
	teilchen.block(4, 0, 2, N) = forces(teilchen, L);
return teilchen;
}

void MD_Simulation(int L, int N, double T, double tequi, double tmax, double h)
	auto teilchen = init(N, L, T);
	t=0;

	do while (t< tequi) {
		integrate(teilchen, h, L);
		t=t+h;
		}
		do while (t<tmax){
		  integrate(teilchen, h, L){

			integrate;
		}

int main() {
	const int N = 16; // immer quadratzahl
	int L = 8; // immer gerade waehlen!
	//MatrixXd teilchen = init(N, L, 1);
	// cout << forces(teilchen, L)<<endl;
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	cout << init(N, L, 1)<<endl;

	return 0;
}