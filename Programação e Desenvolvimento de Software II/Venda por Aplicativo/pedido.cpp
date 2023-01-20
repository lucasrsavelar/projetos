#include "pedido.hpp"


Pedido::~Pedido() {
  // TODO: Implemente este metodo.
  /**
   * Aqui voce deve deletar os ponteiros contidos na lista m_produtos
   */
   for(auto&& produto : m_produtos) {
     delete produto;
}
}

void Pedido::setEndereco(const std::string& endereco) {
  // TODO: Implemente este metodo.
  this->m_endereco = endereco;
}

float Pedido::calculaTotal() const {
  // TODO: Implemente este metodo.
  float valorTotal = 0;
  for (auto prod : m_produtos) {
      int quantidade = prod->getQtd();
      float valor = prod->getValor();
      valorTotal += quantidade * valor;
  }
  return valorTotal;
}

void Pedido::adicionaProduto(Produto* p) {
  // TODO: Implemente este metodo.
  m_produtos.push_back(p);
}

std::string Pedido::resumo() const {
  // TODO: Implemente este metodo.
  /**
   * Aqui voce deve percorrer a lista de produtos para criar um resumo completo
   * do pedido. A cada iteracao, utilize o metodo descricao de cada produto para
   * montar o resumo do pedido. Por fim, adicione o endereco de entrega.
   *
   */
   string resumoPedidos;
   
   for (auto* prod : m_produtos) {
    resumoPedidos += prod->descricao();
} 
  resumoPedidos += "Endereco: " + this->m_endereco;
  resumoPedidos += "\n";
  return resumoPedidos;
}