//============================================================================
// Name        : aufgabe1.cpp
// Author      : Jasper Karl Lammering, Henning Ptaszyk, Timo Gräßer
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

class zustand{
private:
  int spin = 0;
public:
  zustand(int initialspin){
    if(initialspin==0){//den ersten zufälling mit spin up oder down erzeugen
      double zahl = drand48();
      if (zahl < 0.5) {
        spin = -1;
      }else {
        spin = +1;
      }
    }else{//den neuen entegegengesetzt wählen
      spin = initialspin*(-1);
    }
  }
  int getZustand(){
    return spin;
  }
  double getEnergie(double H){ // gibt jeweils die dem spinzustand zugeordnete energie zurueck
    return (-spin*H);
  }
  void changeZustand(){ //  veranlasse spin-flip
    spin *= -1;
  }
};


int main() {
  double schritte = 100000;
  double beta = 1;
  double H =-5; // min-wert fuer H
  ofstream myfile; //Daten abspeichern zum plotten mit plotRN.py
	myfile.open ("build/magnetisierung.txt");
  myfile << "#magnetisierung H \n";

  for (int i = 0; i <= 10000; i++) { // laufe von min-wert bis maxwert von H indem pro durchlauf 1/1000 addiert wird
  H += 0.001;
  zustand alt(0); // initalisiere "alt" in zufaelligem zustand
  double sum = 0;
  for (int k = 0; k < schritte; k++) {
    sum += alt.getZustand(); // addiere werte der spins
    //cout << alt.getZustand()<<endl;
    zustand neu(alt.getZustand()); // initialisiere neuen zustand gegensaetzlich zum alten
    double energiediff = neu.getEnergie(H) - alt.getEnergie(H);
    if(energiediff < 0){
      alt.changeZustand(); // wenn alte energie groesser als neue -> aktzeptiere neuen zustand
    }else{ // wenn neue energie groesser -> erzeuge gleichverteilte zufallszahl auf [0,1] und vergleiche mit boltzmannfaktor
      double zufallszahl = drand48();
      double boltzmann = exp(-beta*energiediff);
      //cout << energiediff << ' '<<zufallszahl<<" "<<boltzmann<<endl;
      if (zufallszahl<boltzmann) { // wenn boltzmannfaktor groesser aktzeptiere
        alt.changeZustand();
      }
    }
  }
  double magnetisierung = sum/schritte; // berechne mittlere magnetisierung
  myfile << setprecision(4)<< magnetisierung << " " << H << endl;
}
myfile.close();
  return 0;
}
