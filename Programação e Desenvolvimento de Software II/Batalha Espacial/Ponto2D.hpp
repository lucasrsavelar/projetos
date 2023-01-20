#ifndef PONTO2D_H
#define PONTO2D_H

#include <iostream>
#include <cmath>

using namespace std;

struct Ponto2D {

double x;
double y;

Ponto2D(double _x = 0, double _y = 0);
double calcular_distancia(Ponto2D* ponto);

};

#endif