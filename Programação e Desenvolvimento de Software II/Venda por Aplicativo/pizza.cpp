#include "pizza.hpp"

std::string Pizza::descricao() const {
  // TODO: Implemente este metodo.
  /*
   * Note que aqui voce deve retornar uma descricao detalhada da pizza.
   *
   * Exemplos:
   * 2X Pizza Calabresa, 4 pedacos e borda recheada.
   * 2X Pizza Calabresa, 4 pedacos sem borda recheada.
   */
   
   string quantidade = to_string(this->m_qtd);
   string num_pedacos = to_string(this->pedacos);
   string descBorda; 
   
   if(this->borda_recheada == true)
   descBorda = "e borda recheada.";
   
   else if(this->borda_recheada == false)
   descBorda = "e sem borda recheada.";
   
   string resumo = quantidade + "X Pizza " + this->sabor + ", " + num_pedacos + " pedacos " + descBorda + "\n";  
   
  return resumo;
}

Pizza::Pizza(const std::string& sabor,
             int pedacos,
             bool borda_recheada,
             int qtd,
             float valor_unitario) {
  // TODO: Implemente este metodo.
  this->sabor = sabor;
  this->pedacos = pedacos;
  this->borda_recheada = borda_recheada;
  this->m_qtd = qtd;
  this->m_valor_unitario = valor_unitario;
}