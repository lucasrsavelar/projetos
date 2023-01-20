#ifndef LISTA_PROCESSOS_H
#define LISTA_PROCESSOS_H

#include <iostream>
#include "Processo.hpp"
using namespace std;

struct ListaProcessos {

Processo* head = nullptr;
Processo* tail = nullptr;

void adicionar_processo(Processo* proc);
Processo* remover_processo_maior_prioridade();
Processo* remover_processo_menor_prioridade();
Processo* remover_processo_por_id(int id);
void imprimir_lista();

};

#endif