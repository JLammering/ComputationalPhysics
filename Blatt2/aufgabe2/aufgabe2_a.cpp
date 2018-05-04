//============================================================================
// Name        : compuational_physics_b2.cpp
// Author      : henning
// Version     :
// Copyright   : Your copyright notice
// Description : Blatt2 in C++, Ansi-style
//============================================================================


#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
using namespace std;


// funktionen aus transformationsmethode
double verteilung1(double x){
	return (asin(x));
}


double verteilung2(double x){
	return (asin(0.5 + x / 2.0));
}


int main() {
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_real_distribution<> dist1(0,1);
	std::uniform_real_distribution<> dist2(-1,1);

	int anzahl = 1e5; // anzahl zufallszahlen
	double zahl;
	ofstream file;
	file.open ("build/random1.txt");
	for(int i = 0; i < anzahl; i++){
		double ran  = dist1(rng); // erzeuge gleichverteilte zufallszahl auf [0,1]
		zahl = verteilung1(ran); // transformiere so, dass cos verteilte zufallszahl erhalten wird
		file << zahl << endl;
	}
	file.close();

	file.open ("build/random2.txt");
	for(int j = 0; j < anzahl; j++){
			double ran = dist2(rng); // erzuge gleichverteilte zufallszahl auf [-1,1]
			zahl = verteilung2(ran); // transformiere so, dass cos verteilte zufallszahl erhalten wird
			ran  = dist2(rng);
			file << zahl << endl;
		}
		file.close();
		return 0;
}
