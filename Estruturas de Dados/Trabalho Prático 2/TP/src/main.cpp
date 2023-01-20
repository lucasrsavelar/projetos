#include "funcoes.hpp"

int main(int argc, char** argv) {

    int i = 0, mediana = 0, tamParticao = 0;
    string output = " ", inicioTexto, inicioOrdem, input;

    //Leitura dos parametros passados na linha de comando
    for (i = 1; i < argc; i+=2) {
        if(string(argv[i]) == "-i" || string(argv[i]) == "-I")
        input = argv[i+1];

        else if(string(argv[i]) == "-m" || string(argv[i]) == "-M")
        mediana = atoi(argv[i+1]);

        else if(string(argv[i]) == "-s" || string(argv[i]) == "-S")
        tamParticao = atoi(argv[i+1]);

        else if(string(argv[i]) == "-o" || string(argv[i]) == "-O")
        output = argv[i+1];
    }

    //Tratamentos para o caso de argumentos de mediana e particao invalidos
    if(mediana <= 0)
    mediana = 1;

    if(tamParticao <= 0)
    tamParticao = 1;

    //Tratamento para o caso de não fornecimento do argumento de arquivo de saida
    if(output == " ")
    output = "saida.txt";

    //Arquivos de entrada e saida
    ifstream entrada(input, ios::in);
    ofstream saida(output);

    entrada >> inicioOrdem;
     
    //Array que contem a nova ordem passada, sendo que a primeira letra eh a de maior indice e vice versa
    char ordem[26], c;
    for(i = 25; i >= 0; i--) {
        entrada >> c;
        c = tolower(c);
        ordem[i] = c;
    }

    entrada >> inicioTexto;

    //Inicializa o array de palavras com espacos em branco em todas as posicoes
    string palavras[MAXTAM];
    for(i = 0; i < MAXTAM; i++)
    palavras[i] = " ";

    i = 0;
    string aux;
    //Leitura do arquivo de entrada, enquanto ha o que ser lido
    while(!entrada.eof()) {

        //Coloca a palavra na posicao i
        entrada >> palavras[i];

        //Se a palavra for uma string proibida, eh substituida por um espaco em branco
        if(ehProibido(palavras[i]))
        palavras[i] = " ";

        else {
            //Verifica os sinais proibidos no final da string e, enquanto existirem, eles sao removidos
            if(removeChar(palavras[i].back())) {
                while(removeChar(palavras[i].back()))
                palavras[i].pop_back();
            }

            //Transforma a palavra em minuscula e acrescenta o indice
            palavras[i] = toLower(palavras[i]);
            i++;
        }
    }

    i = 0;
    int numPalavras = 0;
    //Conta o numero de palavras
    for(i = 0; palavras[i] != " "; i++)
    numPalavras++;

    //Chama o QuickSort para ordenar o array de palavras
    QuickSort(palavras, numPalavras, ordem, tamParticao, mediana);

    i = 0;
    int repeticoes = 1;
    //Loop para imprimir as palavras ordenadas e o numero de repeticoes na saida
    for(i = 0; palavras[i] != " "; i++) {
        //Se a proxima palavra for igual a atual, acrescenta o numero de repeticoes
       if(palavras[i] == palavras[i+1])
         repeticoes++;

       //Caso contrario, imprime a palavra, seu numero de repeticoes e volta o valor de repeticoes para 1
       else {
         saida << palavras[i] << " " << repeticoes <<  endl;
         repeticoes = 1;
        }
    }

    //Impressao do marcador definido 
    saida << "#FIM" << endl;

    //Fechamento dos arquivos de entrada e saida
    entrada.close();
    saida.close();

    return 0;
}