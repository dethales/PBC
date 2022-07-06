/*

OK	1. Definir uma matriz de estruturas de dimensão 50x50. Cada posição da matriz deve
	conter um caracter.

OK	2. Preencher a matriz com as nxn letras lidas a partir de arquivo-texto1, onde n é lido da
	primeira linha do arquivo e deve ser menor ou igual a 50.

OK	3. Ler cada palavra do arquivo-texto2 e armazenar em um vetor de estruturas de nome
	palavras, onde a estrutura armazena a palavra e o seu custo.

	4. Para cada palavra do vetor palavras, informar em cada linha do arquivo de saída de
	nome saida.txt a palavra e o custo. O custo de uma palavra é calculado como o
	número de letras da palavra multiplicado pelo número de ocorrências desta palavra no
	caça-palavras (na matriz). Se a palavra não existir na matriz, o menor custo associado
	da palavra deve ser -1.

	5. Escrever em seguida, no mesmo arquivo texto, separado por uma linha em branco, a
	lista das palavras encontradas na matriz, em ordem alfabética, informando o seu
	número de ocorrências na matriz. Informar nos casos que a palavra for encontrada, a
	posição na matriz do caractere inicial de cada ocorrência da palavra, além da direção
	que ela se encontra na matriz. As direções são definidas como: vertical-topo-base,
	vertical-base-topo, horizontal-esquerda-direita e horizontal-direita esquerda.
	Sugestão: Inserir na estrutura palavra, o número de ocorrências. Inserir também na
	estrutura palavra, um vetor de ocorrências dentro da estrutura palavra onde a
	ocorrência é uma estrutura que contém a posição na matriz e a direção.

	6. Informe em seguida, no mesmo arquivo texto, separado por uma linha em branco, a
	direção que mais palavras foram encontradas: vertical ou horizontal. Informe também
	a quantidade de palavras encontradas nesta direção.

	thales 20/06 -  troquei TAM_MAX por TAM pq tava um saco escrever tudo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 50 // tamanho maximo das matrizes e nomes

typedef struct Ocorrencia{
	
	int lin; // linha em que se encontra a palavra
	int col; // coluna em que se encontra a palavra
	char direcao[TAM];
	
}tOcorrencia;

typedef struct Palavra {
	
	char nome[TAM];
	int custo;
	int numOcorr; // Número de ocorrência da palavra
	tOcorrencia vetOcorr[TAM];
	
}tPalavra;


void initMatChar(char mat[TAM][TAM]);

int getMatChar(FILE *f, char mat[TAM][TAM]);

int getVetChar(FILE *f, tPalavra vet[TAM]);

void printMatChar(char mat[TAM][TAM], int m);

void printVetChar(tPalavra vet[TAM], int m);

void achaPalavra(char mat[TAM][TAM], char nome[TAM], int m);

void achaPalavraAux(char[TAM][TAM], char[TAM], int);

void inverte(char[TAM]);

void transposta(char[TAM][TAM], int);

/* DEU MERDA
void achaOcorrencia (char mat[TAM][TAM], tPalavra vet[TAM], int m, int n);

void direcaoPalavra (char mat[TAM][TAM], tPalavra vet[TAM], char nome[TAM], int lin, int col, int k);

void calculaCusto (tPalavra vet[TAM], int n);

int contaLetras (char nome[TAM]);

void imprimePalavCusto (tPalavra vet[TAM], int n);

*/



int main(void)
{
	char entrada[TAM][TAM]; // mariz para armazenar a outra matriz lida no arquivo texto 1
	
	FILE *arq1, *arq2;  // ponteiro para o arquivo 1 e 2 respectivamente 
	  
	tPalavra palavras[TAM]; // vetor de struct que armazena também as palavras lidas no arquivo texto 2
	
	int n, m = 50; // m é a dimensão da matriz lida no arquivo texto 1 e n é a quantidade de palavras lidas no arquivo texto 2
	
	initMatChar(entrada); // inicializa a matriz de entrada com '.'
 		
	arq1 = fopen("arquivo-texto1.txt", "r");
	
	if (arq1 == NULL) {
 		printf ("Erro na abertura de arquivo! Programa terminado...");
	 	exit (1);
 	}
 	
 	m = getMatChar(arq1, entrada); // Agora essa função está retornando a dimensão da matriz lida no arquivo texto 1
 	
	fclose(arq1);
	
	printMatChar(entrada, m); // manda imprimir a matriz lida no arquivo 1
	
 	arq2 = fopen("arquivo-texto2.txt", "r");
	
	if (arq1 == NULL) {
 		printf ("Erro na abertura de arquivo! Programa terminado...");
	 	exit (1);
 	}	
	
	n = getVetChar(arq2, palavras); // Essa função retorna o números de palavras lidas no arquivo texto 2
	
	fclose(arq2);
	
	printVetChar (palavras, n); // manda imprimir as palavras lidas no arquivo 2

	//achaPalavra(entrada, palavras[0].nome, m);

	achaPalavraAux(entrada, palavras[0].nome, m);
	achaPalavraAux(entrada, inverte(palavras[0].nome), m);
	achaPalavraAux(transposta(entrada, m), palavras[0].nome, m);
	achaPalavraAux(transposta(entrada, m), inverte(palavras[0].nome), m);
	
	
/* DEU MERDA
	achaOcorrencia(entrada, palavras, m, n);

	calculaCusto (palavras, n);
	
	imprimePalavCusto (palavras, n);
*/
	
	return 0;
}

