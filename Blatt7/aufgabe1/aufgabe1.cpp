//============================================================================
// Name        : aufgabe1.cpp
// Author      :
// Version     :
// Copyright   : Henning Ptaszyk, Jasper Lammering
// Description : Harmonischer Oszillator
//============================================================================

#include <iostream>
#include <Eigen/Eigenvalues>
#include <string>
#include <fstream>
using namespace std;
using namespace Eigen;

VectorXd kraftfeldHO(VectorXd r){
	return -r;
}

VectorXd fvector(VectorXd y, function<VectorXd(VectorXd)> kraftfeld){
	VectorXd f_rueck(y.rows());
	f_rueck << y.tail(y.rows()/2), kraftfeld(y.head(y.rows()/2));
	return f_rueck;
}

MatrixXd euler(VectorXd rAnfang, VectorXd vAnfang, double T, int N, function<VectorXd(VectorXd)> kraftfeld)
{
	//erste Spalte
	int dimanfang = rAnfang.rows();
	VectorXd y_0(dimanfang*2);//
	y_0 << rAnfang, vAnfang;
	int dim = dimanfang*2;
	MatrixXd Y_Matrix = MatrixXd::Zero(dim, N+1);
	Y_Matrix.col(0) = y_0;
	double h = T / N;
	//andere Spalten
	for(size_t i = 1 ; i <= N ; i++ )
	{
		Y_Matrix.col(i) = h*fvector(Y_Matrix.col(i-1), kraftfeld);
		Y_Matrix.col(i) += Y_Matrix.col(i-1);
	}
	return Y_Matrix;
}

MatrixXd rungekutta4(VectorXd rAnfang, VectorXd vAnfang, double T, int N, function<VectorXd(VectorXd)> kraftfeld){
	//erste Spalte
	int dimanfang = rAnfang.rows();
	VectorXd y_0(dimanfang*2);//
	y_0 << rAnfang, vAnfang;
	int dim = dimanfang*2;
	MatrixXd Y_Matrix = MatrixXd::Zero(dim, N+1);
	Y_Matrix.col(0) = y_0;
	double h = T / N;
	//andere Spalten
	VectorXd k_1(dim);
	VectorXd k_2(dim);
	VectorXd k_3(dim);
	VectorXd k_4(dim);
	for(size_t i = 1 ; i <= N ; i++ )
	{
		k_1 = h*fvector(Y_Matrix.col(i-1), kraftfeld);
		k_2 = h*fvector(Y_Matrix.col(i-1) + 0.5*k_1, kraftfeld);
		k_3 = h*fvector(Y_Matrix.col(i-1) + 0.5*k_2, kraftfeld);
		k_4 = h*fvector(Y_Matrix.col(i-1) + 0.5*k_3, kraftfeld);
		Y_Matrix.col(i) = 1.0/6.0 * (k_1 + 2*k_2 + 2*k_3 + k_4);
		Y_Matrix.col(i) += Y_Matrix.col(i-1);
	}
	return Y_Matrix;
}

MatrixXd rungekutta2(VectorXd rAnfang, VectorXd vAnfang, double T, int N, function<VectorXd(VectorXd)> kraftfeld){
	//erste Spalte
	int dimanfang = rAnfang.rows();
	VectorXd y_0(dimanfang*2);//
	y_0 << rAnfang, vAnfang;
	int dim = dimanfang*2;
	MatrixXd Y_Matrix = MatrixXd::Zero(dim, N+1);
	Y_Matrix.col(0) = y_0;
	double h = T / N;
	//andere Spalten
	VectorXd k_1(dim);
	for(size_t i = 1 ; i <= N ; i++ )
	{
		k_1 = h*fvector(Y_Matrix.col(i-1), kraftfeld);
		Y_Matrix.col(i) = h*fvector(Y_Matrix.col(i-1) + 0.5*k_1, kraftfeld);
		Y_Matrix.col(i) += Y_Matrix.col(i-1);
	}
	return Y_Matrix;
}

void absaven(VectorXd V){
	int dim = V.rows();
	ofstream myfile;
	myfile.open("build/auslenkSchritt"+to_string(dim)+".txt");
		for (size_t j = 0; j < dim; j++) {//durch auslenkungen
			myfile << V(j)<< "\n";
		}
	myfile.close();
}

int main() {
	VectorXd rAnfang(3);
	rAnfang << 1, 1, 1;
	VectorXd vAnfang(3);
	vAnfang << 0, 0, 0;
	int N = 30;
	int T = 1;
	MatrixXd E(rAnfang.rows()*2, N+1);
	E = euler(rAnfang, vAnfang, T, N, kraftfeldHO);
	MatrixXd R2(rAnfang.rows()*2, N+1);
	R2 = rungekutta2(rAnfang, vAnfang, T, N, kraftfeldHO);
	MatrixXd R4(rAnfang.rows()*2, N+1);
	R4 = rungekutta4(rAnfang, vAnfang, T, N, kraftfeldHO);
	cout << E << endl<<endl;
	cout << R2 << endl<<endl;
	cout << R4 << endl;

	//a
	int schrittanfang = 5;
	int schrittende = 50;
	T = 5;


	for (size_t i = schrittanfang; i < schrittende; i++) {//Schritte
		VectorXd V(i);
		MatrixXd R4a(rAnfang.rows()*2, i+1);
		R4a = rungekutta4(rAnfang, vAnfang, T, i, kraftfeldHO);
		absaven(R4a.row(0).transpose());//x-Koordinate abspeichern
	}




	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
