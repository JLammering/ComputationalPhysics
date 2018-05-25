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
#include <deque>

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

};


class gitter{
  private:
    int gitterGroesse = 30;
    gitterplatz gitter_array[30][30];
		int orientierungen;
		deque<int> orientliste;

public:
  gitter(int orientierungen_set){//Konstruktor
		orientierungen = orientierungen_set;
		for (int o_iter=0; o_iter<orientierungen; o_iter++) orientliste.push_back(o_iter);

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

  void changeEntry(int x, int y, int ziel){//bisher nur für q=2 implementiert
	// orientliste.erase(getEntry(x, y));
	// 			double rnd = drand48();
	// 			for( int i_orient = 0; i_orient < orientierungen - 1; i_orient++){
	// 				if ((rnd >  (i_orient) * 1/(orientierungen - 1)) && (rnd <  (i_orient + 1) * 1/(orientierungen - 1))){
	// 					gitter_array[x][y].set_eintrag(orientliste.at(i_orient));
	// 				}
	// 			}
	// orientliste.emplace(getEntry(x, y), getEntry(x,y));
	gitter_array[x][y].set_eintrag(ziel);


  }

	void setBesucht(int x, int y, bool value){
		gitter_array[x][y].set_besucht(value);
	}

	bool getBesucht(int x, int y){
		return gitter_array[(x % gitterGroesse + gitterGroesse)%gitterGroesse][(y % gitterGroesse + gitterGroesse)%gitterGroesse].get_besucht();
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
		gg = gg_setting;
    x= (x_setting%gg+gg)%gg;
    y = (y_setting%gg+gg)%gg;
  }
  int get_x(){ return x;}
  int get_y(){ return y;}
  void setting(int x_setting, int y_setting) {
    x = (x_setting%gg+gg)%gg;
    y = (y_setting%gg+gg)%gg;
  }
};



void wolffAlgorithmus(gitter& grid, int schritte, double kbT, int q){
  int gg = grid.getGitterGroesse();
  double beta = 1.0/kbT;
  double J = 1;
  double p_C = 1-exp(-2.0*beta*J);

  for (size_t t = 0; t < schritte; t++) {
		grid.absaven("2DTESTRUN"	+ to_string(t));


    int anfangs_x = drand48()*gg;
    int anfangs_y = drand48()*gg;

    queue<position> unbesuchteSpins;
    queue<position> cluster;

    position ersterSpin(anfangs_x, anfangs_y, gg);
    unbesuchteSpins.push(ersterSpin);
		cluster.push(ersterSpin);
    int richtung = grid.getEntry(anfangs_x, anfangs_y);

    while (!unbesuchteSpins.empty()) {

    position aktuell = unbesuchteSpins.front();
		int x = aktuell.get_x();
		int y = aktuell.get_y();
		unbesuchteSpins.pop();


    for (int i = -1; i <= 1; i++) { // erzeuge alle moeglichen Schritte um Nachbarn zu erreichen
      for (int j = -1; j <= 1; j++) {
        if (abs(i + j) == 1) {//nur NN
					double rnd = drand48();
					cout << (!grid.getBesucht(x+i, y+j)) << (richtung == grid.getEntry(x+i, y+j)) << (rnd < p_C) << endl;
          if(!grid.getBesucht(x+i, y+j) && richtung == grid.getEntry(x+i, y+j) && rnd < p_C){//wenn er noch nicht besucht wurde, die richtung die ist vom initialen Spin und die Wkeit stimmt:
						cout << "guter Nachbar gefunden" << endl;
						position nachbar((x+i), (x+j), gg);
            cluster.push(nachbar);
            unbesuchteSpins.push(nachbar);
          }
        }
      }
    }
		grid.setBesucht(x, y, true);//den gitterplatz markieren, dass er besucht wurde
		cout << "cluster.size()=" << cluster.size() << "unbesuchteSpins.size()=" << unbesuchteSpins.size()<<endl;
  } //unbesuchteSpins Schleife
	cout << "cluster gebildet" << "mit größe"<<cluster.size()<<endl;
	int zielflip = (int)(richtung + (drand48()*(q-1)+1)) % q;//nochmal drüber nachdenken
	cout << "cluster flippen von " << richtung << " nach " << zielflip<< endl;
	while(!cluster.empty()) {//cluster flippen
		cout << "position" <<  cluster.front().get_x()<< cluster.front().get_y() << endl;
		grid.changeEntry(cluster.front().get_x(), cluster.front().get_y(), zielflip);
		grid.setBesucht(cluster.front().get_x(), cluster.front().get_y(), false);
		cluster.pop();
	}
  } //schritte Schleife end
}


double b_crit(int q){
    return(log(1 + sqrt(q)));
}


int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	int q = 2; // anzahl
  gitter grid(q);
  wolffAlgorithmus(grid, 2, 1, q);

	return 0;
}