/* essa funcao atribui todas as casas da matriz entrada 50x50 o caractere '.'
   eu escolhi o ponto pra poder visualizar mais facilmente os outros caracteres */ 
void initMatChar(char mat[TAM][TAM])
{
	int i, j;

	for(i = 0; i < TAM; i++)
		for(j = 0; j < TAM; j++)
			mat[i][j] = '.';
}


/* essa funcao captura da segunda linha ate a ultima do arquivo entrada-texto1
   ignorando qualquer caractere que nao seja letra maiuscula ou quebra de linha
   (incluindo espacos) e guarda na matriz entrada 50x50 */ 
int getMatChar(FILE *f, char mat[TAM][TAM])
{
/* i = -1 para poder ignorar a primeira linha do arquivo-texto1, que não é um numero */
	int i = -1, j = 0, m;
	char c;
	
	fscanf(f, "%d", &m); // le a primeira linha do arquivo, que é a dimensão da matriz
	
	do
	{
		c = getc(f);

	/*somente grava na matriz se a letra for maiuscula */
		if(c >= 'A' && c <= 'Z')
		{
			mat[i][j] = c;
			j++;
		}
		else if(c == '\n')
		{
			i++;
			j = 0;
		}
	} while(c != EOF);
	
	return m; // coloquei ela pra retornar a dimensão da matriz
}

/* Inicializa no campo "nome" de cada posição do vetor de struct tPalavra as palavras lidas no arquivo-texto2
*/
int getVetChar(FILE *f, tPalavra vet[TAM]){
	/* i = -1 para poder ignorar a primeira linha do arquivo-texto2, que não é um numero */
	int i = -1, j = 0, n;
	char c;
	
	fscanf(f, "%d", &n);

	do
	{
		c = getc(f);

	
		if(c >= 'A' && c <= 'Z')
		{
			vet[i].nome[j] = c;
			j++;
		}
		else if(c == '\n')
		{
			vet[i].nome[j++] = '\0'; // Para indicar que a palavra termina
			
			i++;
			j = 0;
		}
	} while(c != EOF);
	
	return n;
}


/* imprime uma matriz, da linha 0 ate m e da coluna 0 ate n */
void printMatChar(char mat[TAM][TAM], int m)
{
	int i, j;
	
	printf("MATRIZ LIDA NO ARQUIVO TEXTO 1:\n");
	
	for(i = 0; i < m; i++)
	{
		for(j = 0; j < m; j++)
		{
			printf("%c ", mat[i][j]);
		}
		printf("\n");
	}
		printf("\n");
}

 //imprime os nomes armazenados no vetor de palavras, só pra testar se as palavras lidas foram gravadas no vetor de struct 
//do tipo tPalavra.

void printVetChar(tPalavra vet[TAM], int n)
{
	int i;

	printf("PALAVRAS LIDAS NO ARQUIVO TEXTO 2:\n");

	for(i = 0; i < n; i++)	printf("%s\n", vet[i].nome);
	
	printf("\n\n");
}





