#include "funcoes.hpp"

int main() {

    //Inicia variaveis necessarias
    int numRodadas = 0, dinheiroInicial = 0, numJogadores = 0, valorPingo = 0, valorAcumulado = 0, rodada = 1,
    participantes = 0, vencedor = 0, i = 0, j = 0, k = 0;
    bool rodadaInvalida = false;

    //Inicia arquivos de entrada e saida, abre arquivo de entrada
    fstream entrada;
    ofstream saida("saida.txt");
    entrada.open("entrada.txt", ios::in);

    //Le os valores necessarios da entrada
    entrada >> numRodadas >> dinheiroInicial; 
    entrada >> numJogadores >> valorPingo;

    //Cria o array de jogadores
    participantes = numJogadores;
    Jogador jogadores[participantes];

    //Inicializa os jogadores
    for(i = 0; i < participantes; i++) {
        jogadores[i].dinheiro = dinheiroInicial;
        entrada >> jogadores[i].nome >> jogadores[i].aposta >> jogadores[i].mao[0] >> 
        jogadores[i].mao[1] >> jogadores[i].mao[2] >> jogadores[i].mao[3] >> jogadores[i].mao[4];
    }

    //Verifica se existe alguma violacao dos testes de sanidade. Se sim, a rodada e invalidada.
    //Caso contrario, a mao dos apostadores e analisada e os valores do pingo e das apostas sao deduzidos do
    //montante de cada jogador e adicionados ao pote
    for(i = 0; i < participantes; i++) {
        if(jogadores[i].dinheiro < jogadores[i].aposta || jogadores[i].aposta % 50 != 0 
        || jogadores[i].dinheiro < valorPingo) {
            rodadaInvalida = true;
         for(k = 0; k < i; k++) {
            jogadores[k].dinheiro += valorPingo;
            jogadores[k].dinheiro += jogadores[k].aposta;
            }
        }

        if(rodadaInvalida)
        break;

        jogadores[i].dinheiro -= valorPingo;
        valorAcumulado += valorPingo;

        valorAcumulado += jogadores[i].aposta;
        jogadores[i].dinheiro -= jogadores[i].aposta;
        
        jogadores[i].combo = analisaMao(jogadores[i].mao);
        jogadores[i].IDCombo = atribuiID(jogadores[i].combo);
        jogadores[i].maiorCartaCombo = maiorCartaCombo(jogadores[i].mao, jogadores[i].combo);
        jogadores[i].maiorCartaForaCombo = maiorCartaForaCombo(jogadores[i].mao, jogadores[i].combo);
        if(jogadores[i].combo == "TP")
        jogadores[i].maiorCartaCombo2 = segundoPar(jogadores[i].mao);

        if(jogadores[i].combo == "RSF")
        jogadores[i].maiorCartaCombo = jogadores[i].maiorCartaForaCombo = 13;
    }

    //Escreve no arquivo de saida, se a rodada for invalida. Prepara os jogadores e o pote para uma nova rodada
    if(rodadaInvalida) {
        saida << "0 0 I" << endl;
        saida << "Rodada Invalida" << endl;
        resetaJogadores(jogadores, participantes);
        valorAcumulado = 0;
    }

    else {
    //Se a rodada nao for invalida, o vencedor e determinado
    vencedor = determinarVencedor(jogadores, participantes);
    
    //Caso haja um unico vencedor, sao impressos na saida os dados necessarios
    if(vencedor <= 100) {
        saida << "1 " << valorAcumulado << " " << jogadores[vencedor].combo << endl;
        saida << jogadores[vencedor].nome << endl;
        jogadores[vencedor].dinheiro += valorAcumulado;
    }

    //Para o caso de mais de um vencedor, percorre-se o array de jogadores imprimindo na saida o nome de cada um
    //Divide-se o pote entre os vencedores
    else if(vencedor > 100) {
        int numVencedores = 0;
        string comboVencedor;
        for(i = 0; i < participantes; i++) {
            if(jogadores[i].IDCombo == vencedor) {
            numVencedores++;
            comboVencedor = jogadores[i].combo;
            }
        }

        saida << numVencedores << " " << valorAcumulado/numVencedores << " " << comboVencedor << endl;

        for(i = 0; i < participantes; i++) {
            if(jogadores[i].IDCombo == vencedor) {
            saida << jogadores[i].nome << " ";
            jogadores[i].dinheiro += valorAcumulado/numVencedores;
            }
        }
        saida << endl;
    }
     
    //Prepara os jogadores para uma nova rodada e zera o pote
    resetaJogadores(jogadores, participantes);
    valorAcumulado = 0;

    }

    string nome;

    //Repete o que foi feito acima, com a diferenca que agora e necessario verificar qual jogador esta apostando
    for(rodada = 1; rodada < numRodadas; rodada++) {
        rodadaInvalida = false;
        entrada >> numJogadores >> valorPingo;
        for(i = 0; i < participantes; i++) {
            if(jogadores[i].dinheiro < valorPingo) {
                for(k = 0; k < i; k++)
                jogadores[k].dinheiro += valorPingo;
                
                rodadaInvalida = true;
                break;
            }
            jogadores[i].dinheiro -= valorPingo;
            valorAcumulado += valorPingo;
        }

        for(j = 0; j < numJogadores; j++) {
            entrada >> nome;
            for(i = 0; i < participantes; i++) {
                //Percorre o vetor de jogadores ate encontrar o apostador
                if(jogadores[i].nome == nome) {
                    entrada >> jogadores[i].aposta >> jogadores[i].mao[0] >> 
                    jogadores[i].mao[1] >> jogadores[i].mao[2] >> jogadores[i].mao[3] >> jogadores[i].mao[4];
                    if((jogadores[i].aposta % 50 != 0 || jogadores[i].dinheiro < jogadores[i].aposta )
                    && rodadaInvalida == false) {
                        for(k = 0; k < i; k++) 
                        jogadores[k].dinheiro += jogadores[k].aposta;
                    
                        rodadaInvalida = true;
                        break;
                      }

                      if(rodadaInvalida == false) {
 
                      valorAcumulado += jogadores[i].aposta;
                      jogadores[i].dinheiro -= jogadores[i].aposta;
                      jogadores[i].combo = analisaMao(jogadores[i].mao);
                      jogadores[i].IDCombo = atribuiID(jogadores[i].combo);
                      jogadores[i].maiorCartaCombo = maiorCartaCombo(jogadores[i].mao, jogadores[i].combo);
                      jogadores[i].maiorCartaForaCombo = maiorCartaForaCombo(jogadores[i].mao, jogadores[i].combo);

                      if(jogadores[i].combo == "TP")
                      jogadores[i].maiorCartaCombo2 = segundoPar(jogadores[i].mao);

                      if(jogadores[i].combo == "RSF")
                      jogadores[i].maiorCartaCombo = jogadores[i].maiorCartaForaCombo = 13;
                      }
                }
            }
        }

        if(rodadaInvalida == true) {
            saida << "0 0 I" << endl;
            saida << "Rodada Invalida" << endl;
            resetaJogadores(jogadores, participantes);
            valorAcumulado = 0;
            continue;
        } 

        else if(rodadaInvalida == false) {
        
        vencedor = determinarVencedor(jogadores, participantes);
    
    if(vencedor <= 100) {
        saida << "1 " << valorAcumulado << " " << jogadores[vencedor].combo << endl;
        saida << jogadores[vencedor].nome << endl;
        jogadores[vencedor].dinheiro += valorAcumulado;
    }

    else if(vencedor > 100) {
        int numVencedores = 0;
        string comboVencedor;
        for(i = 0; i < participantes; i++) {
            if(jogadores[i].IDCombo == vencedor) {
            numVencedores++;
            comboVencedor = jogadores[i].combo;
            }
        }

        saida << numVencedores << " " << valorAcumulado/numVencedores << " " << comboVencedor << endl;

        for(i = 0; i < participantes; i++) {
            if(jogadores[i].IDCombo == vencedor) {
            saida << jogadores[i].nome << " ";
            jogadores[i].dinheiro += valorAcumulado/numVencedores;
            }
        }
        saida << endl;
    }  
        resetaJogadores(jogadores, participantes);
        valorAcumulado = 0;
        }
    }

    //Imprime no arquivo de saida os resultados finais, apos todas as rodadas
    saida << endl << "####" << endl << endl;

    ordenaJogadores(jogadores, participantes);
    for(i = 0; i < participantes; i++)
    saida << jogadores[i].nome << " " << jogadores[i].dinheiro << endl;

    //Fecha os arquivos de entrada e saida
    entrada.close();
    saida.close();
    return 0;
}