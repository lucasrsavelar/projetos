#include "celular.hpp"

// TODO: Inicialize aqui sua variavel estatica. Caso tenha optado por essa
// solucao.

int Celular::global = 1;

Celular::Celular(std::string _modelo,
                 std::string _fabricante,
                 int _armazenamento,
                 int _memoria,
                 double _peso,
                 std::string _cor,
                 int _qtd,
                 float _valor) {
  // TODO: Implemente este metodo
 peso = _peso;
 fabricante = _fabricante;
 modelo = _modelo;
 armazenamento = _armazenamento;
 memoria = _memoria;
 cor = _cor;
 cor[0] = toupper(cor[0]);
 quantidade = _qtd;
 valor_unitario = _valor;
 codigo = global;
 
 global++;
}

bool Celular::operator<(const Celular& other) {
  // TODO: Implemente este metodo. 
  // Preste atencao no exemplo que a descricao utilizada na ordenacao considera
  // a fabricante antes do modelo do celular
  
  return false;
}

bool Celular::comparaCelular(const Celular& _cel1, const Celular& _cel2) {
      string cel1 = _cel1.fabricante + _cel1.modelo;
      string cel2 = _cel2.fabricante + _cel2.modelo;
      
      unsigned int i=0;
      while ( (i<cel1.length()) && (i<cel2.length()) )
  {
    if (tolower(cel1[i])<tolower(cel2[i])) return true;
    else if (tolower(cel1[i])>tolower(cel2[i])) return false;
    ++i;
  }
  return ( cel1.length() < cel2.length() );
}
 