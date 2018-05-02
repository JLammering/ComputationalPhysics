//============================================================================
// Name        : aufgabe1.cpp
// Author      : Jasper Karl Lammering, Henning Ptaszyk, Timo Gräßer
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include <fstream>
#include <limits>
#include <string>


// #include "saw.h"


using namespace std;

class RNG{ //Oberklasse um die Funktion abspeichern für beide Generatorklassen schreiben zu können
public:
  virtual double getLittleRnd() = 0;
};

class LCG : public RNG{ //erbt von RNG
  private:
    uint32_t r_n, a, c, m;
  public:
    LCG(uint32_t r_0_eingabe, uint32_t a_eingabe, uint32_t c_eingabe, uint32_t m_eingabe){//Konstruktor
      r_n = r_0_eingabe;
      a = a_eingabe;
      c = c_eingabe;
      m = m_eingabe;
    }
    uint32_t getRnd(){//ganzzahlige Zufallszahl erhalten
      r_n = (a*r_n + c)%m;
      return r_n;
    }
    double getLittleRnd(){//Zufallszahl zwischen 0 und 1 erhalten
      return (getRnd()/(double)m);
    }
};

class XORshift : public RNG{ // erbt auch von RNG
  private:
    uint16_t a, b, c, y;
  public:
    XORshift(uint16_t a_eingabe, uint16_t b_eingabe, uint16_t c_eingabe, uint16_t y_eingabe){//Konstruktor
      a = a_eingabe;
      b = b_eingabe;
      c = c_eingabe;
      y = y_eingabe;
    }

    uint16_t getRnd(){//ganzzahlige Zufallszahl erhlaten nach XORshift
      y^=(y<<a);
      y^=(y>>b);
      return (y^=(y<<c));
    }
    double getLittleRnd(){//Zufallszahl zwischen 0 und 1 durch Division der Ganzzahligen durch das Maximum des 16-bit-Integer
      return (double)getRnd()/(double)(numeric_limits<uint16_t>::max());
    }
};

void abspeichern(string dateiname, RNG& generator, uint32_t anzahlWerte){
  ofstream myfile; //Daten abspeichern zum plotten mit plotRN.py
	myfile.open (dateiname);
	myfile << "# Rnd_numbers \n";
	for(uint32_t i=0; i<anzahlWerte; i++){
			myfile << generator.getLittleRnd() << "\n";
		}
	myfile.close();
}

uint16_t testPeriod(XORshift& rng){
  uint16_t start = rng.getRnd();//anfangswert
  uint16_t periode = 1;
  for (; rng.getRnd() != start; periode++) {}//bricht ab wenn Zufallsreihe wieder am Anfang ankommt
  return periode;
}



int main() {
  uint32_t anzahlWerte = 1e5;

  // LCG Generatoren mit verschiedenen Parametern
  LCG erster(1234, 20, 120, 6075);
  abspeichern("build/ersterGenerator.txt", erster, anzahlWerte);

  LCG zweiter(1234, 137, 187, 256);
  abspeichern("build/zweiterGenerator.txt", zweiter, anzahlWerte);

  LCG dritter(123456789, 65539, 0, 2147483648);
  abspeichern("build/dritterGenerator.txt", dritter, anzahlWerte);

  LCG vierter(1234, 16807, 0, 2147483647);
  abspeichern("build/vierterGenerator.txt", vierter, anzahlWerte);


  //Aufgabe d
  XORshift fifth(11, 1, 7, 123);
  abspeichern("build/fifthGenerator.txt", fifth, anzahlWerte);

  XORshift six(11, 4, 7, 123);
  abspeichern("build/sixGenerator.txt", six, anzahlWerte);

  //Aufgabe e
  ofstream otherfile;
  otherfile.open("build/Rekursionstest.txt");
  otherfile << "#b c periode \n";
  for (int b = 1; b <= 15; b++) {//zwei Schleifen um b und c zu variieren
    for (int c = 1; c <= 15; c++) {
      XORshift seveneleven(11, b, c, 123);//XORshift mit entsprechendem b und c initialisieren
      otherfile << testPeriod(seveneleven) << "\t";//bei festem b alle Perioden für
      // die verschiedenen c in eine Zeile der txt Datei schreiben 
    }
    otherfile << endl;//neue Zeile mit neuem b. Muss so gemacht werden um in der
    //python Datei ein 2d-Array zu erhalten, welches für pcolormesh gebraucht wird
  }
  otherfile.close();
	return 0;
}
