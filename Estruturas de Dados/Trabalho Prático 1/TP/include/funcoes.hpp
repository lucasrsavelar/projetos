#ifndef FUNCOES
#define FUNCOES

#include <iostream>
#include <fstream>
#include <sstream>

//Usada na funcao que ordena jogadores
#define Troca(A,B) {Jogador c = A; A = B; B = c;}

using namespace std;

//Estrutura de um Jogador. Um combo = uma jogada
struct Jogador {
   string nome, combo = "NA";
   string mao[5];
   int dinheiro = 0, aposta = 0, maiorCartaCombo = 0, maiorCartaCombo2 = 0, maiorCartaForaCombo = 0, IDCombo = 0;
};

int maiorCartaCombo(string* mao, string combo);
int maiorCartaForaCombo(string* mao, string combo);
int segundoPar(string* mao);
string analisaMao(string* mao);
int atribuiID(string combo);
int determinarVencedor(Jogador* jgdr, int numParticipantes);
void resetaJogadores(Jogador* jgdr, int numJogadores);
void ordenaJogadores(Jogador* jogadores, int participantes);

#endif