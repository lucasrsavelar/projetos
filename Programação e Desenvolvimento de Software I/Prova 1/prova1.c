//arquivo inicial da prova.


//implemente abaixo os codigos das funcoes da prova:

#include <stdio.h>

int cadastraUsuario(int *chave, int *senha) //1

{
    int n;
    do {
        scanf("%d" "%d", chave, senha);
       } while(*chave < 1000 || *chave > 999999 || *senha < 1000 || *senha > 999999);
  
    if(*chave > 2000) {
        n = 3;
    } else {
        n = 5;
    }
   
    return n;
}

int verificaSenha(int tentativa, int senha) //2

{

    if(tentativa == senha) 
    {
        return 1;
    }
        return 0;
}

int acessoConta(int senha, int n) //3

{
    int tentativa;
    int tentativa2;
    
  do {
   scanf("%d", &tentativa);
  if(tentativa == -999 )
   {
       n--;
       do {
      scanf("%d", &tentativa2);
      if(senha % tentativa2 == 0 && tentativa2 > 10)
      {
          return 1;
      }
      else {
          n--;
      }
   } while(n>0);
   }
   
   else {
   if(verificaSenha(tentativa, senha) == 1)
  {
      return 1;
  }
   else {
       n--;
   }
  }
  } while(n > 0);
 return 0;
}

char cartaoCredito(int score) //4

{
    if(score < 0 || score > 1000) {
        printf("Score invalido\n");
        return 'X';
    }
    else if(score <= 400) {
        printf("Cartao negado\n");
        return 'N';
    }
    else if(score >= 401 && score <= 600) {
        printf("Necessita de mais detalhes\n");
        return 'X';
    }
    else if(score >= 601 && score <= 800) {
        printf("Cartao basico\n");
        return 'B';
    }
    else {
        printf("Cartao gold\n");
        return 'A';
    }
}

void banco() //5

{
    int score, chave, senha, n;
    n = cadastraUsuario(&chave, &senha);
    score = chave % 1000;
    if (acessoConta(senha, n) == 1) {
        printf("Acesso realizado com sucesso\n"); 
        printf("%c", cartaoCredito(score));
    } else 
  {
     printf("Cliente bloqueado\n");
    } 
    
} 

int codigoVerificador(int chave) //7

{

int n;
int resto;
        do {
            chave & 1;
            if(chave & 1 == 1)
            {
                chave = chave >> 1;
                n++;
            } else 
            {
            chave = chave >>1;
            }
        } while(chave > 0);
    
    if(n < 10) {
        return n;
    }
    else {
    resto = n % 10;
    return resto;
    }

}
//IMPORTANTE: voce nao deve implementar a funcao main()!