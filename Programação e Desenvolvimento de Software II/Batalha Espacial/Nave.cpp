#include "Nave.hpp"

Nave::Nave(Ponto2D _posicao, double _forca) {
    posicao = _posicao;
    forca = _forca;
}

void Nave::mover(double dx, double dy) {
    this->posicao.x += dx;
    this->posicao.y += dy;
}

double Nave::calcular_distancia(Nave* nave) {
    double dx = nave->posicao.x - this->posicao.x;
    double dy = nave->posicao.y - this->posicao.y;
    return sqrt(dx*dx + dy*dy);

}

Nave* Nave::determinar_nave_mais_proxima(Nave** naves, int n) {

    Nave* maisprox = nullptr;
    int i = 0;
    double menor = 1000, dist = 0;
    
    for(i = 0; i < n; i++)
    {
        dist = calcular_distancia(naves[i]);
        if(dist < menor && dist != 0) {
            menor = dist;
            maisprox = naves[i];
        } 
    }
    return maisprox;
}

void Nave::atacar(Nave** naves, int n) {
    
    Nave* alvo = determinar_nave_mais_proxima(naves, n);
    double d = calcular_distancia(alvo);
    
    double dano = (100/d) * forca;
    
    if(dano > 30) {
        dano = 30;
    }
    
    alvo->energia -= dano;
    
    if(alvo->energia <= 50) {
        cout << "Energia baixa!" << endl;
    }
}

void Nave::imprimir_status() {
    
    cout << posicao.x << " " << posicao.y << " " << energia << endl;
    
}