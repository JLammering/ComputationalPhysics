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
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct gitterplatz{
private:
	int eintrag;
	bool besucht;
public:
	gitterplatz(){
		eintrag = 0;
		besucht = false;
	}
	void set_eintrag(int eintrag_setting){eintrag = eintrag_setting;}
	void set_besucht(bool besucht_setting){besucht = besucht_setting;}
	int get_eintrag(){return eintrag;}
	bool get_besucht(){return besucht;}

}


class gitter{
  private:
    int gitterGroesse = 100;
    gitterplatz gitter_array[100][100];
public:
  gitter(int orientierungen){//Konstruktor
		double wkeit = 1.0 / (double)orientierungen;
		for (int i = 0; i < gitterGroesse; i++) {//zeilen
      for (int k = 0; k < gitterGroesse; k++) {//spalten
        double rnd = drand48();
        for( int i_orient = 0; i_orient < orientierungen; i_orient++){
					if ((rnd >  (i_orient) * wkeit) && (rnd <  (i_orient + 1) * wkeit)){
	          gitter_array[i][k].set_eintrag(i_orient);
					}
				}
      }
    }
  }

  int getGitterGroesse(){
    return gitterGroesse;
  }

  int getEntry(int x, int y){
    return gitter_array[(x % gitterGroesse + gitterGroesse)%gitterGroesse][(y % gitterGroesse + gitterGroesse)%gitterGroesse].get_eintrag();
  }

  void changeEntry(int x, int y){//bisher nur für q=2 implementiert
    gitter_array[x][y].set_eintrag(gitter_array[x][y].get_eintrag()*=-1);
  }

	void setBesucht(int x, int y){
		gitter_array[x][y].set_besucht(true);
	}

	bool getBesucht(int x, int y){
		return gitter_array[x][y].get_besucht();
	}

	//
  // double getEnergyDiff(int j, int l){
  //   int spin_aktuell = getEntry(j, l);
  //   int gg = getGitterGroesse();
  //   double energie_lokal = spin_aktuell*(getEntry(((j+1)%gg+gg)%gg, l) +
  //    getEntry(((j-1)%gg+gg)%gg, l) +
  //    getEntry(j, ((l-1)%gg+gg)%gg) +
  //    getEntry(j, ((l+1)%gg+gg)%gg));
	//
  //   return 2*energie_lokal;
  // }


  // double getMagnetisierung(){
  //   int gg = getGitterGroesse();
  //   int sum = 0;
  //   for (int i = 0; i < gg; i++) {
  //     for (int k = 0; k < gg; k++) {
  //       sum += getEntry(i,k);
  //     }
  //   }
  //   return ((double)sum/pow(gg, 2));
  // }


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
	int gg;
public:
  position(int x_setting, int y_setting, int gg_setting){
    x= x_setting;
    y = y_setting;
		gg = gg_setting;
  }
  int get_x(){ return x;}
  int get_y(){ return y;}
  void setting(int x_setting, int y_setting) {
    x = (x_setting%gg+gg)%gg;
    y = (y_setting%gg+gg)%gg;
  }
};



void wolffAlgorithmus(gitter& grid, int schritte, double kbT){
  int gg = grid.getGitterGroesse();
  double beta = 1.0/kbT;
  double J = 1;
  double p_C = 1-exp(-2.0*beta*J);

  for (size_t i = 0; i < schritte; i++) {
    double anfangs_x = drand48()*gg;
    double anfangs_y = drand48()*gg;

    queue<position> unbesuchteSpins;
    queue<position> cluster;

    position ersterSpin(anfangs_x, anfangs_y, gg);
    unbesuchteSpins.push(ersterSpin);
		cluster.push(ersterSpin);
    int richtung = grid.getEntry(anfangs_x, anfangs_y);

    while (!unbesuchteSpins.empty()) {
    position aktuell = unbesuchteSpins.front();

		unbesuchteSpins.pop();

		x = aktuell.get_x();
		y = aktuell.get_y();
    position nachbar(-1,-1, gg);


    for (int i = -1; i <= 1; i++) { // erzeuge alle moeglichen Schritte um NN zu erreichen
      for (int j = -1; j <= 1; j++) {
        if (abs(i + j) == 1) {
          if(!grid.getBesucht(x+i, y+j) && richtung == grid.getEntry(x+i, y+j) && drand48() < p_C){//wenn er noch nicht besucht wurde, die richtung die ist vom initialen Spin und die Wkeit stimmt:
            nachbar.setting((x+i), (y+j));
            cluster.push(nachbar);
            unbesuchteSpins.push(nachbar);
          }
        }
      }
    }
		grid.setBesucht(x, y);//den gitterplatz markieren, dass er besucht wurde
  }

  }//schritte Schleife ende

}


double b_crit(int q){
    return(log(1 + sqrt(q)));
}


int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

  gitter grid(2);
  grid.absaven("thisisatest");
  wolffAlgorithmus(grid, 1, 1);


	return 0;
}
