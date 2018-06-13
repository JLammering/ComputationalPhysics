#include <iostream>
#include <Eigen/Dense>
#include <fstream>

using namespace std;
using namespace Eigen;

//zustandserzeugung
MatrixXi erzeuger(int N, int i){
  int a = (int)pow(2, N);
  MatrixXi A;
  A = MatrixXi::Zero(N, a);
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < a; j++) {
      A(j, i) = (j/((int)pow(2,i)))%2;
    }
  }
  // return A.row(n);
  MatrixXi B;
  B=MatrixXi::Zero(a,N);
  int counter =0;
  for (size_t i = 0; i < N; i++) {//über unterräume iterieren
    for (size_t j = 0; j < a; j++) {//zustände durchgehen und sortieren
      if (i==A.row(j).sum()) {//zustand in richtigen Unterraum einsortieren
        B.row(counter)=A.row(j);
        counter++;
      }
    }
  }
  return B;
}

//zustand->unterraum

//permutationsoperator

//hamiltonian








int main() {

  return 0;
}
