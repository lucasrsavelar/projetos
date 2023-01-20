#include "hamburguer.hpp"

std::string Hamburguer::descricao() const {
  // TODO: Implemente este metodo.
  /*
   * Note que aqui voce deve retornar uma descricao detalhada do Hamburguer.
   *
   * Exemplos:
   * 1X Hamburguer X-tudo artesanal.
   * 1X Hamburguer X-tudo simples.
   */
   
   string quantidade = to_string(this->m_qtd);
   string descBurg;
   
   if(this->artesanal == true)
   descBurg = "artesanal.";
   
   else if(this->artesanal == false)
   descBurg = "simples.";
   
   string resumo = quantidade + "X Hamburguer " + this->tipo + " " + descBurg + "\n";
   
  return resumo;
}

Hamburguer::Hamburguer(const std::string& tipo,
                       bool artesanal,
                       int qtd,
                       float valor_unitario) {
  // TODO: Implemente este metodo.
  this->tipo = tipo;
  this->artesanal = artesanal;
  this->m_qtd = qtd;
  this->m_valor_unitario = valor_unitario;
}