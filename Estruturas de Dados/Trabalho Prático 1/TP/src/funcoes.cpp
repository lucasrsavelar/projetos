#include "funcoes.hpp"

//Funcao que analisa a carta com maior valor dentro de um combo (combo = jogada)
int maiorCartaCombo(string* mao, string combo) {
    //Quando um jogador nao aposta, seu combo e definido como NA
    if(combo == "NA")
    return 0;

    //Cria um vetor com 14 posicoes e o preenche com 0
    int valores[14], i = 0, maior = 0;
    for(i = 0; i < 14; i++) 
    valores[i] = 0;

    //No vetor criado, adiciona-se uma unidade em cada posicao do vetor equivalente ao valor da carta.
    //Na carta 9 de paus, por exemplo, adiciona-se uma unidade na nona posicao do vetor
    for(i = 0; i < 5; i++) {
        istringstream is(mao[i]);
        int n;
        while( is >> n )
        valores[n]++;
    }

    //Procura e retorna a maior carta, dependendo do combo
    if(combo == "SF" || combo == "S" || combo == "F" || combo == "HC") {
    //Retorna a maior preenchida do vetor, que e a maior carta
    for(i = 1; i < 14; i++) {
        if(valores[i] > 0)
        maior = i;
    }
    }

    else if(combo == "FK") {
        //Retorna qual o valor das cartas que compoe o FK
        for(i = 1; i < 14; i++) {
        if(valores[i] == 4)
        maior = i;
    }
    }

    else if(combo == "FH") {
        //Retorna qual o valor das cartas que compoe a trinca do FH
        for(i = 1; i < 14; i++) {
        if(valores[i] == 3)
        maior = i;
    }
    }

    else if(combo == "TK") {
        //Retorna qual o valor das cartas que compoe o TK
        for(i = 1; i < 14; i++) {
        if(valores[i] == 3)
        maior = i;
    }
    }

    else if(combo == "TP" || combo == "OP") {
        //Retorna qual o valor das cartas que compoe o maior par
        for(i = 1; i < 14; i++) {
        if(valores[i] == 2)
        maior = i;
    }
    }

    else
    maior = 0;

    return maior;
}

//Funcao que analisa a carta com maior valor fora do combo, para ajudar no desempate
int maiorCartaForaCombo(string* mao, string combo) {
    if(combo == "NA")
    return 0;

    int valores[14], i = 0, maior = 0;
    for(i = 0; i < 14; i++) 
    valores[i] = 0;

    for(i = 0; i < 5; i++) {
        istringstream is(mao[i]);
        int n;
        while( is >> n )
        valores[n]++;
    }

    if(combo == "SF" || combo == "S" || combo == "F" || combo == "HC") {
    //Retorna a segunda maior carta desses combos
    int count = 0;
    for(i = 14; i > 0; i--) {
        if(valores[i] > 0) {
        maior = i;
        count++;
        }

        if(count == 2)
        break;
    }
    }

    else if(combo == "FK") {
        //Retorna a carta que esta fora do FK
        for(i = 1; i < 14; i++) {
        if(valores[i] != 4 && valores[i] > 0)
        maior = i;
    }
    }

    else if(combo == "FH") {
        //Retorna qual o valor das cartas que compoe o par do FH
        for(i = 1; i < 14; i++) {
        if(valores[i] == 2)
        maior = i;
    }
    }

    else if(combo == "TK") {
        //Retorna a maior carta fora do TK
        for(i = 1; i < 14; i++) {
        if(valores[i] != 3 && valores[i] > 0) 
        maior = i;
    }
    }

    else if(combo == "TP" || combo == "OP") {
        //Retorna a maior carta fora dos pares
        for(i = 1; i < 14; i++) {
        if(valores[i] != 2 && valores[i] > 0)
        maior = i;
    }
    }

    else
    maior = 0;

    return maior;

}

//Funcao exclusiva para desempate de TPs. Retorna o valor das cartas que compoe o segundo par
int segundoPar(string* mao) {

    int valores[14], i = 0, segundoPar = 0;
    for(i = 0; i < 14; i++) 
    valores[i] = 0;

    for(i = 0; i < 5; i++) {
        istringstream is(mao[i]);
        int n;
        while( is >> n )
        valores[n]++;
    }

    for(i = 1; i < 14; i++) {
        if(valores[i] == 2) {
        segundoPar = i;
        break;
        }
    }

    return segundoPar;

}

