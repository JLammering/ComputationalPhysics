//============================================================================
// Name        : aufgabe2.cpp
// Author      : Jasper Karl Lammering, Henning Ptaszyk, Timo Gräßer
//============================================================================
#include <iostream>
#include <random>
#include <fstream>
#include <string>


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
          gitter_array[i][k] = +1;
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
          getEntry(j, l)*(getEntry(((j+1)%gg+gg)%gg, l) +
           getEntry(((j-1)%gg+gg)%gg, l) +
           getEntry(j, ((l-1)%gg+gg)%gg) +
           getEntry(j, ((l+1)%gg+gg)%gg));
      }
    }

    return -1*(double)energie_berechnet*0.5;//*0.5 wegen doppelter nächster Nachbarn
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
};

gitter zweiDimensionenIsing(int schritte, double kbT, string dateiname){
  //Gitter initialisieren
  gitter grid;
  int gitterGroesse = grid.getGitterGroesse();
  double beta = pow(kbT, -1);

  //äqibrilierungsphase
  ofstream energyfile;
  energyfile.open("build/energie"+dateiname+".txt");

  //Metropolis
  double energie_allgemein = grid.getEnergy();
  for (int i = 0; i < schritte; i++) {
    energyfile << energie_allgemein / pow(gitterGroesse, 2) << " " << i << "\n";

    int x = drand48()*gitterGroesse;
    int y = drand48()*gitterGroesse;

    double energiediff = grid.getEnergyDiff(x, y);
    //wieder ändern wenn es verworfen wird
    if(energiediff < 0){// wenn alte energie groesser als neue -> aktzeptiere neuen zustand
      grid.changeEntry(x, y);
      energie_allgemein += energiediff; //gesamtenergie ändert sich
    }else{ // wenn neue energie groesser -> erzeuge gleichverteilte zufallszahl auf [0,1] und vergleiche mit boltzmannfaktor
      double zufallszahl = drand48();
      double boltzmann = exp(-beta*energiediff);
      if (zufallszahl<boltzmann)
        grid.changeEntry(x, y); // wenn boltzmannfaktor groesser aktzeptiere
        energie_allgemein += energiediff;
    }
  }
  energyfile.close();


  //ausgabe
  ofstream matrix;
    matrix.open("build/"+dateiname+".txt");
     for (int i = 0; i < gitterGroesse; i++) {//zeilen
       for (int k = 0; k < gitterGroesse; k++) {//spalten
         matrix << grid.getEntry(i, k) << " ";
       }
    matrix << "\n";
     }
    matrix.close();
  return(grid);
  }





int main() {
  cout << "its something" << endl;
  int schritte = 100000;
  double kbTgleicheins = 1;
  double kbTgleichzwei = 2;
  double kbTgleichdrei = 3;

  gitter g1 = zweiDimensionenIsing(schritte, kbTgleicheins, "kbTgleicheins");
  gitter g2 = zweiDimensionenIsing(schritte, kbTgleichzwei, "kbTgleichzwei");
  gitter g3 = zweiDimensionenIsing(schritte, kbTgleichdrei, "kbTgleichdrei");

  return 0;
}
