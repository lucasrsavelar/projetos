#include <stdio.h>
#include <stdlib.h>

// 1
float somaSaldo(char nome_arquivo[], int filial, int ini, int fim) {
    
  float soma = 0;
	int limite = 0;
    FILE *arq = fopen(nome_arquivo, "r");
    
    if(arq == NULL || fim < ini || filial < 1 || filial > 5)
       return 0;

	int i = 0, j = 0;
    float **M = NULL;
	
	
	M = (float**)malloc(fim * sizeof(float*));
	for(i = 0; i < fim; i++)
		M[i] = (float*)malloc(5 * sizeof(float));
	
	for(i = 0; i < fim; i++) 
		for(j = 0; j < 5; j++) 
			M[i][j] = 0;
       
    if(ini < 1)
       ini = 1;
   
    while(feof(arq) == 0 && limite < fim) {
		
		for(i = 0; i < fim; i++) {
			for(j = 0; j < 5; j++) {
				fscanf(arq,"%f", &M[i][j]);
				if(j + 1 == filial && i + 1 >= ini && i + 1 <= fim) 
					soma += M[i][j];		
			}
			
			limite++;
		}
		
	}
	
    fclose(arq);
	for(i = 0; i < fim; i++)
		free(M[i]);
	free(M);
	
	return soma;  
}

// 2
float** carregaLista(char nome_arquivo[]) {
    
    int i = 0, a = 0;
	
	int num_linhas;
	FILE *arq = fopen(nome_arquivo, "r");
	if(arq == NULL)
	   return NULL;
	fscanf(arq, "%d\n", &num_linhas);
	
	float **M = NULL;
	M = (float**)malloc((num_linhas + 1) * sizeof(float*));
	
	char c[20];
	int ano = 0;
	int numelementos = 0;
	
	
	while(a < num_linhas)
	{		
		fscanf(arq, "%s", c);
		fscanf(arq, "%d", &ano);
		fscanf(arq, "%d", &numelementos);
		M[a] = (float*)malloc((numelementos + 1) * sizeof(float));
		
		for(i = 0; i < numelementos; i++) {
			fscanf(arq, "%f", &M[a][i]);
		}
		M[a][numelementos] = 0;
		a++;
	}
	
	M[num_linhas] = NULL;
	
    return M;
}

// 3
float somaValor(float *g)

{
	int a = 0;
	if(g[a] == 0)
		return 0;
	
	return g[a] + somaValor(g + 1);
}

float confereValores(float **g, int i)

{
	float valor1, valor2;
	
	if(g[i] == NULL)
		return 0;
	
	valor1 = somaValor(g[i]);
	valor2 = confereValores(g,i + 1);
	
	if(valor1 > valor2)
		return valor1;
	
	else
		return valor2;

}

float maiorGasto(float **gastos) {

    int i = 0;
	
    float valor = confereValores(gastos, i);
	
	return valor;
	
}


// 4
//não altere este struct!
typedef struct Empresa {
  float juros;
  float taxa;
}Empresa;

float calculaJuros(float valor, int m, Empresa empresa)

{
   if(m == 0)
	   return 0;
   
   float atual = valor + (valor * empresa.juros);
  
   return valor * empresa.juros + calculaJuros(atual, m - 1, empresa);
  
}

float valorTotalEmprestimo(float valor, int m, Empresa empresa) {
   
   float valorbase = valor + empresa.taxa;
   float juros = calculaJuros(valorbase, m, empresa);

   return valorbase + juros;
}

// 5
int chavesAbertas(char *p) 

{
    int num = 0;
    if(*p == '\0')
       return 0;
    
    else if(*p == '{')
       num++;
       
    return num + chavesAbertas(p+1);
}

int chavesFechadas(char *p) 

{
    int num = 0;
    if(*p == '\0')
       return 0;
    
    else if(*p == '}')
       num++;
       
    return num + chavesFechadas(p+1);
}


int diferencaChaves(char *programa) {
    
    int abertas = chavesAbertas(programa);
    int fechadas = chavesFechadas(programa);
    
    if(abertas == fechadas)
       return 0;
       
    else if(abertas > fechadas) 
       return abertas - fechadas;
       
    else if(abertas < fechadas)
       return -(fechadas - abertas);
}

// Para testes
int minha_main()
{
    return -1;
}