//Funcao que analisa a mao de um jogador e retorna o maior combo que ela forma
string analisaMao(string* mao) {
    if(mao[0] == "NA")
    return "NA";

    int valores[14];
    string naipes[5];
    int i = 0;
    for(i = 0; i < 14; i++) 
    valores[i] = 0;

    for(i = 0; i < 5; i++)
    naipes[i] = "";
    
    for(i = 0; i < 5; i++) {
        istringstream is(mao[i]);
        int n;
        while( is >> n )
        valores[n]++;

        naipes[i] = mao[i].back();
    }

    bool mesmoNaipe = false, ehSequencia = false, ehRSF = false;
    int numPares = 0, numTrios = 0, numQuadras = 0;

    for(i = 0; i < 14; i++) {
        //Conta numero de pares
        if(valores[i] == 2)
        numPares++;

        //Conta numero de trincas 
        if(valores[i] == 3)
        numTrios++;
      
        //Conta numero de quadras
        if(valores[i] == 4)
        numQuadras++;
    }

    //Verifica se os naipes de todas as cartas sao iguais
    if(naipes[0] == naipes[1] && naipes[1] == naipes[2] && naipes[2] == naipes[3] && naipes[3] == naipes[4])
    mesmoNaipe = true;

    //Verifica se e um RSF
    if(valores[10] == 1 && valores[11] == 1 && valores[12] == 1 && valores[13] == 1 && valores[1] == 1
    && mesmoNaipe == true)
    ehRSF = true;

    for(i = 0; i <= 9; i++) {
        //Verifica se e uma sequencia
        if(valores[i] == 1 && valores[i+1] == 1 && valores[i+2] == 1 && valores[i+3] == 1 && valores[i+4] == 1 ) {
        ehSequencia = true;
        break;
        }
    }

    //Verifica o caso especial da sequencia do 10 ao As
    if(valores[10] == 1 && valores[11] == 1 && valores[12] == 1 && valores[13] == 1 && valores[1] == 1)
    ehSequencia = true;

    //Retorna o combo do jogador, dependendo do valor de cada variavel
    if(ehRSF)
    return "RSF";

    else if(ehSequencia == true && mesmoNaipe == true)
    return "SF";

    else if(numQuadras == 1)
    return "FK";

    else if(numTrios == 1 && numPares == 1)
    return "FH";

    else if(mesmoNaipe == true && ehSequencia == false)
    return "F";

    else if(mesmoNaipe == false && ehSequencia == true)
    return "S";

    else if(numTrios == 1)
    return "TK";

    else if(numPares == 2)
    return "TP";

    else if(numPares == 1)
    return "OP";

    else
    return "HC";
}

//Funcao que atribui um ID para cada combo
int atribuiID(string combo) {

    if(combo == "RSF")
    return 1000;

    else if(combo == "SF")
    return 900;

    else if(combo == "FK")
    return 800;

    else if(combo == "FH")
    return 700;

    else if(combo == "F")
    return 600;

    else if(combo == "S")
    return 500;

    else if(combo == "TK")
    return 400;

    else if(combo == "TP")
    return 300;

    else if(combo == "OP")
    return 200;

    else if(combo == "HC")
    return 150;

    else 
    return 110;  
}

