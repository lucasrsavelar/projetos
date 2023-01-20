#include "venda.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

void Venda::adicionaCelular(const Celular& celular) {
  // TODO: Implemente este metodo
  m_celulares.push_back(celular);
}

void Venda::ordena() {
  // TODO: Implemente este metodo
  // Preste atencao no exemplo que a descricao utilizada na ordenacao considera
  // a fabricante antes do modelo do celular
  
  m_celulares.sort(Celular::comparaCelular);
}

void Venda::recarregaEstoque(int cod, int qtd) {
  // TODO: Implemente este metodo
  list<Celular>::iterator it;
  for (it = m_celulares.begin(); it != m_celulares.end(); ++it) {
      if(it->codigo == cod)
      it->quantidade += qtd;
  }
}

void Venda::efetuaVenda(int cod, int qtd) {
  // TODO: Implemente este metodo
  /**
   * Observe na descricao do enunciado que nao e permita a venda de um modelo
   * cuja quantidade seja maior que a quantidade atual em estoque.
   * Ex: Se existirem apenas 5 celulares Motorola Moto G50 em estoque, vendas a
   * partir de 6 unidades devem ser ignoradas.
   */
  list<Celular>::iterator it;
  for (it = m_celulares.begin(); it != m_celulares.end(); ++it) {
      if(it->codigo == cod) {
          if(it->quantidade < qtd)
          return;
          
          else {
          it->quantidade -= qtd;
          }
      }
  }
   
}

void Venda::aplicaDesconto(const std::string& fabricante, float desconto) {
  // TODO: Implemente este metodo
  list<Celular>::iterator it;
  for (it = m_celulares.begin(); it != m_celulares.end(); ++it) {
      if(it->fabricante == fabricante)
      {
          float valorDesconto = (it->valor_unitario * desconto) / float(100);
          it->valor_unitario -= valorDesconto;
      }
  }
}

void Venda::removeModelo(int cod) {
  // TODO: Implemente este metodo
  list<Celular>::iterator it;
  for (it = m_celulares.begin(); it != m_celulares.end(); ++it) {
      if(it->codigo == cod) {
      it->quantidade = -1;
      }
  }
}

void Venda::imprimeEstoque() const {
  // TODO: Implemente este metodo.
  /**
   * Aqui voce tera que imprimir a lista de celulares em estoque com as
   * restricoes descritas no enunciado do problema. Notem no exemplo que a
   * primeira letra da cor do celular fica maiuscula. Outra coisa, se houver
   * apenas um item em estoque de determinado modelo de celular, voce tera que
   * imprimir '1 restante' e nao '1 restantes'. Por ultimo, apenas modelos de
   * celulares com pelo menos um item em estoque deverao ser exibidos.
   */
  for (const Celular & celular : m_celulares) {
      
      float peso = celular.peso * 1000;
      
      if(celular.quantidade > 0) {
          
          
         cout << setprecision(0) << fixed << celular.fabricante << " " << celular.modelo << ", " << celular.armazenamento << "GB" << ", " <<
         celular.memoria << "GB RAM" << ", " << peso << " " << "gramas" << ", " << celular.cor << ", ";
         
         if(celular.quantidade == 1)
         cout << celular.quantidade << " " << "restante" << ", " << "R$" << setprecision(2) << fixed << celular.valor_unitario  << endl;
         
         else {
         cout << celular.quantidade << " " << "restantes" << ", " << "R$" << setprecision(2) << fixed << celular.valor_unitario  << endl;
         }
         
     }
  }
 
}