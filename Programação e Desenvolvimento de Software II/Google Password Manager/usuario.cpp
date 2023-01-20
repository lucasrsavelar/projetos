#include "usuario.hpp"
using namespace std;

Usuario::Usuario(const std::string& _login, const std::string& _password) : login(_login), password(_password) {}
  // TODO: Implemente este metodo


std::string Usuario::getLogin() const {
  // TODO: Implemente este metodo
  return this->login;
}

std::string Usuario::getPassword() const {
  // TODO: Implemente este metodo
  return this->password;
}

void Usuario::setPassword(const std::string& password) {
  // TODO: Implemente este metodo
  this->password = password;
}

void Usuario::setLogin(const std::string& login) {
  // TODO: Implemente este metodo
  this->login = login;
}