#include "Processo.hpp"

Processo::Processo(int _id, string _nome, int _prioridade) {
    id = _id;
    nome = _nome;
    prioridade = _prioridade;
}

void Processo::imprimir_dados() {
    cout << id << " " << nome << " " << prioridade << endl;
}