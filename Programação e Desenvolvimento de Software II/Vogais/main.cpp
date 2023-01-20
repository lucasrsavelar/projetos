#include <iostream>

using std::cout;
using std::cin;

int main()

{
  char palavra[100];
  cin >> palavra;

  int a = 0, e = 0, i = 0, o = 0, u = 0, x = 0;

  while(palavra[x] != '\0')
  {
      if(palavra[x] == 'a') {
          a++;
      }

      else if(palavra[x] == 'e') {
          e++;
      }

      else if(palavra[x] == 'i') {
          i++;
      }

      else if(palavra[x] == 'o') {
          o++;
      }

      else if(palavra[x] == 'u') {
          u++;
      }

      x++;
  }


  if(a>0){
  cout << "a " << a << "\n"; }

  if(e>0) {
  cout << "e " << e << "\n"; }

  if(i>0) {
  cout << "i " << i << "\n"; }

  if(o>0) {
  cout << "o " << o << "\n"; }

  if(u>0) {
  cout << "u " << u << "\n"; }

  
  return 0;

}