#ifndef FUNCOES
#define FUNCOES

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int funcaoDispercao(int identificadorUsuario, int tamTabela);

struct Email{

    //Funciona tanto como estrutura para emails quanto como nos das arvores
    string mensagem;
    int identificadorEmail, identificadorUsuario;
    Email* esq = nullptr;
    Email* dir = nullptr;

};

struct ArvoreBinaria {

    Email* raiz;
    bool foiRemovido = true; //Booleano util para a operacao de remocao

    void insercaoAuxiliar(Email* &e, string msg, int idEmail, int idUsuario);
    Email pesquisaAuxiliar(Email* e, int idEmail, int idUsuario);
    void Antecessor(Email *q, Email* &r) ;
    void remocaoAuxiliar(Email* &e, int idEmail, int idUsuario);
    void insereArvore(string msg, int idEmail, int idUsuario);
    void removeArvore(int idEmail, int idUsuario);
    Email Pesquisa(int idEmail, int idUsuario);

};

struct TabelaHash {

    ArvoreBinaria* Tabela;

    void inicializaTabela(int tamanhoTabela);
    void InsereHash(string msg, int idEmail, int identificadorUsuario, int tamTabela);
    bool RemoveHash(int idEmail, int identificadorUsuario, int tamTabela);
    Email PesquisaHash(int idEmail, int identificadorUsuario, int tamTabela);

};

#endif