#ifndef PROCESSO_H
#define PROCESSO_H

#include <iostream>
using namespace std;

struct Processo {

int id, prioridade;
string nome;
Processo* next;

Processo(int _id = 0, string _nome = "default", int _prioridade = 0);
void imprimir_dados();

};

#endif