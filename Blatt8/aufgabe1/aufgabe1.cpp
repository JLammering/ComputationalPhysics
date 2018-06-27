//============================================================================
// Name        : aufgabe1.cpp
// Author      :
// Version     :
// Copyright   : Henning Ptaszyk, Jasper Lammering
// Description : Doppelpendel
//============================================================================

#include <iostream>
#include <Eigen/Eigenvalues>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;
using namespace Eigen;
//orientiert am Kierfeldskript
VectorXd kraftfeldDP(VectorXd y){
	VectorXd rueckvector(2);
	double lamda = 1;
	double g1 = 9.81;
	double g2 = 9.81;
	double mu = 0.5;
	double theta1 = y(0);
	double theta2 = y(1);
	double theta1punkt = y(2);
	double theta2punkt = y(3);
	double theta1punktpunkt = 1/(1-mu*pow(cos(theta2-theta1), 2))*(mu*g1*sin(theta2)*cos(theta2-theta1)+mu*pow(theta1punkt, 2)*sin(theta2-theta1)*cos(theta2-theta1)-g1*sin(theta1)+ (mu/lamda)*pow(theta2punkt, 2)*sin(theta2-theta1));
	double theta2punktpunkt = 1/(1-mu*pow(cos(theta2-theta1), 2))*(g2*sin(theta1)*cos(theta2-theta1)-mu*pow(theta2punkt, 2)*sin(theta2-theta1)*cos(theta2-theta1)-g2*sin(theta2)- lamda*pow(theta1punkt, 2)*sin(theta2-theta1));
	rueckvector << theta1punktpunkt, theta2punktpunkt;
	return rueckvector;
}


VectorXd fvector(VectorXd y, function<VectorXd(VectorXd)> kraftfeld){//allgemeiner fvector
	VectorXd f_rueck(y.rows());
	f_rueck << y.tail(2), kraftfeld(y);//oben die unteren zwei Spalten vom mitgegebenen Vektor. unten die oberen zwei
	return f_rueck;
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


void absaven(MatrixXd M){//gesamte MAtrix in datei schreiben
	int dim = M.cols();
	cout << "dim="<<dim<<endl;
	ofstream myfile;
	myfile.open("build/auslenk.txt");
	myfile << "#theta1 theta2 v_theta1 v_theta2\n";
		for (size_t j = 0; j < dim; j++) {
			myfile << M(0, j) <<" "<<M(1, j)<<" "<<M(2, j)<<" "<<M(3, j) << "\n";
		}
	myfile.close();
}

int main() {
	VectorXd rAnfang(2);
	rAnfang << 0.1, sqrt(2)*0.1;
	VectorXd vAnfang(2);
	vAnfang << 0, 0;

	//a
	cout << rungekutta4(rAnfang, vAnfang, 3, 3, kraftfeldDP) << endl;
	absaven(rungekutta4(rAnfang, vAnfang, 20, 20, kraftfeldDP));

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
