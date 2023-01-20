#include <iostream>
#include <vector>

using namespace std;

//Estrutura para manter controle dos índices
struct Indice {
  //Armazena o valor de um subvetor, bem como seus índices de início e fim
  float valor = 0;
  int start = 0, end = 0;
};

struct Solucao {
  //Armazena os índices e valores do prefixo do vetor, do sufixo, do seu total e o maior subvetor possível
  Indice pref, suf, soma, ssm;
};

//Implementação do SSM com dividir para conquistar
Solucao SSM(vector<float> &v, int ini, int fim);
//Função que efetivamente calcula o maior subvetor e seus índices
void RecuperaIndices(Solucao &sol, Solucao &esq, Solucao &dir);