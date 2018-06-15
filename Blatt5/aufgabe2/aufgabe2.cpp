//============================================================================
// Name        : aufgabe2.cpp
// Author      : Henning Ptaszyk, Jasper Lammering
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <Eigen/Dense>
#include <bitset>
#include <vector>
using namespace std;
using namespace Eigen;


template<unsigned int dim>
MatrixXd build_untermatrix(bitset<unsigned int> config){

}


template<unsigned int dim>
void heisenbergModell(){
  cout << "dim = " <<  dim << endl;
  MatrixXd hmat(dim, dim); // hamilton matrix
  bitset<dim> configs[(int)pow(2, dim)]; // array mit den moeglichen konfigurationen
  vector<pair<int,int> > indices(pow(2, dim)); // vector in dem index und anzahl an "1en" jeder bitfolge gespeichert werden

  // erzeuge alle moeglichen kombinationen
  for (size_t i = 0; i < (size_t) sizeof(configs) * 0.125; i++){
    bitset<dim> current_set(i); // generiere binaer-darstellung aus aktuellem counter "i"
    configs[i] = current_set;
    indices[i].second = i;
    indices[i].first = configs[i].count();
    cout << to_string(i) + " " << configs[i] << endl;
    cout << "indices: " <<  indices[i].first << " " << indices[i].second << endl;
  }

  // sortiere vector indices
  sort(indices.begin(), indices.end());
  // for (size_t k = 0; k < pow(2, dim); k++) {
  //   cout << indices[k].first << " || " << indices[k].second << endl;
  // }

  bitset<dim> configs_sort[(int)pow(2, dim)]; // erzeuge array von bitfolgen um dort die konfigurationen in "richtiger" Reihenfolge zu speichern
  for (size_t m = 0; m < pow(2, dim); m++) { // befuelle configs_sort
    configs_sort[m] = configs[indices[m].second];
  }

  unsigned int last_elem = 0; // fuer element
  unsigned int last_ind = 0; // fuer index

  cout << indices.begin().first << endl;
  for (size_t p = 0; p < pow(2, dim) + 1; p++) {
    if((configs[p] != last) || (p == pow(2, dim))){
      vector<pair<int,int> > configs_needed(configs.begin() + last_elem, configs.begin() + p); // erstelle vector mit benoetigten konfigurationen
      hmat.block(last_elem, last_elem, p - last_ind, p - last_ind) = heisenbergModell<dim>(configs_needed);

      if (p != pow(2, dim)){
        last_elem = configs_sort[p].first;
        last_elem = p;
      }

    }
  }
  }



int main() {
	cout << "\nStart:" << endl; // prints !!!Hello World!!!
  heisenbergModell<4>();
	return 0;
}
