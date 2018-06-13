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
#include <string>
using namespace Eigen;
using namespace std;

MatrixXd householder(MatrixXd A){
	int N = A.rows();
	MatrixXd Arueck(N, N);
	MatrixXd test(N, N);
	Arueck = A;
	test = A;
	MatrixXd Q(N, N);
	Q = MatrixXd::Identity(N, N);

	for (size_t n = 1; n <= N-2; n++) {//Transformation N-2 mal
		MatrixXd v(N-n, 1);
		v = Arueck.col(n-1).tail(N-n);
		double k = sqrt(v.squaredNorm()); // die quadratische Summe der letzten  (N-n) Zahlen von der n-ten Spalte
		k = copysign(abs(k), -Arueck(n, n-1)); // um Rundungsfehler zu vermeiden
		MatrixXd u(N-n, 1);
		u = (v-k*VectorXd::Unit(N-n, 0))/sqrt((v-k*VectorXd::Unit(N-n, 0)).squaredNorm());

		MatrixXd S(N-n, N-n);
		S = MatrixXd::Identity(N-n, N-n) - 2*u*u.transpose();

		MatrixXd P(N, N);
		P << MatrixXd::Identity(n, n), MatrixXd::Zero(n, N-n), MatrixXd::Zero(N-n, n),  S;
		test = P*test;
		cerr <<"das mach PT*A"<< endl << test <<endl<< endl;
		Arueck = P.transpose()*Arueck*P;

		// Q *= P.transpose();
	}
	// MatrixXd R(N, N);
	// R = Q.transpose()*A;
return Arueck;
}

void jacobiRotation(MatrixXd& A){
	int N = A.rows();

	MatrixXd Qt(N, N);
	Qt = MatrixXd::Identity(N, N);
	for (size_t i = 0; i < N-1; i++) {//untere nebendiagonal elemente wegdrehen
		// MatrixXd AohneDiagonale(N, N);//Matrix ohne die Diagonalelemente um das größte nicht diagonale Element zu finden
		// AohneDiagonale = A.cwiseAbs();
		// AohneDiagonale.diagonal() = VectorXd::Zero(N);
		// MatrixXd::Index p, q;
		// AohneDiagonale.maxCoeff(&p, &q);//speichert in p und q die Koordinaten des Größten Element
		//Koeffizienten Berechnen
		int p = i+1;
		int q = i;
		double theta =  (A(q,q)-A(p,p))/(2*A(p, q));
		double t = copysign(1.0, theta)/(abs(theta) + sqrt(pow(theta, 2) + 1));
		double c = 1/sqrt(1 + pow(t, 2));
		double s = t*c;
		MatrixXd P(N, N);//Transformationsmatrix aus Koeffizienten zusammenbauen
		P = MatrixXd::Identity(N, N);
		P(p,p) = c;
		P(q, q) = c;
		P(p, q) = s;
		P(q, p) = -s;
		//A = P.transpose()*A*P;//transformation
		Qt = P*Qt;
	}
	cout <<"A nach Jacobi:"<<endl<<Qt*A<<endl;
}


MatrixXd Lanczos(MatrixXd A, MatrixXd q){
	unsigned int dim = A.rows();
	MatrixXd Q(dim, dim);
	Q.col(0) = q / q.norm();

	MatrixXd T(dim, dim);

	double alpha = Q.col(0).transpose().conjugate() * A * Q.col(0);
	VectorXd x = A * Q.col(0) - alpha * Q.col(0);
	T(0, 0) = alpha;
	double beta = x.norm();
	Q.col(1) = x / beta;
	T(1, 0) = beta;
	T(0, 1) = T(1, 0); // beta geht auch , ist aber weniger kuuhl
	for (size_t i = 2; i < dim; i++) {
		  T(i - 1, i - 1) = Q.col(i - 1).transpose().conjugate() * A *Q.col(i - 1);//alpha
		 	VectorXd x(dim, 1);
			x = A * Q.col(i - 1) - T(i - 2, i - 1) * Q.col(i - 2) - T(i - 1, i - 1) * Q.col(i - 1);
			T(i - 1, i) = x.norm();
			T(i , i - 1) = T(i - 1, i);
	   	Q.col(i) = x / T(i -1, i);
 	}
	T(dim-1, dim-1) = Q.col(dim - 1).transpose().conjugate() * A *Q.col(dim - 1);
	return T;
}



int main() {

	MatrixXd M(6, 6);
	M << 9, 10, -7, 15, 13, 14,
			 10, 1, 7, 15, 6, 11,
			 -7, 7, 17, 3, -16, -4,
			 15, 15, 3, -4, 7, 9,
			 13, 6, -16, 7, 11, 16,
			 14, 11, -4, 9, 16, 8;
	cout << M << endl;
	VectorXd q_0(6, 1);
	q_0 << 1, 1, 1, 1, 1, 1;
	cout << "Lanczos"<<endl<<Lanczos(M, q_0) << endl;
	EigenSolver<MatrixXd> esM(M);
	cout << "Eigenwerte von M sind: "<< esM.eigenvalues() << endl;

	MatrixXd L = Lanczos(M, q_0);
	EigenSolver<MatrixXd> esL(L);
	cout << "Eigenwerte von L sind: "<< esL.eigenvalues() << endl;


	cout << "householder"<<endl<<householder(M) << endl;
	MatrixXd H(M.rows(), M.rows());
	H = householder(M);
	jacobiRotation(H);
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
