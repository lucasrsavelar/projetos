#include "loja.hpp"

//Função para verificar maior elemento de um array
int maiorElemento(int tam[], int size) {
    int i = 0, maior = 0;
    //Loop simples que procura o maior elemento por cada posição do array
    for (i = 0; i < size; i++)
        if(tam[i] > maior)
            maior = tam[i];

    return maior;
}

//Adaptação do algoritmo de LIS para calcular a maior subsequência decrescente -> Longest Decreasing Subsequence
int LDS(vector<int> tam) {
    //Array auxiliar da programação dinâmica
    int lds[tam.size()];
    lds[0] = 1;
 
    //Para cada rolo,
    for (int i = 1; i < tam.size(); i++) {
        lds[i] = 1;
        //verifica a maior subsequencia incluindo esse rolo
        for (int j = 0; j < i; j++)
            //se encontrar um rolo menor do que o ultimo da subsequencia e adição desse rolo aumentar a
            //extensão da subsequência, adiciona o rolo e incrementa o tamanho da maior subsequência
            //incluindo o rolo de índice i
            if (tam[i] < tam[j] && lds[i] < lds[j] + 1)
                lds[i] = lds[j] + 1;
    }
 
    //Retorna o valor da maior subsequência possível
    return maiorElemento(lds, tam.size());
}