/*   DEU MERDA

void achaOcorrencia (char mat[TAM][TAM], tPalavra vet[TAM], int m, int n){
	int i, j, k;
	
	for (k = 0; k < n; k++){
	
		vet[k].numOcorr = 0;
		
		for (i = 0; i < m; i++){
			
			for (j = 0; j < m; j++){
				
				if (mat[i][j] == vet[k].nome[0]){
					
					direcaoPalavra (mat, vet, vet[k].nome, i, j, k);
					
				}
				
			}
		}
		
	}
	
}

void direcaoPalavra (char mat[TAM][TAM], tPalavra vet[TAM], char nome[TAM], int lin, int col, int k){
	int i, j, z, w, cont = 0;
	
	// verificando na horizontal da esquerda pra direita
	for (i = 0; nome[i] != '\0' && mat[lin][col+i] != '.'; i++ ){
		
		if(mat[lin][col+i] == nome[i]) cont++;
		
	}
	
	if (cont == --i){
		
		vet[k].vetOcorr[vet[k].numOcorr].lin = lin;
		vet[k].vetOcorr[vet[k].numOcorr].col = col;
	//	vet[k].vetOcorr[vet[k].numOcorr].direcao = "horizontal-esquerda-direita";
		vet[k].numOcorr++;
		
	}
	cont = 0;
	
	// verificando na horizontal da direita pra esquerda
	for (j = 0; nome[j] != '\0' && mat[lin][col-j] != '.'; j++ ){
		
		if(mat[lin][col-j] == nome[j]) cont++;
		
	}
	
	if (cont == --j){
		
		vet[k].vetOcorr[vet[k].numOcorr].lin = lin;
		vet[k].vetOcorr[vet[k].numOcorr].col = col;
	//	vet[k].vetOcorr[vet[k].numOcorr].direcao = "horizontal-direita-esquerda";
		vet[k].numOcorr++;
		
	}
	cont = 0;
	
	// verificando na vertical de cima pra baixo
	for (z = 0; nome[z] != '\0' && mat[lin+z][col] != '.'; z++ ){
		
		if(mat[lin+z][col] == nome[z]) cont++;
		
	}
	
	if (cont == --z){
		
		vet[k].vetOcorr[vet[k].numOcorr].lin = lin;
		vet[k].vetOcorr[vet[k].numOcorr].col = col;
	//	vet[k].vetOcorr[vet[k].numOcorr].direcao = "vertical-topo-base";
		vet[k].numOcorr++;
				
	}
	cont = 0;
	
	// verificando na vertical de baixo pra cima
	for (w = 0; nome[w] != '\0' && mat[lin-w][col] != '.'; w++ ){
		
		if(mat[lin-w][col] == nome[w]) cont++;
		
	}
	
	if (cont == --w){
		
		vet[k].vetOcorr[vet[k].numOcorr].lin = lin;
		vet[k].vetOcorr[vet[k].numOcorr].col = col;
	//	vet[k].vetOcorr[vet[k].numOcorr].direcao = "vertical-base-topo";		
		vet[k].numOcorr++;
		
	}
	cont = 0;
		
}

 // recebe como parâmetro a quantidade de elementos do vetor de struct
void calculaCusto (tPalavra vet[TAM], int n){
	int i;
	
	for(i = 0; i < n; i++){
		
		vet[i].custo = (contaLetras(vet[i].nome))*vet[i].numOcorr;
	}
	
}

int contaLetras (char nome[TAM]){
	int i;
	
	for (i = 0; nome[i] != '\0'; i++);
	
	return i;	
}

void imprimePalavCusto (tPalavra vet[TAM], int n){
	int i;
	for (i = 0; i < n; i++){
		printf("%s %d\n", vet[i].nome, vet[i].custo);
	}
	
}

*/

//thales 20/06:

/*
void achaPalavra(char mat[TAM][TAM], tPalavra palavras[TAM], int m, int n)
{
	int k, l = 0, k_letra_1 = 0; // posicao da string
	int i, j; // linha e coluna da matriz respectivamente

	for(k = 0; palavras[k].nome[l] != '\0'; k++) // varre o nome
	{
		for(i = 0; i < m; i++) // varre as linhas
		{
			for(j = 0; j < m; j++) // varre a posicao na linha
			{
				if(palavras[0].nome[l] == mat[i][j]) // verifica a letra atual
				{
					if(palavras[0].nome[l+1] == '\0'); // se eh a ultima letra
					{
						palavras[0].vetOcorr[0].lin = i;
						palavras[0].vetOcorr[0].col - j;
						printf("Achein");
					}

					if(palavras[0].nome[l+1] == mat[i+1][j] && i > 0)
					{
							i++;
					}
					else if(palavras[0].nome[l+1] == mat[i-1][j] && i < m)
					{
							i--;
					}
					else if(palavras[0].nome[l+1] == mat[i][j+1] && j > 0)
					{
							j++;
					}
					else if(palavras[0].nome[l+1] == mat[i][j-1] && j < m)
					{
							j--;
					}
					else
						l = 0;
				}
			}
		}
	}
}
*/

void inverte(char nome[TAM])
{
	int i, len = strlen(nome);
	char aux, nome_copia[TAM];

	for(i = 0; i < len / 2; i++)
	{
		aux = nome[i];
		nome[i] = nome[len - i - 1];
		nome[len - i - 1] = aux;
	}
}

void transposta(char mat[TAM][TAM], int m)
{
	int i, j;

	for(i = 0; i < m; i++)
		mat[i][j] = mat[j][i];
}

/*void achaPalavra(char mat[TAM][TAM], char nome[TAM], int m)
{
	achaPalavraAux(mat, nome, m);
	achaPalavraAux(mat, inverte(nome), m);
	achaPalavraAux(transposta(mat, m), nome, m);
	achaPalavraAux(transposta(mat, m), inverte(nome), m);	
}*/

void achaPalavraAux(char mat[TAM][TAM], char nome[TAM], int m)
{
	int k = 0;
	int i, j;

	for(i = 0; i < m; i++)
	{
		for(j = 0; j < m; j++)
		{
			if(nome[k+1] == '\0')
			{
				printf("Achou\n");
			}
			if(nome[k] == mat[i][j])
			{
				printf("%c %d %d \n", nome[k], i, j);
				k++;
			}
			else
			{
				k = 0;
			}
		}
	}
}



































