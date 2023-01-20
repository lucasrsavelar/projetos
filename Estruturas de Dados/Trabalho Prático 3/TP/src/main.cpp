#include "funcoes.hpp"

int main(int argc, char* argv[]) {

    string input, output = " ";

    int i = 0;

    //Obtem os arquivos de entrada e saida da linha de comando
    for (i = 1; i < argc; i+=2) {
        if(string(argv[i]) == "-i" || string(argv[i]) == "-I")
        input = argv[i+1];
   
        else if(string(argv[i]) == "-o" || string(argv[i]) == "-O")
        output = argv[i+1];
    }

    //Tratamento para o caso de não fornecimento do argumento de arquivo de saida
    if(output == " ")
    output = "saida.txt";

    //Declara e inicializa os arquivos de entrada e saida
    ifstream entrada(input, ios::in);
    ofstream saida(output);

    //Obtem o tamanho da tabela da entrada
    int tamanhoTabela = 0;
    entrada >> tamanhoTabela;

    //Declara e inicializa a tabela Hash
    TabelaHash TH;
    TH.inicializaTabela(tamanhoTabela);

    while(!entrada.eof()) {

        //Declaracao de variaveis auxiliares
        string comando, msg = "", auxiliar;
        int j = 0, numPalavras = 0, idUsuario = 0, idEmail = 0, indice = 0;
        Email temp;
        bool remocao;
  
        //Obtem a operacao desejada
        entrada >> comando;

        //Se for uma entrega
        if(comando == "ENTREGA") {

            //Obtem da entrada o id do usuario, id do email e tamanho da mensagem
            entrada >> idUsuario >> idEmail >> numPalavras;
            //Obtem da entrada a primeira palavra da mensagem e anexa a variavel mensagem
            entrada >> auxiliar;
            msg += auxiliar;

            //Enquanto houver palavras para ler, adiciona um espaco a mensagem; obtem da entrada a nova palavra
            //e adiciona a nova palavra na mensagem 
            for(j = 1; j < numPalavras; j++) {
                msg += " ";
                entrada >> auxiliar;
                msg += auxiliar;
            }

            //Chama a funcao de insercao da Tabela Hash para entregar o email
            TH.InsereHash(msg, idEmail, idUsuario, tamanhoTabela);

            //Chama a funcao de dispersao para obter o indice da tabela em que o email deve ser armazenado
            indice = funcaoDispercao(idUsuario, tamanhoTabela);

            //Imprime na saida as informacoes necessarias
            saida << "OK: MENSAGEM " << idEmail << " PARA " << idUsuario <<
            " ARMAZENADA EM " << indice << endl;
        
        }

        //Se for uma consulta
        else if(comando == "CONSULTA") {
 
            //Obtem da entrada o id do usuario e id do email
            entrada >> idUsuario >> idEmail;
            //Chama a funcao de pesquisa da Tabela Hash para retornar o email
            temp = TH.PesquisaHash(idEmail, idUsuario, tamanhoTabela);

            //Caso o identificador do email seja valido, imprime na saida as informacoes necessarias
            //e a mensagem
            if(temp.identificadorEmail != -1) 
            saida << "CONSULTA " << idUsuario << " " << idEmail << ": " << temp.mensagem << endl;

            //No caso de identificador invalido, imprime na saida que a mensagem nao existe
            else
            saida << "CONSULTA " << idUsuario << " " << idEmail << ": MENSAGEM INEXISTENTE" << endl;
            
        }

        //Se for uma remocao
        else if(comando == "APAGA") {

            //Obtem da entrada o id do usuario e id do email
            entrada >> idUsuario >> idEmail;
            //Chama a funcao de remocao da Tabela Hash para apagar o email e retornar o resultado
            remocao = TH.RemoveHash(idEmail, idUsuario, tamanhoTabela);

            //Com resultado verdadeiro, a remocao foi executada com sucesso e as informacoes necessarias sao
            //impressas na saida
            if(remocao)
            saida << "OK: MENSAGEM APAGADA" << endl;

            //Caso contrario, a mensagem nao existe ou ja foi apagada
            else {
                //Imprime na saida a mensagem de erro
                saida << "ERRO: MENSAGEM INEXISTENTE" << endl;
                //Chama a funcao de dispersao para obter o indice da tabela em que houve tentativa de remocao
                indice = funcaoDispercao(idUsuario, tamanhoTabela);
                //Reseta o booleano da arvore de volta para true
                TH.Tabela[indice].foiRemovido = true;
            }

        }
    }

    entrada.close();
    saida.close();

    return 0;

}