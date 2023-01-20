#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MAX_TAM 100

typedef struct Xis {
    int linha, coluna, tam;
} Xis;


typedef struct Ponto {
    float x, y;
} Ponto;


typedef struct Circulo {
    Ponto centro;
    float raio;
} Circulo;

typedef struct Triangulo {
    Ponto sup, base_esq, base_dir;
} Triangulo;

//1)

void matrizIdentidade(int M[][MAX_TAM], int n) {
    
    int i=0, j=0;
    
    if(n > 0 && n <= MAX_TAM)
    {
    
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(i == j)
            {
            M[i][j] = 1;
            }
            
            else
            {
                M[i][j] = 0;
            }
        }
    }
    }
}


//2)

int insereXis(int M[][MAX_TAM], int n, Xis x) {
    
    int i = 1;
    
    if(x.linha < 0 || x.coluna < 0 || x.tam <= 0 || x.linha >= n || x.coluna >= n ||
       x.tam > n || x.linha + ((x.tam - 1) / 2) >= n || x.coluna + ((x.tam - 1) / 2) >= n ||
       x.linha - ((x.tam - 1) / 2) < 0 || x.coluna - ((x.tam - 1) / 2) < 0)
       
    {
        return 0;
    }
    
    else
    {
        M[x.linha][x.coluna] = 1;
      do
      {
          M[x.linha + i][x.coluna + i] = 1;
          M[x.linha + i][x.coluna - i] = 1;
          M[x.linha - i][x.coluna + i] = 1;
          M[x.linha - i][x.coluna - i] = 1;
          
          M[x.linha + i][x.coluna] = 0;
          M[x.linha - i][x.coluna] = 0;
          M[x.linha][x.coluna + i] = 0;
          M[x.linha][x.coluna - i] = 0;
          i++;
      }while(i != x.tam - i + 1);
      
      return 1;
    }
}

//3)

int verificaXis(int M[][MAX_TAM], Xis x, int a)
{
    if(M[x.linha + a][x.coluna + a] != 0 &&
       M[x.linha + a][x.coluna - a] != 0 &&
       M[x.linha - a][x.coluna + a] != 0 &&
       M[x.linha - a][x.coluna - a] != 0)
       {
       return 1;
       }
       
       else
       {
           return 0;
       }
}

int temBloco(int M[][MAX_TAM], Xis x, int b)
{
    
    if(M[x.linha + b][x.coluna] == 0 &&
       M[x.linha - b][x.coluna] == 0 &&
       M[x.linha][x.coluna + b] == 0 &&
       M[x.linha][x.coluna - b] == 0)
       {
       return 1;
       }
       
       else
       {
           return 0;
       }
}

   

Xis maiorXis(int M[][MAX_TAM], int n, int i, int j) {
    
    int b = 1;
    
    Xis x;
    x.linha = i;
    x.coluna = j;
    x.tam = 1;
    
    if(M[i][j] == 0)
    {
        x.tam = 0;
    }
    
    else if(M[i][j] != 0)
    {
    while(verificaXis(M, x, b) && temBloco(M, x, b))
    {
        b++;
        x.tam += 2;
    }
    }
    
    return x;
}

//4)

int lerXis(Xis *x, int n) {
    
    int tentativas = 0;
    
    do {    
        scanf("%d %d %d", &x->linha, &x->coluna, &x->tam);
        tentativas++;
    } while(x->linha < 0 || x->coluna < 0 || x->tam <= 0 || x->linha >= n || x->coluna >= n ||
            x->tam > n || x->linha + ((x->tam - 1) / 2) >= n || x->coluna + ((x->tam - 1) / 2) >= n ||
            x->linha - ((x->tam - 1) / 2) < 0 || x->coluna - ((x->tam - 1) / 2) < 0);
    
    return tentativas;
}

//5) 

int numCharsRepetidos(char str[]) {
    
    int i = 0, j = 0;
    int vetor[256];
    int total = 0;
    
    for(i=0; i<256; i++)
    {
        vetor[i] = 0;
    }
    
   while(str[j] != '\0')
   {
       vetor[toupper(str[j])]++;
       j++;
   }
    
    for(i=65; i<91; i++)
    {
        if(vetor[i] > 1)
        {
            total++;
        }
    }
    
    return total;
}

// 6

int estaDentro(Circulo cir, Triangulo tri)
{
    float t1x,t2x,t3x,ccx,t1y,t2y,t3y,ccy;
    
    t1x = tri.sup.x;
    t1y = tri.sup.y;
    
    t2x = tri.base_esq.x;
    t2y = tri.base_esq.y;
    
    t3x = tri.base_dir.x;
    t3y = tri.base_dir.y;
    
    ccx = cir.centro.x;
    ccy = cir.centro.y;
    
    float q1x,q2x,q3x,q1y,q2y,q3y;
    
    q1x = (t1x - ccx) * (t1x - ccx);
    q1y = (t1y - ccy) * (t1y - ccy);
    
    q2x = (t2x - ccx) * (t2x - ccx);
    q2y = (t2y - ccy) * (t2y - ccy);
    
    q3x = (t3x - ccx) * (t3x - ccx);
    q3y = (t3y - ccy) * (t3y - ccy);
    
    float dist1 = sqrt(q1x + q1y);
    float dist2 = sqrt(q2x + q2y);
    float dist3 = sqrt(q3x + q3y);
    
    float baricentrox, baricentroy;
    
    baricentrox = (t1x + t2x + t3x) / 3;
    baricentroy = (t1y + t2y + t3y) / 3;
    
    float qbx, qby;
    
    qbx = (baricentrox - ccx) * (baricentrox - ccx);
    qby = (baricentroy - ccy) * (baricentroy - ccy);
    
    float distb = sqrt(qbx + qby);
    
    if(dist1 <= cir.raio && dist2 <= cir.raio && dist3 <= cir.raio && distb <= cir.raio)
    {
        return 1;
    }
    
    else
    {
    return 0;
    }
}

int estaContidoCirculoTriangulo(Circulo cir, Triangulo tri) {
    
   if(estaDentro(cir, tri))
   {
       return 1;
   }
   
   else
   {
       return 0;
   }
}

// 0

void minha_main() {
    //Voce pode simular uma funcao main nesta funcao. Use-a para testar o que quiser. 
    //Para isso, execute a sua prova e entre com o exercicio 0.
    //Isso fara com que esta funcao (minha_main) seja chamada pelo VPL.
    //Importante: esta funcao NAO sera avaliada!!! No entanto, erros de compilacao nesta funcao invalidam (nota 0!) TODA a prova!
    
    printf("\nPor enquanto nao estou fazendo nada :(");
    
}

