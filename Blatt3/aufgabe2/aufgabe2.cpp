//============================================================================
// Name        : aufgabe2.cpp
// Author      : Jasper Karl Lammering, Henning Ptaszyk, Timo Gräßer
//============================================================================
#include <iostream>
#include <random>
#include <fstream>


using namespace std;

class gitter{
  private:
    int gitterGroesse = 40;
    int gitter_array[40][40];
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

  double getEnergy(){
    int energie_berechnet = 0;
    int gg = getGitterGroesse();
      for (int j = 0; j < gg; j++) {//zeilen
        for (int l = 0; l < gg; l++) {//spalten
        energie_berechnet +=
          (getEntry(j, l)*getEntry(((j+1)%gg+gg)%gg, l) +
           getEntry(j, l)*getEntry(((j-1)%gg+gg)%gg, l) +
           getEntry(j, l)*getEntry(j, ((l-1)%gg+gg)%gg) +
           getEntry(j, l)*getEntry(j, ((l+1)%gg+gg)%gg));
      }
    }

    return -1*(double)energie_berechnet*0.5;//*0.5 wegen doppelter nächster Nachbarn
  }
};

void zweiDimensionenIsing(int schritte, double beta, string dateiname){
  //Gitter initialisieren
  gitter grid;
  int gitterGroesse = grid.getGitterGroesse();

  //Metropolis
  for (int i = 0; i < schritte; i++) {
    int x = drand48()*gitterGroesse;
    int y = drand48()*gitterGroesse;

    double energie_aktuell = grid.getEnergy();
    grid.changeEntry(x, y);
    double energie_nach_wechsel = grid.getEnergy();
    double energiediff = energie_nach_wechsel - energie_aktuell;
    //wieder ändern wenn es verworfen wird
    if(energiediff < 0){
      // wenn alte energie groesser als neue -> aktzeptiere neuen zustand
    }else{ // wenn neue energie groesser -> erzeuge gleichverteilte zufallszahl auf [0,1] und vergleiche mit boltzmannfaktor
      double zufallszahl = drand48();
      double boltzmann = exp(-beta*energiediff);
      //cout << energiediff << ' '<<zufallszahl<<" "<<boltzmann<<endl;
      if (zufallszahl<boltzmann) { // wenn boltzmannfaktor groesser aktzeptiere
      }else
        grid.changeEntry(x, y);//zurück wechseln weil neuer Vorschlag verworfen wird
    }



  }


  //ausgabe
  ofstream myfile;
    myfile.open(dateiname);
     for (int i = 0; i < gitterGroesse; i++) {//zeilen
       for (int k = 0; k < gitterGroesse; k++) {//spalten
         myfile << grid.getEntry(i, k) << " ";
       }
    myfile << "\n";
     }
    myfile.close();
  }



int main() {
  cout << "its something" << endl;
  int schritte = 10000;
  int kbT = 1;
  double beta = 1/((double)kbT);
  zweiDimensionenIsing(schritte, beta, "build/kbT=1.txt");
  return 0;
}
