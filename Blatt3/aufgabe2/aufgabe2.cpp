//============================================================================
// Name        : aufgabe2.cpp
// Author      : Jasper Karl Lammering, Henning Ptaszyk, Timo Gräßer
//============================================================================
#include <iostream>
#include <random>

using namespace std;

class gitter{
  private:
    int gitterGroesse = 10;
    int gitter_array[10][10];
public:
  gitter(){//Konstruktor
    for (int i = 0; i < gitterGroesse; i++) {//zeilen
      for (int k = 0; k < gitterGroesse; k++) {//spalten
        if (drand48()<0.5)
          gitter_array[i][k] = +1;
        else
          gitter_array[i][k] = -1;
      }
    }
  }

  int getGitterGroesse(){
    return gitterGroesse;
  }

  int getEntry(int x, int y){
    return gitter_array[x][y];
  }

  void changeEntry(int x, int y){
    gitter_array[x][y] *= -1;
  }

  int getEnergy(){
    int energie_berechnet = 0;
    for (int j = 0; j < gitterGroesse; j++) {//zeilen
      for (int l = 0; l < gitterGroesse; l++) {//spalten
        energie_berechnet +=
        (getEntry(j, l)*getEntry((j+1), (l)%gitterGroesse) +
        getEntry(j, l)*getEntry((j-1)%gitterGroesse, (l)%gitterGroesse) +
        getEntry(j, l)*getEntry((j)%gitterGroesse, (l-1)%gitterGroesse) +
        getEntry(j, l)*getEntry((j)%gitterGroesse, (l+1)%gitterGroesse));
        cout << "energie= " <<j<<l<< energie_berechnet << gitter_array[j][l]<< endl;
      }
    }

    return -1*energie_berechnet;
  }
};

void zweiDimensionenIsing(int schritte){
  //Gitter initialisieren
  gitter grid;
  int gitterGroesse = grid.getGitterGroesse();

  //Metropolis
  for (int i = 0; i < schritte; i++) {
    int x = drand48()*gitterGroesse;
    int y = drand48()*gitterGroesse;
    int spin_aktuell = grid.getEntry(x, y);
    int spin_nach_wechsel = spin_aktuell*(-1);
    int energie_aktuell = grid.getEnergy();


  }


  //ausgabe
  for (int i = 0; i < gitterGroesse; i++) {//zeilen
    for (int k = 0; k < gitterGroesse; k++) {//spalten
        cout << i<<k<< grid.getEntry(i, k) << "  ";
    }
    cout << endl;
  }

}

int main() {
  cout << "its something" << endl;
  int schritte = 10;
  zweiDimensionenIsing(schritte);
  return 0;
}
