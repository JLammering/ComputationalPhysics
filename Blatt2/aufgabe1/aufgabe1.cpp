//============================================================================
// Name        : aufgabe1.cpp
// Author      : Jasper Karl Lammering, Henning Ptaszyk, Timo Gräßer
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include <fstream>


// #include "saw.h"


using namespace std;

class LCG{
  private:
    uint32_t r_n, a, c, m;
  public:
    LCG(uint32_t r_0_eingabe, uint32_t a_eingabe, uint32_t c_eingabe, uint32_t m_eingabe){
      r_n = r_0_eingabe;
      a = a_eingabe;
      c = c_eingabe;
      m = m_eingabe;
    }
    uint32_t getRnd(){
      r_n = (a*r_n + c)%m;
      return r_n;
    }
    double getLittleRnd(){
      return (getRnd()/(double)m);
    }
};

void abspeichern(string dateiname, LCG generator, uint32_t anzahlWerte){
  ofstream myfile; //Daten abspeichern zum plotten mit plotRN.py
	myfile.open (dateiname);
	myfile << "# Rnd_numbers \n";
	for(uint32_t i=0; i<anzahlWerte; i++){
			myfile << generator.getLittleRnd() << "\n";
		}
	myfile.close();
}

int main() {
  uint32_t anzahlWerte = 1e5;

  LCG erster(1234, 20, 120, 6075);
  abspeichern("build/ersterGenerator.txt", erster, anzahlWerte);

  LCG zweiter(1234, 137, 187, 256);
  abspeichern("build/zweiterGenerator.txt", zweiter, anzahlWerte);

  LCG dritter(123456789, 65539, 0, 2147483648);
  abspeichern("build/dritterGenerator.txt", dritter, anzahlWerte);

  LCG vierter(1234, 16807, 0, 2147483647);
  abspeichern("build/vierterGenerator.txt", vierter, anzahlWerte);
	return 0;
}
