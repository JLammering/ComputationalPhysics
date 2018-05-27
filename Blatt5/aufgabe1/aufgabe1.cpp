//============================================================================
// Name        : HelloWorld.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <Eigen/Eigenvalues>
#include <cmath>
using namespace Eigen;
using namespace std;
typedef Matrix<double, 5, 5> Matrix5d;

void householder(Matrix5d& A){
	int N = A.rows();
	for (size_t n = 1; n <= N-2; n++) {
		cout << "n= "<< n<<endl;
		MatrixXd v(N-n, 1);
		v = A.col(n-1).tail(N-n);
		//cout << "v="<<v<<endl;
		double k = sqrt(v.squaredNorm()); // die quadratische Summe der letzten  (N-n) Zahlen von der n-ten Spalte// Vorzeichen ??
		MatrixXd u(N-n, 1);
		u = (v-k*VectorXd::Unit(N-n, 0))/sqrt((v-k*VectorXd::Unit(N-n, 0)).squaredNorm());
		//cout << "u="<<endl<<u<<endl<<"u^2="<<u.squaredNorm()<<endl;

		MatrixXd S(N-n, N-n);
		S = MatrixXd::Identity(N-n, N-n) - 2*u*u.transpose();
		//cout <<"S="<<endl<< S << endl;

		MatrixXd P(N, N);
		P << MatrixXd::Identity(n, n), MatrixXd::Zero(n, N-n), MatrixXd::Zero(N-n, n),  S;
		//cout <<"P="<<endl<<P<<endl;
		A = P.transpose()*A*P;
		cout <<"A="<<endl <<A<<endl;
	}
}

void matrixDiagonalisierung(Matrix5d& M) {
	cout << M << endl;
	householder(M);
}


int main() {

	Matrix5d M = Matrix5d::Ones();
	for (size_t i = 0; i < 5; i++) {
		M(i, i) = i+1;
	}
	matrixDiagonalisierung(M);
	// EigenSolver<Matrix5f> es(M);
	// cout << "Eigenwerte von M sind: "<< es.eigenvalues() << endl;

	return 0;
}
