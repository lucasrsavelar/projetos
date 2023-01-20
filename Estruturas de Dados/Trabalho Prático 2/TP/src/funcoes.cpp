#include "funcoes.hpp"

//Funcao que retorna o ID de cada letra dada a nova ordem. Na ordem alfabética, por exemplo, o A tem id = 26
int returnID(char c, char* ordem) {

    int i = 0;
    for(i = 0; i < 26; i++) {
        //Loop que percorre o array de char e retorna a posicao em que o char passado como parameto esta
        if(ordem[i] == c)
        return i;
    }

    //Se nao for uma letra, retorna o valor ascii do char
    return int(c);
}

//Funcao que transforma cada char de uma string em minusculo
string toLower(string s) {

    transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c){ return tolower(c); });

        return s;
}

 //Verifica se uma string eh algum dos sinais proibidos
bool ehProibido(string s) {

    if(s == "," || s == "." || s == "!" || s == "?" || s == ":" || s == ";" || s == "_")
    return true;

    return false;
}

//Verifica se algum char de uma string eh um dos sinais proibidos
bool removeChar(char c) {

    if(c == ',' || c == '.' || c == '!' || c == '?' || c == ':' || c == ';' || c == '_')
    return true;

    return false;
}

//Compara a primeira string passada como parametro (left) com a segunda (right) e retorna se a primeira eh maior
//que a segunda, dada a nova ordem passada
bool ehMaior(string left, string right, char* ordem) {

    int pos = 0;
    //Obtem o ID da primeira letra de cada string
    int IDleft = returnID(left[pos], ordem);
    int IDright = returnID(right[pos], ordem);
    //Obtem o tamanho da menor string passada como parametro
    int menor =  min(left.size(), right.size());

    if(IDleft == IDright) {
        pos = 1;
        //Se a primeira letra das string for igual, verifica o ID da proxima letra ate que sejam diferentes
        //e enquanto nao acaba a string menor
        while(IDleft == IDright && pos <= menor - 1) {
            IDleft = returnID(left[pos], ordem);
            IDright = returnID(right[pos], ordem);
            pos++;
        }

        //Se a string menor eh a da esquerda e todas as letras comparadas sao iguais, entao left eh maior
        //Exemplo: casa e casar, carro e carros
        if(IDleft == IDright && left.size() == menor)
        return true;
    }

    //Se o ID da atual letra da string left for maior que o da right, retorna true
    if(IDleft > IDright)
    return true;

    else
    return false;
}

//Algoritmo do Insertion Sort
void Insercao(string* palavras, int Esq, int Dir, char* ordem) {
    int i = Esq + 1;
    int j;
    string t;
    
    while(i <= Dir) {
        t = palavras[i];
        j = i;
        while((j > Esq) && (!ehMaior(palavras[j-1], t, ordem))) {
        //A funcao ehMaior eh usada negada pois ao inves de se ordenar de acordo com chaves ascendentes, quero
        //ordenar pelos maiores IDs. Ou seja, na ordem alfabetica, quero que o A, com ID = 26, venha primeiro
            palavras[j] = palavras[j-1];
            j--;
            
        }
        
        palavras[j] = t;
        i++;
    }
}

//Algorimo da Particao do QuickSort
void Particao(string* palavras, int Esq, int Dir, char* ordem, int tamParticao, int mediana) {

    int tam = Dir - Esq + 1;
    if(Esq >= Dir)
    return;

    //Se a particao for menor do que o parametro passado, chama o Insert Sort ao inves de uma nova Particao
    if(tam <= tamParticao) {
        Insercao(palavras, Esq, Dir, ordem);
        return;
    }

    string pivo;

    //Tratamento para quando a medianda de M elementos eh maior que o tamanho da particao
    if(tamParticao < mediana)
    pivo = palavras[(Esq + Dir)/2];

    //Caso contrario, aplica a mediana de M elementos
    else {
        string med[mediana];
        int a = 0, b = Esq;

        //Pega os M primeiros valores do array de palavras
        for(a = 0; a < mediana; a++, b++)
            med[a] = palavras[b];

        //Ordena o array med com as M primeiras palavras
        Insercao(med, 0, mediana - 1, ordem);

        //Pega o pivo
        pivo = med[(mediana-1)/2];
    }

    string t;
    int i = Esq - 1;
    int j = Dir + 1;
    while(true) {
        while(!ehMaior(pivo, palavras[++i], ordem));
        while(!ehMaior(palavras[--j],pivo, ordem));
        //Uso da funcao ehMaior negada, como ja explicado em Insercao
        if(i >= j)
        break;


        Troca(palavras[i], palavras[j]);
    }
    
    Particao(palavras, Esq, j, ordem, tamParticao, mediana);
    Particao(palavras, j+1, Dir, ordem, tamParticao, mediana);
  
}

//Algoritmo do QuickSort, que funciona chamando a Particao
void QuickSort(string* palavras, int numPalavras, char* ordem, int tamParticao, int mediana) {
   Particao(palavras, 0, numPalavras - 1, ordem, tamParticao, mediana);
}