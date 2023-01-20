#ifndef FUNCOES
#define FUNCOES

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm> //Apenas para manipulação da string em si
#include <string>

using namespace std;
#define MAXTAM 10001
#define Troca(A,B) {string c = A; A = B; B = c;}

int returnID(char c, char* ordem);
string toLower(string s);
bool ehProibido(string s);
bool removeChar(char c);
bool ehMaior(string left, string right, char* ordem);
void Insercao(string* palavras, int Esq, int Dir, char* ordem);
void Particao(string* palavras, int Esq, int Dir, char* ordem, int tamParticao, int mediana);
void QuickSort(string* palavras, int numPalavras, char* ordem, int tamParticao, int mediana);

#endif