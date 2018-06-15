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
#include <ctime>
using namespace Eigen;
using namespace std;

MatrixXd householder(MatrixXd A){
	int N = A.rows();
	MatrixXd Arueck(N, N);
	Arueck = A;
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
		Arueck = P.transpose()*Arueck*P;

		// Q *= P.transpose();
	}
	// MatrixXd R(N, N);
	// R = Q.transpose()*A;
return Arueck;
}

MatrixXd QausDerQRZerlegung(MatrixXd A){
  MatrixXd Q = A;
  MatrixXd U = A;
  for (int k = 0; k < U.rows(); k++){
    // cout << "K =" << k  <<endl;
    for(int j = 0; j < k; j++){
		  U.col(k) -= (double)(U.col(j).adjoint() * A.col(k)) / U.col(j).squaredNorm() * U.col(j);
    }
    Q.col(k) = U.col(k) / U.col(k).norm();
    //cout <<"Q("<< k << ")=" << endl  << Q.col(k) << endl;
  }
  return Q;
}

MatrixXd QR_Iteration(MatrixXd A, size_t steps){
	for(int i = 0 ; i < steps ; i++){
  	MatrixXd Q = QausDerQRZerlegung(A);
   	A = Q.adjoint() * A * Q;
	}
	return A;
}


MatrixXd Lanczos(MatrixXd A, MatrixXd q){
	unsigned int dim = A.rows();
	MatrixXd Q(dim, dim);
	Q.col(0) = q / q.norm();

	MatrixXd T(dim, dim);
	T = MatrixXd::Zero(dim, dim);

	double alpha = Q.col(0).transpose().conjugate() * A * Q.col(0);
	VectorXd x = A * Q.col(0) - alpha * Q.col(0);
	T(0, 0) = alpha;
	double beta = x.norm();
	Q.col(1) = x / beta;
	T(1, 0) = beta;
	T(0, 1) = T(1, 0); // beta geht auch , ist aber weniger kuhl
	for (size_t i = 2; i < dim; i++) {
		  T(i - 1, i - 1) = Q.col(i - 1).transpose().conjugate() * A * Q.col(i - 1);//alpha
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

	//a)
	MatrixXd M(6, 6);
	M << 9, 10, -7, 15, 13, 14,
			 10, 1, 7, 15, 6, 11,
			 -7, 7, 17, 3, -16, -4,
			 15, 15, 3, -4, 7, 9,
			 13, 6, -16, 7, 11, 16,
			 14, 11, -4, 9, 16, 8;
	cout << "M = "<<endl<< M << endl<<endl;
	VectorXd q_0_1(6, 1);
	q_0_1 << 1, 1, 1, 1, 1, 1;
	VectorXd q_0_2(6, 1);
	q_0_2 << 0, 6, 1, 9, 9, 6;

	MatrixXd L_1 = Lanczos(M, q_0_1);
	MatrixXd L_2 = Lanczos(M, q_0_2);
	cout << "Mit q_0 = ("<<q_0_1.transpose()<<")"<<endl<<"Matrix nach Lanczos-Verfahren: "<<endl<<L_1<<endl;
	cout << "Mit q_0 = ("<<q_0_2.transpose()<<")"<<endl<<"Matrix nach Lanczos-Verfahren: "<<endl<<L_2<<endl<<endl;

	//b)
	cout << "Eigenwerte von Lanczos-Matrix nach QR-Iteration sind: ("<< QR_Iteration(Lanczos(M, q_0_1), 30).diagonal().transpose() <<")"<< endl;
	EigenSolver<MatrixXd> esM(M);
	cout << "Eigenwerte von M mit Eigen sind: ("<< esM.eigenvalues().real().transpose()<<")" << endl;

	//c)
	double Tarray_eigen[18];
	double Tarray_lanczos[18];
	double Tarray_householder[18];
	clock_t t; // zeitvariable t initialisieren
	for (size_t N = 3; N <= 20; N++) {
		for (size_t i = 0; i < 50; i++) {
		MatrixXd zufall = MatrixXd::Random(N, N);
		MatrixXd zufall_sym = zufall + zufall.transpose();
		t = clock(); // setze t auf aktuelle zeit
		EigenSolver<MatrixXd> esM(zufall_sym);
		t = clock() - t; // berechne laufzeit
		Tarray_eigen[N-3] += (double)t/CLOCKS_PER_SEC;
		// std::cout << "Eigensolver Zeit:"<< (double)t/CLOCKS_PER_SEC << '\n';

		t = clock();
		VectorXd q_0 = MatrixXd::Ones(N, 1);
		QR_Iteration(Lanczos(zufall_sym, q_0), 30);
		t = clock() - t;
		Tarray_lanczos[N-3] += (double)t/CLOCKS_PER_SEC;
		// std::cout << "Lanczos + QR Zeit:"<< (double)t/CLOCKS_PER_SEC << '\n';

		t = clock();
		QR_Iteration(householder(zufall_sym), 30);
		t = clock() - t;
		Tarray_householder[N-3] += (double)t/CLOCKS_PER_SEC;
		// std::cout << "householder + QR Zeit:"<< (double)t/CLOCKS_PER_SEC << '\n';
	}
	}
	ofstream myfile;
	myfile.open("build/zeiten.txt");
	myfile << "#T_eigen, T_lanczos, T_householder\n";
	for (size_t i = 0; i < 18; i++) {
		myfile << Tarray_eigen[i] * 0.02 <<" "<< Tarray_lanczos[i] * 0.02 <<" "<< Tarray_householder[i] * 0.02 << "\n"; // * 0.02 um fuer mittelwerte durch 50 zu teilen
	}
	myfile.close();
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!! sehr wichtig!
	return 0;
}
