//============================================================================
// Name        : HelloWorld.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <Eigen/Eigenvalues>
#include <cmath>
#include <complex>
using namespace Eigen;
using namespace std;
typedef Matrix<double, 5, 5> Matrix5d;

void householder(Matrix5d& A){
	int N = A.rows();
	for (size_t n = 1; n <= N-2; n++) {
		MatrixXd v(N-n, 1);
		v = A.col(n-1).tail(N-n);
		//cout << "v="<<v<<endl;
		double k = sqrt(v.squaredNorm()); // die quadratische Summe der letzten  (N-n) Zahlen von der n-ten Spalte// Vorzeichen ??
		k = copysign(abs(k), -A(n+1, n));
		MatrixXd u(N-n, 1);
		u = (v-k*VectorXd::Unit(N-n, 0))/sqrt((v-k*VectorXd::Unit(N-n, 0)).squaredNorm());

		MatrixXd S(N-n, N-n);
		S = MatrixXd::Identity(N-n, N-n) - 2*u*u.transpose();

		MatrixXd P(N, N);
		P << MatrixXd::Identity(n, n), MatrixXd::Zero(n, N-n), MatrixXd::Zero(N-n, n),  S;
		A = P.transpose()*A*P;
	}
	cout <<"A nach Householder:"<<endl<<A<<endl;
}

void jacobiRotation(double epsilon, Matrix5d& A){
	int N = A.rows();

	while (A.squaredNorm() - A.diagonal().squaredNorm() >= epsilon) {//wenn die nicht-diagonalen Quadrate größer sind als die gewählte Schranke
		MatrixXd AohneDiagonale(N, N);//Matrix ohne die Diagonalelemente um das größte nicht diagonale Element zu finden
		AohneDiagonale = A.cwiseAbs();
		AohneDiagonale.diagonal() = VectorXd::Zero(N);
		MatrixXd::Index p, q;
		AohneDiagonale.maxCoeff(&p, &q);//speichert in p und q die Koordinaten des Größten Element
		//Koeffizienten Berechnen
		double theta =  (A(q,q)-A(p,p))/(2*A(p, q));
		double t = copysign(1.0, theta)/(abs(theta) + sqrt(pow(theta, 2) + 1));
		double c = 1/sqrt(1 + pow(t, 2));
		double s = t*c;
		MatrixXd P(N, N);
		P = MatrixXd::Identity(N, N);
		P(p,p) = c;
		P(q, q) = c;
		P(p, q) = s;
		P(q, p) = -s;
		A = P.transpose()*A*P;//transformation
	}
	cout <<"A nach Jacobi:"<<endl<<A<<endl;
}


void matrixDiagonalisierung(Matrix5d& M) {
	cout << M << endl;
	householder(M);
	jacobiRotation(0.00000000000001, M);
}

void absaven(string dateiname, VectorXd& eigenwerte){
	ofstream myfile;
	myfile.open("build/"+dateiname+".txt");
	myfile<<"#Eigenwert\n";
	for (size_t i = 0; i < eigenwerte.rows(); i++) {
		myfile<<eigenwerte(i, 0)<<"\n";
	}
	myfile.close();
}


int main() {
	//a)
	Matrix5d M = Matrix5d::Ones();
	for (size_t i = 0; i < 5; i++) {
		M(i, i) = i+1;
	}
	Matrix5d B = M;
	matrixDiagonalisierung(M);
	VectorXd eigenwertePH(5);
	eigenwertePH = M.diagonal();
	absaven("perHand",eigenwertePH);

	//b)
	EigenSolver<Matrix5d> es(B);
	cout << "Eigenwerte von M sind: "<< es.eigenvalues() << endl;
	complex<double> E;
	VectorXd eigenwerteES(5);
	for(int i = 0; i < B.rows(); i++){
		E = es.eigenvalues()[i];
		eigenwerteES(i) = E.real();
	}
	absaven("mitEigensolver", eigenwerteES);

	return 0;
}
