#include "rock.hpp"

int main(int argc, char* argv[]) {
  
  int i = 0, j = 0;
  float aux = 0;

  int numAmigos = 0, numShows = 0;
  cin >> numAmigos >> numShows;

  int inicio = 0, fim = 0;

  while(numAmigos != 0 && numShows != 0) {

    //Criando o vetor das notas
    vector<float> notas;
    for(i = 0; i < numShows; i++)
      notas.push_back(0);

    //Preenchendo o vetor de notas
    for(i = 0; i < numAmigos; i++) {
      for(j = 0; j < numShows; j++) {
        cin >> aux;
        notas[j] += aux;
      }
    }

    //Colocando a resposta em uma instância de Solução
    Solucao s = SSM(notas, 0, numShows - 1);

    //O "start" e o "end" do SSM da solução representam os índices de início e fim do maior subvetor possível
    //Adiciona-se 1 pois os shows começam do 1, não do 0 (como o vetor)
    inicio = s.ssm.start + 1;
    fim = s.ssm.end + 1;

    //Imprimindo a solução e verificando a próxima entrada
    cout << inicio << " " << fim << endl;
    cin >> numAmigos >> numShows;
  }

  return(0);
}