//Funcao para determinar o vencedor de uma rodada
int determinarVencedor(Jogador* jgdr, int numParticipantes) {
    int i = 0, vencedor = 0, maiorCombo = 0, combosVencedores = 0;
    bool vencedorUnico = true, maisDeDois = false;
    string nome;
    //Procura pelo combo com maior ID
    for(i = 0; i < numParticipantes; i++) {
        if(jgdr[i].IDCombo > maiorCombo) {
        vencedor = i;
        nome = jgdr[i].nome;
        maiorCombo = jgdr[i].IDCombo;
        }
    }

    //Verifica se algum outro jogador tem o mesmo maior combo
    for(i = 0; i < numParticipantes; i++) {
        if(jgdr[i].IDCombo == maiorCombo && jgdr[i].nome != nome) {
        vencedorUnico = false;
        break;
        }
    }

    //Retorna o vencedor, caso haja apenas um
    if(vencedorUnico)
    return vencedor;

    else {
     //Caso o maior combo nao seja TP, os valores do maior combo sao analisados. Em caso de empate, analisa-se
     //a maior carta fora do combo. Permanencendo o empate, o ID do maior combo e retornado
     if(maiorCombo != 300) {
      for(i = 0; i < numParticipantes; i++) {
        if(jgdr[i].IDCombo == maiorCombo && jgdr[i].maiorCartaCombo > jgdr[vencedor].maiorCartaCombo
        && jgdr[i].nome != nome) {
        vencedor = i;
        nome = jgdr[i].nome;
        maiorCombo = jgdr[i].IDCombo;
        }

        else if(jgdr[i].IDCombo == maiorCombo && jgdr[i].maiorCartaCombo == jgdr[vencedor].maiorCartaCombo
        && jgdr[i].maiorCartaForaCombo > jgdr[vencedor].maiorCartaForaCombo && jgdr[i].nome != nome) {
        vencedor = i;
        nome = jgdr[i].nome;
        maiorCombo = jgdr[i].IDCombo;
        }

        else if(jgdr[i].IDCombo == maiorCombo && jgdr[i].maiorCartaCombo == jgdr[vencedor].maiorCartaCombo
        && jgdr[i].maiorCartaForaCombo == jgdr[vencedor].maiorCartaForaCombo && jgdr[i].nome != nome) {
        vencedor = i;
        maisDeDois = true;
        combosVencedores = maiorCombo;
        }
        }
    }

    else if(maiorCombo == 300) {
      //Caso o maior combo seja TP, os valores do maior par sao analisados. Se empatarem, os valores do
      //segundo par sao analisados. Permancendo o empate, retorna-se o ID do TP
      for(i = 0; i < numParticipantes; i++) {
        if(jgdr[i].IDCombo == maiorCombo && jgdr[i].maiorCartaCombo > jgdr[vencedor].maiorCartaCombo
        && jgdr[i].nome != nome) {
        vencedor = i;
        nome = jgdr[i].nome;
        }

        else if(jgdr[i].IDCombo == maiorCombo && jgdr[i].maiorCartaCombo == jgdr[vencedor].maiorCartaCombo
        && jgdr[i].maiorCartaCombo2 > jgdr[vencedor].maiorCartaCombo2) {
        vencedor = i;
        nome = jgdr[i].nome;
        }

        else if(jgdr[i].IDCombo == maiorCombo && jgdr[i].maiorCartaCombo == jgdr[vencedor].maiorCartaCombo
        && jgdr[i].maiorCartaCombo2 == jgdr[vencedor].maiorCartaCombo2 && 
        jgdr[i].maiorCartaForaCombo > jgdr[vencedor].maiorCartaForaCombo && jgdr[i].nome != nome) {
        vencedor = i;
        nome = jgdr[i].nome;
        }

        else if(jgdr[i].IDCombo == maiorCombo && jgdr[i].maiorCartaCombo == jgdr[vencedor].maiorCartaCombo
        && jgdr[i].maiorCartaCombo2 == jgdr[vencedor].maiorCartaCombo2 && 
        jgdr[i].maiorCartaForaCombo == jgdr[vencedor].maiorCartaForaCombo && jgdr[i].nome != nome) {
        vencedor = i;
        maisDeDois = true;
        combosVencedores = maiorCombo;
        }
        }

    }
    if(maisDeDois == false)
    return vencedor;

    else
    return combosVencedores;
    }
}

//Funcao que retorna os jogadores para o estado inicial, preparando-os para uma nova rodada
void resetaJogadores(Jogador* jgdr, int numJogadores) {
    int i = 0, j = 0;
    for(i = 0; i < numJogadores; i++) {
        jgdr[i].aposta = 0;
        jgdr[i].maiorCartaCombo = 0;
        jgdr[i].maiorCartaCombo2 = 0;
        jgdr[i].maiorCartaForaCombo = 0;
        jgdr[i].IDCombo = 0;
        jgdr[i].combo = "NA";
        for(j = 0; j < 5; j++) 
            jgdr[i].mao[j] = "NA";    
    }
}

//Funcao que ordena os jogadores em ordem decrescente de dinheiro
void ordenaJogadores(Jogador* jogadores, int participantes) {
    int a = 0, b = 0;
    for(a = 0; a < participantes - 1 ; a++) {
    for(b = 1; b < participantes - a; b++) {
      if(jogadores[b].dinheiro > jogadores[b-1].dinheiro)
      Troca(jogadores[b-1], jogadores[b]);
    }
  }
}