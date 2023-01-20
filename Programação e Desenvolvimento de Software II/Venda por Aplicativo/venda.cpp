#include "venda.hpp"

#include <iomanip>

Venda::~Venda() {
  // TODO: Implemente este metodo
  /**
   * Aqui voce deve deletar os ponteiros contidos na lista m_pedidos
   */
   for(auto&& pedido : m_pedidos) {
     delete pedido;
}
}

void Venda::adicionaPedido(Pedido* p) {
  // TODO: Implemente este metodo
  m_pedidos.push_back(p);
}

void Venda::imprimeRelatorio() const {
    int i = 0;
    int numPedido = 1;
    float valorFinal;
  // TODO: Implemente este metodo
  /**
   * Aqui voce tem que percorrer a lista de todos os pedidos e imprimir o resumo
   * de cada um. Por ultimo, devera ser exibido o total de venda e a quantidade
   * de pedidos processados.
   */
   for (auto* pedido : m_pedidos) {
    valorFinal += pedido->calculaTotal();
    i++;
    string impressaoPedidos = pedido->resumo();
    cout << "Pedido " << numPedido << endl;
    cout << impressaoPedidos;
    numPedido++;
   }
   
   cout << "Relatorio de Vendas" << endl;
   cout << "Total de vendas: R$ " << setprecision(2) << fixed << valorFinal << endl;
   cout << "Total de pedidos: " << i << endl;
}