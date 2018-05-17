//============================================================================
// Name        : aufgabe2.cpp
// Author      : Jasper Karl Lammering, Henning Ptaszyk, Timo Gräßer
//============================================================================
#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

class gitter{
  private:
    int gitterGroesse = 100;
    int gitter_array[100][100];
    double wkeit = 0.5;
public:
  gitter(bool allesgleich){//Konstruktor
    if(allesgleich){
      wkeit = 1.0;
    }
    for (int i = 0; i < gitterGroesse; i++) {//zeilen
      for (int k = 0; k < gitterGroesse; k++) {//spalten
        if (drand48()<wkeit)
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
          getEntry(j, l)*(getEntry(((j+1)%gg+gg)%gg, l) +
           getEntry(((j-1)%gg+gg)%gg, l) +
           getEntry(j, ((l-1)%gg+gg)%gg) +
           getEntry(j, ((l+1)%gg+gg)%gg));
      }
    }
    return -1*(double)energie_berechnet;
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

  double getabsMagnetisierung(){
    return(abs(getMagnetisierung()));
  }
};

void zweiDimensionenIsing(int schritte, double kbT, string dateiname, gitter& grid){
  int gitterGroesse = grid.getGitterGroesse();
  double beta = pow(kbT, -1);

  //energie
  ofstream energyfile;
  energyfile.open("build/energie"+dateiname+".txt");
  double energie_allgemein = grid.getEnergy();

  //magnetisierung
  ofstream magnetfile;
  magnetfile.open("build/magnet"+dateiname+".txt");
  double magnetisierung_allgemein = grid.getMagnetisierung();

  //magnetisierungabs
  ofstream absmagnetfile;
  absmagnetfile.open("build/absmagnet"+dateiname+".txt");

  //Metropolis
  for (int i = 0; i < schritte; i++) {
    if(i%(10000)== 0){//pro sweep ein messpunkt
    energyfile << energie_allgemein / pow(gitterGroesse, 2) << " " << i/1e4<< "\n";
    magnetfile << magnetisierung_allgemein << " " << i/1e4 << "\n";
    absmagnetfile << abs(magnetisierung_allgemein) << " " << i/1e4 << "\n";
  }
    int x = drand48()*gitterGroesse;
    int y = drand48()*gitterGroesse;

    double energiediff = grid.getEnergyDiff(x, y);
    //energyfile << energiediff/pow(gitterGroesse, 2) << "\n";
    //wieder ändern wenn es verworfen wird
    if(energiediff <= 0){// wenn alte energie groesser als neue -> aktzeptiere neuen zustand
      grid.changeEntry(x, y);
      energie_allgemein += energiediff; //gesamtenergie ändert sich
      magnetisierung_allgemein += 2 * grid.getEntry(x, y) / pow((double)gitterGroesse, 2);
    }else{ // wenn neue energie groesser -> erzeuge gleichverteilte zufallszahl auf [0,1] und vergleiche mit boltzmannfaktor
      double zufallszahl = drand48();
      double boltzmann = exp(-beta*energiediff);
      if (zufallszahl<boltzmann){
        grid.changeEntry(x, y); // wenn boltzmannfaktor groesser aktzeptiere
        energie_allgemein += energiediff;
        magnetisierung_allgemein += 2 * grid.getEntry(x, y) / pow((double)gitterGroesse, 2);}
    }
  }
  energyfile.close();
  magnetfile.close();
  absmagnetfile.close();


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
  }

//
void templiste(vector<double>& temperaturen, double start, double ende, double schritte){
  for (double T = start; T <= ende; T += schritte) {
    temperaturen.push_back(T);
  }
}

// zweite funktion fuer temperaturplot
void TempZweiDimensionenIsing(int schritte, string dateiname){

  //magnetisierung
  ofstream magnetfile;
  magnetfile.open("build/tempmagnet"+dateiname+".txt");


  //magnetisierungabs
  ofstream absmagnetfile;
  absmagnetfile.open("build/tempabsmagnet"+dateiname+".txt");

  //temperaturen vektoren erstellen
  vector <double> temperaturen;
  templiste(temperaturen, 1, 2.1, 0.1);
  templiste(temperaturen, 2.1, 2.4, 0.01);
  templiste(temperaturen, 2.5, 3.1, 0.1);


  for( int iter = 0; iter < temperaturen.size(); iter ++){
    if(iter%12==0){
      cout << "Temperatur = " << temperaturen.at(iter) << endl;
    }
  //Gitter initialisieren
  gitter grid(false);
  int gitterGroesse = grid.getGitterGroesse();

  double kbT = temperaturen.at(iter);
  double magnetisierung_allgemein = grid.getMagnetisierung();
  double beta = pow(kbT, -1);

  //Metropolis
  int wieVielWerte = 1e4;
  for (int i = 0; i < schritte; i++) {

    int x = drand48()*gitterGroesse;
    int y = drand48()*gitterGroesse;

    double energiediff = grid.getEnergyDiff(x, y);
    //energyfile << energiediff/pow(gitterGroesse, 2) << "\n";
    //wieder ändern wenn es verworfen wird
    if(energiediff <= 0){// wenn alte energie groesser als neue -> aktzeptiere neuen zustand
      grid.changeEntry(x, y);
      magnetisierung_allgemein += 2 * grid.getEntry(x, y) / pow((double)gitterGroesse, 2);
    }else{ // wenn neue energie groesser -> erzeuge gleichverteilte zufallszahl auf [0,1] und vergleiche mit boltzmannfaktor
      double zufallszahl = drand48();
      double boltzmann = exp(-beta*energiediff);
      if (zufallszahl<boltzmann){
        grid.changeEntry(x, y); // wenn boltzmannfaktor groesser aktzeptiere
        magnetisierung_allgemein += 2 * grid.getEntry(x, y) / pow((double)gitterGroesse, 2);}
    }
  }
  magnetfile << magnetisierung_allgemein << " " << temperaturen.at(iter) << "\n";
  absmagnetfile << abs(magnetisierung_allgemein) << " " << temperaturen.at(iter) << "\n";
}

  magnetfile.close();
  absmagnetfile.close();


}



int main() {
  cout << "its something" << endl;
  int schritteprosweep = 1e4;
  int schritteaufwaerm = 400*schritteprosweep;
  int sweeeeeeeeeeeeep = 1e4*schritteprosweep;
  int tempschritte = 1e3*schritteprosweep; //am ende 1e3 einstellen
  gitter gridGleich1(true);
  gitter gridGleich2(true);
  gitter gridGleich3(true);
  gitter gridZufall1(false);
  gitter gridZufall2(false);
  gitter gridZufall3(false);

  //aufwärmphase
  zweiDimensionenIsing(schritteaufwaerm, 1, "kbTgleicheins", gridZufall1);
  zweiDimensionenIsing(schritteaufwaerm, 2, "kbTgleichzwei", gridZufall2);
  zweiDimensionenIsing(schritteaufwaerm, 3, "kbTgleichdrei", gridZufall3);

  zweiDimensionenIsing(schritteaufwaerm, 1, "kbTgleicheinsgleich", gridGleich1);
  zweiDimensionenIsing(schritteaufwaerm, 2, "kbTgleichzweigleich", gridGleich2);
  zweiDimensionenIsing(schritteaufwaerm, 3, "kbTgleichdreigleich", gridGleich3);
  cout << "alle Systeme aufgewärmt" << endl;


  //sweep
  zweiDimensionenIsing(sweeeeeeeeeeeeep, 1, "kbTgleicheins_sweep", gridZufall1);
  cout << "erster sweeeeeeeeeeeeep" << endl;
  zweiDimensionenIsing(sweeeeeeeeeeeeep, 2, "kbTgleichzwei_sweep", gridZufall2);
  cout << "zweiter sweeeeeeeeeeeeep" << endl;
  zweiDimensionenIsing(sweeeeeeeeeeeeep, 3, "kbTgleichdrei_sweep", gridZufall3);
  cout << "dritter sweeeeeeeeeeeeep" << endl;

  //tempplots
  cout << "Temperaturenplots" << endl;
  TempZweiDimensionenIsing(tempschritte, "datei");


  return 0;
}
