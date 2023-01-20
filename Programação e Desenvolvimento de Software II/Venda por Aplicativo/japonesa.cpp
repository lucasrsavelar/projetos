#include "japonesa.hpp"

std::string Japonesa::descricao() const {
  // TODO: Implemente este metodo.
  /*
   * Note que aqui voce deve retornar uma descricao detalhada da comida
   * japonesa.
   *
   * Exemplos:
   * 1X Comida japonesa - Combo 1, 4 sushis, 5 temakis e 6 hots.
   * 1X Comida japonesa - Combo 2, 5 sushis, 6 temakis e 8 hots.
   */
   
   string quantidade = to_string(this->m_qtd);
   string numSushis = to_string(this->sushis);
   string numTemakis = to_string(this->temakis);
   string numHots = to_string(this->hots);
   
   string resumo = quantidade + "X Comida japonesa - " + this->combinado + ", " + numSushis + " sushis, " +
                   numTemakis + " temakis e " + numHots + " hots." + "\n";
   
  return resumo;
}

Japonesa::Japonesa(const std::string& combinado,
                   int sushis,
                   int temakis,
                   int hots,
                   int qtd,
                   float valor_unitario) {
  // TODO: Implemente este metodo.
  this->combinado = combinado;
  this->sushis = sushis;
  this->temakis = temakis;
  this->hots = hots;
  this->m_qtd = qtd;
  this->m_valor_unitario = valor_unitario;
}