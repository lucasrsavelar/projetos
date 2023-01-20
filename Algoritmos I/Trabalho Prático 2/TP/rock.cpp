#include "rock.hpp"

void RecuperaIndices(Solucao &sol, Solucao &esq, Solucao &dir) {

  //Cálculo do prefixo da solução
  //Para isso, verifica se o total da esquerda + prefixo da direita é maior do que o prefixo da esquerda
  if(esq.soma.valor + dir.pref.valor > esq.pref.valor) {
      //Se for, atualiza o valor e os índices do prefixo da solução
      sol.pref.valor = esq.soma.valor + dir.pref.valor;
      sol.pref.start = esq.pref.start;
      sol.pref.end = dir.pref.end;
    }

    else {
      //Caso contrário, o prefixo da solução é o prefixo da esquerda
      sol.pref = esq.pref;
    }

    //Cálculo do sufixo da solução
    //Para isso, verifica se o total da direita + sufixo da esquerda é maior do que o sufixo da direita
    if(dir.soma.valor + esq.suf.valor > dir.suf.valor) {
        //Se for, atualiza o valor e os índices do sufixo da solução
        sol.suf.valor = dir.soma.valor + esq.suf.valor;
        sol.suf.start = esq.suf.start;
        sol.suf.end = dir.suf.end;
    } 
    
    else {
        //Caso contrário, o sufixo da solução é o sufixo da direita
        sol.suf = dir.suf;
    }

    //Soma total do vetor é a soma do total da esquerda com o total da direita
    sol.soma.valor = dir.soma.valor + esq.soma.valor;
    //A soma do vetor inicia-se no começo da esquerda e termina no fim da direita
    sol.soma.start = esq.soma.start;
    sol.soma.end = dir.soma.end;

    //Sequência de comparações para descobrir a soma máxima
    //O uso do "maior ou igual" é importante em casos como: 1 2 3 0. A resposta precisa incluir o 0

    //Para isso, realiza comparações entre o sufixo da solução, o prefixo da solução, o maior subvetor da 
    //esquerda, o maior subvetor da direita e a soma total da solução

    //Verifica se a soma máxima da solução é o sufixo da solução
    if(sol.suf.valor >= sol.pref.valor && sol.suf.valor >= sol.soma.valor && 
       sol.suf.valor >= esq.ssm.valor && sol.suf.valor >= dir.ssm.valor)
        sol.ssm = sol.suf;
    
    //Verifica se a soma máxima da solução é o prefixo da solução
    else if (sol.pref.valor >= sol.suf.valor && sol.pref.valor >= sol.soma.valor &&
             sol.pref.valor >= esq.ssm.valor && sol.pref.valor >= dir.ssm.valor)
        sol.ssm = sol.pref;

    //Verifica se a soma máxima da solução é a soma máxima da esquerda 
    else if (esq.ssm.valor >= sol.pref.valor && esq.ssm.valor >= sol.soma.valor &&  
             esq.ssm.valor >= sol.suf.valor && esq.ssm.valor >= dir.ssm.valor)
        sol.ssm = esq.ssm;

    //Se nenhum dos casos acima é verdadeiro, então a soma máxima da solução é a soma máxima da direita
    else {
      sol.ssm = dir.ssm;
    }

    //Finalmente, verifica se existe uma solução que cruza o meio do vetor e, portanto, abrange direita e esquerda. 
    //Para isso, verifica se a soma do sufixo da esquerda com o prefixo da direita é maior que a soma máxima atual da solução
    if(esq.suf.valor + dir.pref.valor > sol.ssm.valor) {
      //Se for, atualiza os valores da soma máxima e os índices
      sol.ssm.valor = esq.suf.valor + dir.pref.valor;
      sol.ssm.start = esq.suf.start;
      sol.ssm.end = dir.pref.end;
    }
}

Solucao SSM(vector<float> &v, int ini, int fim) {

  Solucao sol;

  //Se início e fim são iguais, é um vetor com um único elemento, logo basta retornar seu valor e índices
  if(ini == fim) {
    Indice index;
    index.valor = v[ini];
    index.start = index.end = ini;
    sol.pref = sol.suf = sol.soma = sol.ssm = index;
  }

  else {
    int meio = (ini + fim)/2;

    //Chamada recursiva para cada metade do vetor
    Solucao esq = SSM(v, ini, meio);
    Solucao dir = SSM(v, meio + 1, fim);

    //Chamada da função que calcula valores e índices
    RecuperaIndices(sol, esq, dir);
  }

  //Retorno da solução
  return sol;

}