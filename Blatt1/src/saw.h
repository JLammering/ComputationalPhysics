//============================================================================
// Name        : saw.cpp
// Author      : Jasper Karl Lammering
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <random>
#include <iostream>
#include <cmath>
#include <cstring>
#include <numeric>
#include <fstream>

using namespace std;

struct position{
	int x;
	int y;
	void move(int x_step, int y_step){
		x += x_step;
		y += y_step;
	}
	void initialise(int ursprung){
		x = ursprung;
		y = ursprung;
	}
	void print_position(){
		cout << "x = " << x << ", y = " << y << endl;
	}
	double quad_abstand_zum_ursprung(int ursprung){
		return pow(x-ursprung, 2) + pow(y-ursprung, 2);
	}

};

void saw() {


	const int cluster = 1e5;

	double abstaende[cluster] = {0};

	mt19937 rng; //erzeugt mersenne twister 19937 generator
	rng.seed(random_device()()); //setzt seed (”startwert”) zufällig
	uniform_real_distribution<> dist (0 ,1); //erzeugt Verteilung von 0 bis 1

	double R_N[11] = {0};

	for(int N=10; N<=60; N+=5){//verschiedene N

	for(int p = 0; p < cluster; p++){//viele Iterationen pro N für Statistik

	int gitter[2*N+1][2*N+1]; // Gitter bauen
	memset(gitter, 0, sizeof(gitter)); // Gitter mit Nullen belegen

	position punkt;
	punkt.initialise(N);
	gitter[N][N] = 1;//Ursprung belegen




	for(int i=0; i<N; i++){ // selfavoiding random Walk mit N schritten
		double rand_number = dist(rng); // neue Zufallszahl für jeden Schritte

		if(gitter[punkt.x-1][punkt.y] != 0 && gitter[punkt.x+1][punkt.y] != 0 && gitter[punkt.x][punkt.y-1] != 0 && gitter[punkt.x][punkt.y+1] != 0){
			break;
		}//überprüfung ob Punkt in Sackgasse

		if(rand_number >= 0 && rand_number < 0.25){//je nach Intervall in der Zufallszahl liegt, andere Richtung für Schritt
			if(gitter[punkt.x-1][punkt.y] == 0){//Schritt möglich
				punkt.move(-1, 0);
				gitter[punkt.x][punkt.y] = i+2; // in Gitter Weg abspeichern
			}else {
				i -= 1;
			}
		}else if(rand_number >= 0.25 && rand_number < 0.5){
				if(gitter[punkt.x][punkt.y+1] == 0){
					punkt.move(0, 1);
					gitter[punkt.x][punkt.y] = i+2;
			}else {
				i -= 1;
			}
		}else if(rand_number >= 0.5 && rand_number < 0.75){
			if(gitter[punkt.x+1][punkt.y] == 0){
				punkt.move(1, 0);
				gitter[punkt.x][punkt.y] = i+2;
			}else {
				i -= 1;
			}
		}else if(rand_number >= 0.75 && rand_number <=1){
			if(gitter[punkt.x][punkt.y-1] == 0){
				punkt.move(0, -1);
				gitter[punkt.x][punkt.y] = i+2;
			}else {
				i -= 1;
			}
		}
	}
	abstaende[p] = punkt.quad_abstand_zum_ursprung(N); // r_N^2 für jede Iteration in array abspeichern
//	for (int i = 0; i < 2*N+1; ++i)
//	    {
//	        for (int j = 0; j < 2*N+1; ++j)
//	        {
//	            std::cout << gitter[j][i] << ' ';
//	        }
//	        std::cout << std::endl;
//	    }
//	cout << abstaende[p] << endl;
	}

	double mittelwert = accumulate(abstaende, abstaende+cluster, 0.0)/cluster; //R_N^2 berechnen
	R_N[N/5 - 2] = pow(mittelwert, 0.5); //R_N in array abspeichern
	cout << "N= "<< N << "quadratischer mittelwert = " << mittelwert << " Wurzel = " << pow(mittelwert, 0.5) << endl;//ergebnisse ausgeben
	}

	ofstream myfile; //Daten abspeichern zum plotten mit plotRN.py
	myfile.open ("mittlClustergroesse.txt");
	myfile << "# N R_N \n";
	for(int i=0; i<11; i++){
			myfile << (i+2)*5 << " " <<  R_N[i] << "\n";
		}
	myfile.close();

}
