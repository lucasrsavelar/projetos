#include "loja.hpp"

int main() {

  //Declaração de variáveis necessárias e leitura do número de casos de teste
  int numTestes = 0, numRolos = 0, testes = 0, i = 0, aux = 0;
  cin >> numTestes;

  //Laço para repetir enquanto houver casos de teste
  for(testes = 0; testes < numTestes; testes++) {

    //Declaração dos vetores necessários
    vector<int> rolos;
    vector<int> tam;

    cin >> numRolos;
    for(i = 0; i < numRolos; i++) {
      cin >> aux;
      rolos.push_back(aux);
    }

    tam.push_back(rolos[0]);

    //Adaptação do enunciado do problema. Ao invés de considerar todas as possibilidades através de
    //chamadas recursivas que optam por incluir ou não o rolo atual, todos os rolos existentes são
    //"considerados". Para isso, ele é adicionado tanto no início quanto no final do vetor.
    //Se um rolo é maior do que o seguinte ou menor do que o anterior, contrariando o enunciado, ele é
    //desconsiderado pela função LDS.

    //Desse modo, todos os rolos são calculados, mas nem todos são efetivamente considerados.
    for(i = 1; i < rolos.size(); i++) {
            tam.push_back(rolos[i]);
            tam.insert(tam.begin(), rolos[i]);
    }

    //A função LDS calcula a maior subsequência decrescente do vetor tam (Longest Decreasing Subsequence), 
    //e o valor é impresso
    int max = LDS(tam);
    cout << max << endl;

  }
  
  return(0);
}