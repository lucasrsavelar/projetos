#include <iostream>
//using std::cout;
//using std::endl;
using namespace std;

int main(){

    // 1) Declare uma variável do tipo inteiro e atribua o valor '10'
    int x = 10;

    // 2) Declare um ponteiro para inteiros e inicialize com valor nulo
    int *pointer = nullptr;

    // 3) Declare um vetor de inteiros e inicialize com valores de 9 a 0 (nessa ordem)
    int v[10], i = 0, j = 9;
    for(i = 0; i < 10; i++, j--) {
        v[i] = j;
    }

    // 4) Imprima o ENDEREÇO da variável declarada em (1)
    cout << &x << endl;

    // 5) Imprima o VALOR da variável declarada em (1)
    cout << x << endl;

    // 6) Imprima o ENDEREÇO da variável declarada em (2)
    cout << &pointer << endl;
    
    // 7) Imprima o VALOR da variável declarada em (2)
    cout << pointer << endl;

    // 8) Imprima o ENDEREÇO da variável declarada em (3)
    cout << &v << endl;

    // 9) Imprima o ENDEREÇO da primeira posição da variável declarada em (3)
    cout << &v[0] << endl;

    // 10) Imprima o VALOR da primeira posição da variável declarada em (3)
    cout << v[0] << endl;

    // 11) Atribua o ENDEREÇO da variável declarada em (1) à variável declarada em (2)
    pointer = &x;

    // 12) Imprima o VALOR da variável declarada em (2)
    cout << pointer << endl;

    // 13) Imprima o VALOR guardado no ENDEREÇO apontado por (2)
    cout << *pointer << endl;

    // 14) Imprima o resultado da comparação do ENDEREÇO de (1) e do VALOR de (2)
    cout << (&x == pointer) << endl;

    // 15) Coloque o VALOR '5' no ENDEREÇO apontado por (2)
    *pointer = 5;

    // 16) Imprima o VALOR da variável declarada em (1)
    cout << x << endl;

    // 17) Atribua o ENDEREÇO da variável (3) à variável declarada em (2)
    pointer = &v[0];

    // 18) Imprima o VALOR da variável declarada em (2)
    cout << pointer << endl;

    // 19) Imprima o VALOR guardado no ENDEREÇO apontado por (2)
    cout << *pointer << endl;

    // 20) Atribua o ENDEREÇO da primeira posição de (3) à variável declarada em (2)
    pointer = &v[0];

    // 21) Imprima o VALOR da variável declarada em (2)
    cout << pointer << endl;

    // 22) Imprima o VALOR guardado no ENDEREÇO apontado por (2)
    cout << *pointer << endl;

    // 23) Multiplique todos os valores do vetor declarado em (3) por '10', porém manipulando apenas a variável (2)
    for(i = 0; i < 10; i++) {
    *(pointer+i) *= 10;
    }
    // 24) Imprima os elementos de (3) a partir variável do vetor utilizando a notação [] (colchetes)
    for(i = 0; i < 10; i++) {
    if(i != 9) {    
    cout << v[i] << " ";
    }
    else {
    cout << v[i] << endl;
    }
    }

    // 25) Imprima os elementos de (3) a partir variável do vetor utilizando a notação ponteiro/deslocamento
    for(i = 0; i < 10; i++) {
    if(i != 9) {
    cout << *(v+i) << " ";
    }
    else {
    cout << v[i] << endl;
    }
    }
    

    // 26) Imprima os elementos de (3) utilizando a variável (2) e a notação ponteiro/deslocamento
    for(i = 0; i < 10; i++) {
    if(i != 9) {
    cout << *(pointer+i) << " ";
    }
    else {
    cout << *(pointer+i) << endl;
    }
    }
    
    // 27) Atribua o ENDEREÇO da quinta posição de (3) à variável declarada em (2)
    pointer = &v[4];

    // 28) Imprima o VALOR da variável declarada em (2)
    cout << pointer << endl;

    // 29) Imprima o VALOR guardado no ENDEREÇO apontado por (2)
    cout << *pointer << endl;

    // 30) Imprima o VALOR guardado no ENDEREÇO do ponteiro (2) decrementado de 4
    cout << *(pointer - 4) << endl;

    // 31) Declare um ponteiro para ponteiro e o inicialize com o ENDEREÇO da variável (2)
    int **ptrtopointer = &pointer;

    // 32) Imprima o VALOR da variável declarada em (31)
    cout << ptrtopointer << endl;

    // 33) Imprima o ENDEREÇO da variável declarada em (31)
    cout << &ptrtopointer << endl;

    // 34) Imprima o VALOR guardado no ENDEREÇO apontado por (31)
    cout << *ptrtopointer << endl;

    // 35) Imprima o VALOR guardado no ENDEREÇO do ponteiro apontado por (31)
    cout << **ptrtopointer << endl;
    
    return 0;
}