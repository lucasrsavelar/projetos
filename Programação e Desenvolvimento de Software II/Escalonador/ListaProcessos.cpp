#include "ListaProcessos.hpp"

void ListaProcessos::adicionar_processo(Processo* proc) {
    Processo* aux = new Processo;
    
    aux->id = proc->id;
    aux->nome = proc->nome;
    aux->prioridade = proc->prioridade;
    
    if(head==nullptr) {
        head = aux;
        tail = aux;
        aux->next = nullptr;
    }
    
    else {
        Processo* current = head;
        
        while(current != nullptr) {
            if(aux->prioridade <= current->prioridade && current->next != nullptr) {
                current = current->next;
            }
            
            else if(aux->prioridade > current->prioridade && current == head)
            {
               head = aux;
               aux->next = current;
               break;
            }
            
            else if(aux->prioridade > current->prioridade && current != head) 
            {
                aux->next = current;
                Processo* it = head;
                while(it != nullptr) {
                    if(it->next == current) {
                        it->next = aux;
                        break;
                    }
                    it = it->next;
                }
                break;
            }
            
            else if(aux->prioridade <= current->prioridade && current->next == nullptr) 
            {
                current->next = aux;
                aux->next = nullptr;
                tail = aux;
                break;
            }
        }
    } 
}

Processo* ListaProcessos::remover_processo_maior_prioridade() {
    
    Processo* removed = head;
    head = head->next;
    removed->next = nullptr;
    
    return removed;
}

Processo* ListaProcessos::remover_processo_menor_prioridade() {
    Processo* removed = tail;
    
    Processo* current = head;
    
    while(current != nullptr) {
        if(current->next->next == nullptr) {
            tail = current;
            current->next = nullptr;
        }
        current = current->next;
    }
    removed->next = nullptr;
    return removed;
}

Processo* ListaProcessos::remover_processo_por_id(int id) {
    
    Processo *current = head;
    Processo *removed = nullptr;
    
    while(current != nullptr) {
        if(current->id == id) {
            if(current == head) {
            head = current->next;}
            
            else if(current->next == nullptr) {
            Processo* it = head;
            while(it != nullptr) {
                if(it->next == current) {
                it->next = nullptr;
                tail = it;
                break; }
                it = it->next;
            }
            }
            else {
                Processo* it = head;
                while(it != nullptr) {
                if(it->next == current) {
                    it->next = current->next;
                }
                it = it->next;
            }
            }
            
            removed = current;
            removed->next = nullptr;
        }
        
        else {
            removed = nullptr;
        }

        current = current->next;
        
    }
    
    return removed;
}

void ListaProcessos::imprimir_lista() {
    
    Processo* current = head;
    
    while(current != nullptr) {
        current->imprimir_dados();
        current = current->next;
    }
    
}