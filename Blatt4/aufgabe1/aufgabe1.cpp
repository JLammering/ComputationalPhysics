//============================================================================
// Name        :wolff-algorithm.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stack>
using namespace std;


class gitter{
  private:
    int gitterGroesse = 100;
    int gitter_array[100][100];
public:
  gitter(int orientierungen){//Konstruktor
		double wkeit = 1.0 / (double)orientierungen;
		for (int i = 0; i < gitterGroesse; i++) {//zeilen
      for (int k = 0; k < gitterGroesse; k++) {//spalten
        double rnd = drand48();
        for( int i_orient = 0; i_orient < orientierungen; i_orient++){
					if ((rnd >  (i_orient) * wkeit) && (rnd <  (i_orient + 1) * wkeit)){
	          gitter_array[i][k] = i_orient;
					}
				}
      }
    }
  }

  int getGitterGroesse(){
    return gitterGroesse;
  }

  int getEntry(int x, int y){
    return gitter_array[(x % gitterGroesse + gitterGroesse)%gitterGroesse][(y % gitterGroesse + gitterGroesse)%gitterGroesse];
  }

  void changeEntry(int x, int y){
    gitter_array[x][y] *= -1;
  }


  double getEnergyDiff(int j, int l){
    int spin_aktuell = getEntry(j, l);
    int gg = getGitterGroesse();
    double energie_lokal = spin_aktuell*(getEntry(((j+1)%gg+gg)%gg, l) +
     getEntry(((j-1)%gg+gg)%gg, l) +
     getEntry(j, ((l-1)%gg+gg)%gg) +
     getEntry(j, ((l+1)%gg+gg)%gg));

    return 2*energie_lokal;
  }


  double getMagnetisierung(){
    int gg = getGitterGroesse();
    int sum = 0;
    for (int i = 0; i < gg; i++) {
      for (int k = 0; k < gg; k++) {
        sum += getEntry(i,k);
      }
    }
    return ((double)sum/pow(gg, 2));
  }


  void absaven(string dateiname){
    ofstream myfile;
		myfile.open("build/"+dateiname+".txt");
    for (size_t i = 0; i < gitterGroesse; i++) {
    	for (size_t j = 0; j < gitterGroesse; j++) {
    		myfile << getEntry(i, j) << " ";
    	}
      myfile << "\n";
    }
    myfile.close();
  }
};

struct position{
private:
  int x;
  int y;
public:
  position(int x_setting, int y_setting){
    x= x_setting;
    y = y_setting;
  }
  int get_x(){ return x;}
  int get_y(){ return y;}
  void setting(int x_setting, int y_setting) {
    x = x_setting;
    y = y_setting;
  }
};



void wolffAlgorithmus(gitter& grid, int schritte, double kbT){
  int gitterGroesse = grid.getGitterGroesse();
  double beta = 1.0/kbT;
  double J = 1;
  double p_C = 1-exp(-2.0*beta*J);

  for (size_t i = 0; i < schritte; i++) {
    double x = drand48();
    double y = drand48();
    stack<position> unbesuchteSpins;
    stack<position> cluster;

    position ersterSpin(x, y);
    unbesuchteSpins.push(ersterSpin);

    int richtung = grid.getEntry(x, y);

    while (unbesuchteSpins.size() > 0) {
    position aktuell = unbesuchteSpins.back();
    position nachbar(-1,-1);

    for (int i = -1; i <= 1; i++) { // erzeuge alle moeglichen Schritte um NN zu erreichen
      for (int j = -1; j <= 1; j++) {
        if (abs(i + j) == 1) {
          if(drand48() < p_C){
            nachbar.setting(x + i, y + j);
            cluster.push(nachbar);
            unbesuchteSpins.push(nachbar);
          }
        }
      }
    }
  }

  }//schritte Schleife ende

}


double b_crit(int q){
    return(log(1 + sqrt(q)));
}


int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

  gitter grid(4);
  grid.absaven("thisisatest");
  wolffAlgorithmus(grid, 1, 1);


	return 0;
}
