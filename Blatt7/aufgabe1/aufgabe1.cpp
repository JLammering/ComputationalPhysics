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
//orientiert am Kierfeldskript
VectorXd kraftfeldHO(VectorXd r){
	return -r;
}

VectorXd fvector(VectorXd y, function<VectorXd(VectorXd)> kraftfeld){//allgemeiner fvector
	VectorXd f_rueck(y.rows());
	f_rueck << y.tail(y.rows()/2), kraftfeld(y.head(y.rows()/2));//oben die unteren drei Spalten vom mitgegebenen Vektor. unten die oberen drei
	return f_rueck;
}

MatrixXd euler(VectorXd rAnfang, VectorXd vAnfang, double T, int N, function<VectorXd(VectorXd)> kraftfeld)
{
	//erste Spalte
	int dimanfang = rAnfang.rows();
	VectorXd y_0(dimanfang*2);//
	y_0 << rAnfang, vAnfang;//obere drei Zeilen Ortskoordianten untere drei Geschwindigkeitsvektoren
	int dim = dimanfang*2;
	MatrixXd Y_Matrix = MatrixXd::Zero(dim, N+1);//MAtrix in der jede Spalte ein Zeitschritt ist
	Y_Matrix.col(0) = y_0;
	double h = T / N;
	//andere Spalten
	for(size_t i = 1 ; i <= N ; i++ )
	{
		Y_Matrix.col(i) = h*fvector(Y_Matrix.col(i-1), kraftfeld);//nach definition
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

void absaven(MatrixXd M){//gesamte MAtrix in datei schreiben
	int dim = M.cols();
	cout << "dim="<<dim;
	ofstream myfile;
	myfile.open("build/auslenkSchritt"+to_string(dim)+".txt");
	myfile << "#x y z v_x v_y v_z\n";
		for (size_t j = 0; j < dim; j++) {
			myfile << M(0, j) <<" "<<M(1, j)<<" "<<M(2, j)<<" "<<M(3, j) <<" "<<M(4, j)<<" "<<M(5, j)<< "\n";
		}
	myfile.close();
}

int main() {
	VectorXd rAnfang(3);
	rAnfang << 1, 1, 1;
	VectorXd vAnfang(3);
	vAnfang << 0, 0, 0;

	//a
	int T = 20;


	for (size_t i = 1; i <= 5; i++) {//Schritte
		absaven(rungekutta4(rAnfang, vAnfang, T, i*1000, kraftfeldHO));//Matrix abspeichern
		absaven(rungekutta4(rAnfang, vAnfang, T, i*100, kraftfeldHO));
		absaven(euler(rAnfang, vAnfang, T, i*1000+2, kraftfeldHO));//mit 3 hinten bei den Schritten ist euler... +1 wegen dem anfangsvektor
		absaven(euler(rAnfang, vAnfang, T, i*100+2, kraftfeldHO));
		absaven(rungekutta2(rAnfang, vAnfang, T, i*1000+1, kraftfeldHO));
		absaven(rungekutta2(rAnfang, vAnfang, T, i*100+1, kraftfeldHO));

	}
	//b
	vAnfang << 1, 1, 1;//v neq 0
	absaven(rungekutta4(rAnfang, vAnfang, T, 2999, kraftfeldHO));

	vAnfang << 1, 0, 0;//v nparallel r
	absaven(rungekutta4(rAnfang, vAnfang, T, 2998, kraftfeldHO));

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
