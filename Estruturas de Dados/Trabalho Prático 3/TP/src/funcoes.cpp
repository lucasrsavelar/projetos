#include "funcoes.hpp"

int funcaoDispercao(int identificadorUsuario, int tamTabela) {
    //Funcao para obtencao do indice da tabela hash, definida no enunciado do trabalho
    return identificadorUsuario % tamTabela;
}

//--------------------------------FUNCOES ARVORE BINARIA--------------------------------------

    //Funcao auxiliar para entrega de um email
    void ArvoreBinaria::insercaoAuxiliar(Email* &e, string msg, int idEmail, int idUsuario) {

        //Se alcancou um no vazio da arvore, insere nele o novo email
        if(e == nullptr) {
            e = new Email;
            e->mensagem = msg;
            e->identificadorEmail = idEmail;
            e->identificadorUsuario = idUsuario;
        }

        //Caso contrario, continua percorrendo a arvore
        else {
            //Se o email novo tem id menor que o atual, vai para a esquerda da arvore
            if(idEmail < e->identificadorEmail)
            insercaoAuxiliar(e->esq, msg, idEmail, idUsuario);

            //Caso contrario, vai para a direita
            else
            insercaoAuxiliar(e->dir, msg, idEmail, idUsuario);
        }
    }

    //Funcao auxiliar para pesquisa de um email
    Email ArvoreBinaria::pesquisaAuxiliar(Email* e, int idEmail, int idUsuario) {
        //Email auxiliar para o caso do email procurado nao existir
        Email aux;
        aux.identificadorEmail = -1;
        aux.mensagem = " ";

        //Caso o email procurado nao seja encontrado, retorna o email auxiliar, que tem um identificador 
        //negativo para facilitar a identificacao da inexistencia do email procurado
        if(e == nullptr) 
        return aux;
        
        //Se o email procurado tem id menor que o atual, vai para a esquerda da arvore
        if(idEmail < e->identificadorEmail)
        return pesquisaAuxiliar(e->esq, idEmail, idUsuario);
         
        //Caso contrario, vai para a direita
        else if(idEmail > e->identificadorEmail)
        return pesquisaAuxiliar(e->dir, idEmail, idUsuario);

        //Se o email procurado tem tanto o id do email quanto o id do usuario iguais aos atuais, entao retorna
        //o atual
        else if(idEmail == e->identificadorEmail && idUsuario == e->identificadorUsuario)
        return *e;
        
        //Nesse caso, o email procurado tem id igual ao atual, mas eh de um usuario diferente, entao retorna
        //que o email procurado nao existe  
        else
        return aux;

    }

    //Funcao para quando eh necessario remover um no(email) com dois filhos
    void ArvoreBinaria::Antecessor(Email *q, Email* &r) {
        //Procura o filho mais a direita do no a esquerda do que deve ser removido
        if(r->dir != nullptr) {
            Antecessor(q, r->dir);
            return;
        }

        //Vai trocando os valores dos nos ate corrigir a arvore
        q->mensagem = r->mensagem;
        q->identificadorEmail = r->identificadorEmail;
        q = r;
        r = r->esq;
        free(q);

    }

    //Funcao auxiliar para remocao de um email
    void ArvoreBinaria::remocaoAuxiliar(Email* &e, int idEmail, int idUsuario) {
        Email *aux;

        //Se o email nao existe, troca o valor do booleano da arvore
        if(e == nullptr)
        foiRemovido = false;

        else {

        //Se o email procurado tem id menor que o atual, vai para a esquerda da arvore
        if(idEmail < e->identificadorEmail)
        return remocaoAuxiliar(e->esq, idEmail, idUsuario);

        //Caso contrario, vai para a direita
        else if(idEmail > e->identificadorEmail)
        return remocaoAuxiliar(e->dir, idEmail, idUsuario);

        //Se o email procurado tem tanto o id do email quanto o id do usuario iguais aos atuais, entao remove
        //o atual
        else if(idEmail == e->identificadorEmail && idUsuario == e->identificadorUsuario) {
            //Se o no tem um ou nenhum filho, apenas sobe esse filho para o lugar do pai removido ou
            //transforma o pai em nulo
            if(e->dir == nullptr) {
                aux = e;
                e = e->esq;
                free(aux);
            }

            else if(e->esq == nullptr) {
                aux = e;
                e = e->dir;
                free(aux);
            }

            //Se o no tem dois filhos, chama a funcao Antecessor
            else
            Antecessor(e, e->esq);
        }

        //Nesse caso, o email a ser removido tem id igual ao atual, mas eh de um usuario diferente, 
        //entao retorna que o email procurado nao existe
        else
        foiRemovido = false;
        }
    }

    //Funcao para entrega de um novo email, que chama a auxiliar
    void ArvoreBinaria::insereArvore(string msg, int idEmail, int idUsuario) {
        insercaoAuxiliar(raiz, msg, idEmail, idUsuario);
    }

    //Funcao para remocao de um email, que chama a auxiliar
    void ArvoreBinaria::removeArvore(int idEmail, int idUsuario) {
        remocaoAuxiliar(raiz, idEmail, idUsuario);
    }
 
    //Funcao para pesquisa de um email, que chama a auxiliar
    Email ArvoreBinaria::Pesquisa(int idEmail, int idUsuario) {
        return pesquisaAuxiliar(raiz, idEmail, idUsuario);
    }

    //--------------------------------FUNCOES TABELA HASH--------------------------------------

    //Inicializa a Tabela Hash criando um array de arvores binarias com o tamanho especificado na entrada
    void TabelaHash::inicializaTabela(int tamanhoTabela) {
        Tabela = new ArvoreBinaria[tamanhoTabela];
    }

    //Funcao para entrega de um email
    void TabelaHash::InsereHash(string msg, int idEmail, int identificadorUsuario, int tamTabela) {

        //Chama a funcao de dispersao para obter o indice da tabela em que o email deve ser armazenado
        int indice = funcaoDispercao(identificadorUsuario, tamTabela);
        //Insere o email, chamando a funcao da arvore binaria
        Tabela[indice].insereArvore(msg, idEmail, identificadorUsuario);
    }
 
    //Funcao para remocao de um email, que retona se a operacao teve sucesso ou nao
    bool TabelaHash::RemoveHash(int idEmail, int identificadorUsuario, int tamTabela) {

        //Chama a funcao de dispersao para obter o indice da tabela onde esta o email a ser removido
        int indice = funcaoDispercao(identificadorUsuario, tamTabela);
        //Remove o email, chamando a funcao da arvore binaria
        Tabela[indice].removeArvore(idEmail, identificadorUsuario);

        //Se nao houve alteracao no booleano da arvore, a remocao ocorreu com sucesso
        if(Tabela[indice].foiRemovido)
        return true;

        //Caso contrario, a mensagem nao existe ou ja foi removida e nao foi possivel executar a operacao
        else
        return false;
    }

    //Funcao para consulta de um email
    Email TabelaHash::PesquisaHash(int idEmail, int identificadorUsuario, int tamTabela) {

        //Chama a funcao de dispersao para obter o indice da tabela onde esta o email a ser procurado
        int indice = funcaoDispercao(identificadorUsuario, tamTabela);
        //Pesquisa o email, chamando a funcao da arvore binaria
        Email aux = Tabela[indice].Pesquisa(idEmail, identificadorUsuario);
        //Retorna o email
        return aux;
    }