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



void measure(ofstream &myfile, MatrixXd teilchen, double zeit){
	int N = teilchen.cols();
	myfile << zeit << " ";

	// schwerpunktsgeschindigkeit

	MatrixXd geschwindigkeiten(1, N);
	geschwindigkeiten = teilchen.block(2, 0, 1, N).array().square() + teilchen.block(3, 0, 1, N).array().square();
	myfile << sqrt(geschwindigkeiten.sum())/(double)N << " ";

	// kinetische energie
	// myfile << 0.5 * teilchen.block(2, 0, 1, N).colwise().square() + teilchen.block(3, 0, 1, N).colwise().square() << " ";

	// potentielle energie
	// myfile << 0.5 *

	// temperatur

	myfile << endl;
}

double LJAbleitung(double r){
	double kraft = - 48 * (pow(1 / r, 13) - 0.5 * pow(1 / r, 7)); // potential ableitung
	return kraft;
}

void absaven(int schritt, MatrixXd teilchen){
	int N = teilchen.cols();
	ofstream myfile;
	myfile.open("build/" + to_string(schritt) + ".txt");
	for (size_t row = 0; row < 2; row++) {
	for (size_t cols = 0; cols < N; cols++) {
		myfile << teilchen(row, cols) << " ";
		}
		myfile << "\n";
	}
	//myfile << teilchen.block(0, 0, 2, N);
myfile.close();
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
	//cout << nMatrix << endl;
 // Kraftberechung
	 for(int i = 0; i < N; i++)
   for(int j = i + 1; j < N; j++){
		//cout << "r_i = \n"<<teilchen.col(i).head(2) << endl;
		//cout << "r_j = \n"<<teilchen.col(j).head(2) << endl;
		VectorXd r_ij = teilchen.col(j).head(2) - teilchen.col(i).head(2);
		//cout << "r_ij = \n"<< r_ij << endl;

  	MatrixXd newNMatrix = nMatrix.colwise() + r_ij;
		//cout << "Matrix: \n" << newNMatrix <<endl;
 		MatrixXd::Index minRow, minCol;
	 	double r_ij_abs = newNMatrix.colwise().norm().minCoeff(&minRow, &minCol);
	 	r_ij = newNMatrix.col(minCol);
		//cout << "r_ij minimal = \n"<< r_ij << endl;
		//cout << "r_ij_abs minimal = \n"<< r_ij_abs << endl;
		if(r_ij_abs < r_c){
			//cout << "liegt im Bereich\n" <<endl;
			F.col(i) += r_ij * LJAbleitung(r_ij_abs) / r_ij_abs; //
			F.col(j) -= r_ij * LJAbleitung(r_ij_abs) / r_ij_abs; // Newton drei
		}
	}
	return F;
}


MatrixXd integrate(MatrixXd teilchen, double h, int L){
	int N = teilchen.cols();
	teilchen.block(0, 0, 2, N) = teilchen.block(0, 0, 2, N)  + h*teilchen.block(2, 0, 2, N) + 0.5*teilchen.block(4, 0, 2, N)*pow(h, 2);// neue Positionen
	// cout<<" Teilcheposition vorher: \n"  <<teilchen.block(0, 0, 2, 5) << endl;
	MatrixXd Hilfematrix = teilchen.block(0, 0, 2, N);
	Hilfematrix =  L * (teilchen.block(0, 0, 2, N).array()/L).floor();
	teilchen.block(0, 0, 2, N) = teilchen.block(0, 0, 2, N) - Hilfematrix ;
	// cout<<"Teilchenposition nachher \n" <<teilchen.block(0, 0, 2, 5) << endl;
 	// teilchen.block(0, 0, 2, N) = teilchen.block(0, 0, 2, N) + (teilchen.block(0, 0, 2, N)<0.0)*(double)L;

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
	for (size_t i = 0; i < N; i++) {
		teilchen.col(i).segment(2, 2) <<  distribution(rng), distribution(rng);
		teilchen.col(i).tail(2) << 0,0;
	}
	teilchen.block(2, 0, 2, N).colwise() -= teilchen.block(2, 0, 2, N).rowwise().sum() / (double)N;

	//a
	teilchen.block(4, 0, 2, N) = forces(teilchen, L);
return teilchen;
}

void MD_Simulation(int L, int N, double T, double tequi, double tmax, double h, int speicher){
	auto teilchen = init(N, L, T);
	double t = 0;
	int schritt = 0;

	ofstream myfile;
	myfile.open("build/measurements.txt");

	do {
		teilchen = integrate(teilchen, h, L);
		schritt ++;
		if (schritt %speicher ==0) {
			cout << schritt << "abgespeichert" << endl;
			absaven(schritt, teilchen);
		}
		//measure(myfile, teilchen, t);
		t += h;
	}while (t < tequi);
	myfile.close();

	do {
		  teilchen = integrate(teilchen, h, L);
			//absaven(schritt++, teilchen);
			t += h;
		}while (t < tmax);
}



int main() {
	const int N = 16; // immer quadratzahl
	int L = 8; // immer gerade waehlen!
	int T = 1;
	double tequi = 1e-1;
	double tmax = tequi;
	double h = 1e-6;
	int speicher = 1000;
	ofstream myfile;
	myfile.open("build/paras.txt");
	//myfile << "#schritte\n";
	myfile << tmax/h << " "<<speicher<< endl;
	myfile.close();
	//MatrixXd teilchen = init(N, L, 1);
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	MD_Simulation(L, N, T, tequi, tmax, h, speicher);

	return 0;
}
