//============================================================================
// Name        : praesi.cpp
// Author      : Jasper Karl Lammering
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <random>
#include <iostream>
#include <cmath>

using namespace std;

double wurzel1(double x){
	return 1/(sqrt(x))-1/(sqrt(1+x));
}

double wurzel2(double x){
	return 1/(sqrt((x)*(x+1))*(sqrt(x+1)+sqrt(x)));
}

double rel_err (double x, double y){
	return abs(1-x/y);
}


int main()
{
	for(int i=0; i<6; i++){


	double var = pow(10, i);
	//cout << "enter var: "<< endl;
	//cin >> var;
	cout <<var<<"  "<< wurzel1(var)<<"   "<<wurzel2(var)<< "   "<< rel_err(wurzel1(var), wurzel2(var))<<endl;
	}
	return 0;
}
