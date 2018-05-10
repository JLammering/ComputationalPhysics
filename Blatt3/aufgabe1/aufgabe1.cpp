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
  int getEnergie(double H){
    return (-spin*H);
  }
  void changeZustand(){
    spin *= -1;
  }
};


int main() {
  double schritte = 100000;
  double beta = 1;
  double H =-5;
  ofstream myfile; //Daten abspeichern zum plotten mit plotRN.py
	myfile.open ("build/magnetisierung.txt");
  myfile << "#magnetisierung H \n";

  for (int i = 0; i <= 10000; i++) {
  H += 0.001;
  zustand alt(0);
  double sum = 0;
  for (int k = 0; k < schritte; k++) {
    sum += alt.getZustand();
    //cout << alt.getZustand()<<endl;
    zustand neu(alt.getZustand());
    double energiediff = neu.getEnergie(H) - alt.getEnergie(H);
    if(energiediff < 0){
      alt.changeZustand();
    }else{
      double zufallszahl = drand48();
      double boltzmann = exp(-beta*energiediff);
      //cout << energiediff << ' '<<zufallszahl<<" "<<boltzmann<<endl;
      if (zufallszahl<boltzmann) {
        alt.changeZustand();
      }
    }
  }
  double magnetisierung = sum/schritte;
  myfile << setprecision(4)<< magnetisierung << " " << H << endl;
}
myfile.close();
  return 0;
}
