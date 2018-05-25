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


class gitter{
  private:
    int gitterGroesse = 100;
    int gitter_array[100][100];
		int orientierungen;
public:
  gitter(int orientierungen_set){//Konstruktor
		orientierungen = orientierungen_set;

		double wkeit = 1.0 / (double)orientierungen;
		for (int i = 0; i < gitterGroesse; i++) {//zeilen
      for (int k = 0; k < gitterGroesse; k++) {//spalten
        double rnd = drand48();
        for( int i_orient = 0; i_orient < orientierungen; i_orient++){ // initaliesiere gitter zufaellig mit verschiedenen Eintraegen.
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

  void changeEntry(int x, int y, int ziel){
	gitter_array[(x % gitterGroesse + gitterGroesse)%gitterGroesse][(y % gitterGroesse + gitterGroesse)%gitterGroesse]= ziel;
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

struct position{ // erzeuge struct das eine position auf dem gitter darstellt
private:
  int x;
  int y;
	int gg;
public:
  position(int x_setting, int y_setting, int gg_setting){
		gg = gg_setting;
    x= (x_setting%gg+gg)%gg; // periodische Randbedingungen
    y = (y_setting%gg+gg)%gg;
  }
  int get_x(){ return x;}
  int get_y(){ return y;}

};



void wolffAlgorithmus(gitter& grid, int schritte, double kbT, int q){
  int gg = grid.getGitterGroesse();
  double beta = 1.0/kbT; // berechne beta
  double J = 1;
  double p_C = 1-exp(-2.0*beta*J); //Wkeit zum Cluster hinzugefügt zu werden

  for (size_t t = 0; t < schritte; t++) {
		grid.absaven(to_string(q)+"ZUSTAENDE_RUN"	+ to_string(t)); // speichere Gitter ab



    int anfangs_x = drand48()*gg;  // zufaellige startposition
    int anfangs_y = drand48()*gg;

    queue<position> unbesuchteSpins; // schlange fuer unbesuchteSpins

    position ersterSpin(anfangs_x, anfangs_y, gg); // erzeuge position mit der startposition
    unbesuchteSpins.push(ersterSpin); // fuege diese erste position den unbesuchten Spins hinzu
    int richtung = grid.getEntry(anfangs_x, anfangs_y); // speichere die ausrichtung des ausgewaehlten spins
		int zielflip = (int)(richtung + (drand48()*(q-1)+1)) % q;//ergibt zufällig eine der anderen verbleibenden Orientierungen


    while (!unbesuchteSpins.empty()) { // fuehre so lange aus, wie es noch unbesuchte spins im cluster gibt
		if (unbesuchteSpins.size()>gg*gg) {//ist irgendwie nötig weil sonst zu viele mitgenommen werden
			break;
		}

    position aktuell = unbesuchteSpins.front();//unbesuchteSpins durchgehen dessen Nachbarn checken
		int x = aktuell.get_x();
		int y = aktuell.get_y();
		unbesuchteSpins.pop();//rauslöschen


    for (int i = -1; i <= 1; i++) { // erzeuge alle moeglichen Schritte um Nachbarn zu erreichen
      for (int j = -1; j <= 1; j++) {
        if (abs(i + j) == 1) {//nur Naechste Nachbarn
					double rnd = drand48();
          if((richtung == grid.getEntry(x+i, y+j)) && (drand48() < p_C)){//wenn die richtung die gleiche wie beim initialen Spin ist und die Wkeit stimmt:
						position nachbar((x+i), (y+j), gg); // erzeuge nachbarposition
						grid.changeEntry(x+i, y+j, zielflip); // flip jeden cluster eintrag einzlend
            unbesuchteSpins.push(nachbar); //den nachbar zu den unbesuchteSpins hinzufügen um dann seine Nachbarn durchgehen zu können
          }
        }
      }
    }
  } //unbesuchteSpins Schleife
  } //schritte Schleife end
}


double kbT_crit(int q){  // berechnet den kritischen Wert fuer kbT
    return(1 / log(1 + sqrt(q)));
}


int main() {

	int q1 = 2; // anzahl verschiedener einstellmoeglichkeiten
	int q2 = 3;
  gitter grid1(q1); // erzeuge gitter mit spins
	gitter grid2(q2);
  wolffAlgorithmus(grid1, 100, 1, q1);
	wolffAlgorithmus(grid2, 100, 1, q2);



	return 0;
}
