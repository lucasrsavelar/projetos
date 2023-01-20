// NÃO ALTERE ESSA LINHA
#include "avaliacao_basica_escalonador.hpp"

#include "Processo.hpp"
#include "ListaProcessos.hpp"

int main() {
    
    ListaProcessos* Lista_Processos = new ListaProcessos;
    
    char comando;
    
    while(cin >> comando) {
        
    if(comando == 'a') {
        Processo *proc = new Processo;
        cin >> proc->id;
        cin >> proc->nome;
        cin >> proc->prioridade;
        Lista_Processos->adicionar_processo(proc);
    }
    
    else if(comando == 'm') {
        Lista_Processos->remover_processo_maior_prioridade();
    }

    else if(comando == 'n') {
        Lista_Processos->remover_processo_menor_prioridade();
    }
    
    else if(comando == 'r') {
        int n;
        cin >> n;
        Lista_Processos->remover_processo_por_id(n);
    }
    
    else if(comando == 'p') {
        Lista_Processos->imprimir_lista();
    }
    
    else if(comando == 'b') {
        avaliacao_basica();
    }
    
    }

    return 0;
}