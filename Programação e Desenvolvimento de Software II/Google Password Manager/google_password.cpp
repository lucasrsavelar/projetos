#include "google_password.hpp"

#include <iostream>
#include <sstream>
using namespace std;

void GooglePassword::insert(const std::string& url,
                            const std::string& login,
                            const std::string& password) {
  // TODO: Implemente este metodo
  /**
   * Lembre-se que as credenciais so podem ser inseridas com as seguintes
   * condicoes:
   * Condicao 1: A senha nao pode ter a seguencia '123456'.
   * Condicao 2: A senha nao pode ter mais do que 50 caracteres (no maximo 50).
   * Condicao 3: A senha nao pode ter menos do que 6 caracteres (no minimo 6).
   * Condicao 4: A senha nao pode ter caracteres em branco ' '.
   *
   * Exemplos de senhas invalidas:
   * 123456
   * test_123456
   * 123456_test
   * test_123456_test
   * senha test
   */
   
   if(checkPassword(password)) {
       m_passwords.insert({url, Usuario(login, password)});
   }
}

void GooglePassword::remove(const std::string& url) {
  // TODO: Implemente este metodo
  map<string, Usuario>::iterator it;
  for(it = m_passwords.begin(); it != m_passwords.end(); it++) {
      if(it->first == url)
      //m_passwords.erase(it);
      it->second.Usuario::setLogin("deletado");
  }
 }


void GooglePassword::update(const std::string& url,
                            const std::string& login,
                            const std::string& old_password,
                            const std::string& new_password) {
  // TODO: Implemente este metodo
  /**
   * Caso a url nao seja encontrada, o metodo update deve ser ignorado, ou seja,
   * este metodo nao pode inserir novas credenciais. Alem disso, as informacoes
   * do usuario so podem ser atualizadas se a senha antiga for igual a senha
   * atual. Nao esqueca de verificar se o novo password tambem e valido.
   */
   map<string, Usuario>::iterator it;
   for(it = m_passwords.begin(); it != m_passwords.end(); it++) {
       if(it->first == url) {
           string senhaAtual = it->second.Usuario::getPassword();
           if(senhaAtual == old_password && checkPassword(new_password) == true) {
               it->second.Usuario::setPassword(new_password);
               it->second.Usuario::setLogin(login);
           }
       }
   }
}

void GooglePassword::printPasswords() {
  // TODO: Implemente este metodo
  /**
   * Exemplo de saida:
   * www.site.com: login and password
   *
   */
   int i = 0;
   map<string, Usuario>::iterator it;
   for(it = m_passwords.begin(); it != m_passwords.end(); it++) {
       string teste = it->second.Usuario::getLogin();
       if(teste != "deletado")
       i++;
   }
   
   cout << i << endl;
   
   for(it = m_passwords.begin(); it != m_passwords.end(); it++) {
       string url = it->first;
       string login = it->second.Usuario::getLogin();
       string senha = it->second.Usuario::getPassword();
       
       if(login != "deletado")
       cout << url << ":" << login << " and " << senha << endl;
   }
}

bool GooglePassword::checkPassword(const std::string& password) const {
  // TODO: Implemente este metodo
  int i = 0;
  int verdadeiro = 1;
  
  if(password.length() < 6 || password.length() > 50) {
      verdadeiro = 0;
      return false;
  }
  
  for(i = 0; i < password.length(); i++) {
      if(password[i] == ' ') {
      return false;
      verdadeiro = 0;
      }
  }
  
  for(i = 0; i < password.length(); i++) {
      if(password[i] == '1') {
          if(password[i+1] == '2' && password[i+2] == '3' && password[i+3] == '4' && password[i+4] == '5' && password[i+5] == '6') {
          return false;
          verdadeiro = 0;
          }
      }
  }
  
  if(verdadeiro)
  return true;
}

