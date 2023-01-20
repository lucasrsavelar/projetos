#include "Ponto2D.hpp"

Ponto2D::Ponto2D(double _x, double _y) {
    this->x = _x;
    this->y = _y;
}

double Ponto2D::calcular_distancia(Ponto2D* ponto) {
    double dx = ponto->x - this->x;
    double dy = ponto->y - this->y;
    
    return sqrt(dx*dx + dy*dy);
}