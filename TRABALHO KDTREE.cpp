#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <Math.h>


#define K 2 			// MÁXIMO DE DIMENSÕES
#define TAM 25 			// MÁXIMO DE COORDENADAS
#define MAX 100	 		// MÁXIMO DE UMA COORDENADA


// DEFINIÇÃO DAS ESTRUTURAS


///////////////////////////////////////////////////////////


struct KdTree
{
	int ponto[K];
	struct KdTree *esq, *dir;
};
typedef struct KdTree KdTree;



KdTree* CriaNo (int ponto[K])
{
	KdTree *Nova = (KdTree*) malloc(sizeof(KdTree));
	for (int i=0; i < K;i++)
		Nova->ponto[i] = ponto[i];
	Nova->esq = NULL;
	Nova->dir = NULL;
	return Nova;
}


////////////////////////////////////////////////////////////


// FUNÇÕES GERAIS


void EncheVetorChico (int vet[][K])
{
	//(30,40), (5,25), (10,12), (70,70), (50,30), (35,45)
	
	// SE FOR TESTAR COM ESSES VALORES O K TEM QUE SER 2
	
	vet[0][0] = 30;
	vet[0][1] = 40;
	
	vet[1][0] = 5;
	vet[1][1] = 25;
	
	vet[2][0] = 10;
	vet[2][1] = 12;
	
	vet[3][0] = 70;
	vet[3][1] = 70;
	
	vet[4][0] = 50;
	vet[4][1] = 30;
	
	vet[5][0] = 35;
	vet[5][1] = 45;
}


void Muda_Coordenadas (int veti[K], int vetj[K])
{
	// ME BASEIE NA SOLUÇÃO QUE O SENHOR MOSTROU QUANDO TIROU UMA DÚVIDA EM CONJUNTO
	
	int i;
	int Aux[K];
	
	for (i=0; i < K;i++)
		Aux[i] = veti[i];
		
	for (i=0; i < K;i++)
		veti[i] = vetj[i];
		
	for (i=0; i < K;i++)
		vetj[i] = Aux[i];
			
}


void ExibeCoordenadasMatriz (int vet[][K])
{
    for (int i=0; i < TAM;i++)
	{
		printf("(");
		for (int j=0; j < K;j++)
		{
		    if (j == K-1)
		        printf("%d",vet[i][j]);
		    else
		        printf("%d,",vet[i][j]);
		}
		printf(") ");
	}
}


void Ordena (int vet[][K], int inicio, int fim, int Dis)
{
	for (int i=inicio; i < fim; i++)
		for (int j=i+1; j < fim; j++)
			if (vet[i][Dis] > vet[j][Dis]) // TROCA
				Muda_Coordenadas(vet[i],vet[j]);
}




void MostraCoordenada (int Coordenada[K])
{
	printf("(");
	for (int i = 0; i < K; i++)
	{
		if (i == K - 1)
			printf("%d",Coordenada[i]);
		else
			printf("%d,",Coordenada[i]);
	}
	printf(") ");
}




void MostraNaTree (KdTree *KT)
{
	printf("(");
	for (int i = 0; i < K; i++)
	{
		if (i == K - 1)
			printf("%d",KT->ponto[i]);
		else
			printf("%d,",KT->ponto[i]);
	}
	printf(")\n");
}



void ExibeArvoreKdTree (KdTree *KT,int *n)
{
	if(KT != NULL)
	{
		(*n)++;
		ExibeArvoreKdTree(KT->dir,&*n);
		for(int i=0;i<10*(*n);i++)
			printf(" ");
		MostraNaTree(KT);
		ExibeArvoreKdTree(KT->esq,&*n);
		(*n)--;
	}
}


void GeraCoordenada (int Coordenada[K])
{
	for (int i=0; i < K;i++)
		Coordenada[i] = (rand() % MAX) +1;
		
	//Coordenada[0] = 8; Coordenada[1] = 18;
}



///////////////////////////////////////////////////////////


// FUNÇÕES PRINCIPAIS


void EncheVetorRandom (int vet[TAM][K])
{
	for (int i=0; i < TAM; i++)
		for (int j=0; j < K; j++)
			vet[i][j] = (rand() % MAX) + 1;
}


void CriaKdTree (KdTree **KT, int nivel, int inicio, int fim, int vet[][K]) //
{
	int meio,Discriminante;
	if (inicio <= fim)
	{
	    meio = (inicio + fim) / 2;
	
    	Discriminante = nivel % K;
    	
    	Ordena(vet,inicio,fim+1,Discriminante);
    	*KT = CriaNo(vet[meio]);
    	
    	if (inicio < fim)
    	{
    	    CriaKdTree(&(*KT)->esq, nivel+1, inicio, meio-1, vet);
    	    CriaKdTree(&(*KT)->dir, nivel+1, meio+1, fim, vet);
    	}
	}
}


double CalculoDistanciaEuclidiana (KdTree *KT, int Coordenada[K])
{
	double Soma = 0;
	
	for (int i=0; i < K;i++)
		Soma += pow((KT->ponto[i] - Coordenada[i]),2);
		
	return sqrt(Soma);
}



void BuscaPontos (KdTree *KT, int Coordenada[K], int raio)
{
	if (KT != NULL)
	{
		double DE = CalculoDistanciaEuclidiana(KT, Coordenada);
		if (DE <= raio)
		{
			MostraCoordenada(KT->ponto);
			printf("- DistanEucli : %.2lf \n",DE,raio);
			if (KT->dir != NULL)
				BuscaPontos(KT->dir, Coordenada, raio);
		}
		if (KT->esq != NULL)
			BuscaPontos(KT->esq, Coordenada, raio);
	}
}




///////////////////////////////////////////////////////////



// MAIN



int main ()
{
	srand(time(NULL));
	
	KdTree *KT = NULL;
	
	int vet[TAM][K], Coordenada[K], raio;
	
	//EncheVetorChico(vet);
	EncheVetorRandom(vet);
	
	printf(" ### Trabalho KdTree com K Dimensoes ###\n\n\n # CONSTANTES #\n\n DIMENSOES : %d\n NUM_COORDENADAS : %d\n NUM_MAX : %d\n",K,TAM,MAX);
	
	printf("\n\n\nCOORDENADAS GERADAS RANDOMICAMENTE\n\n");
	
	ExibeCoordenadasMatriz(vet);
	
	int Discriminante = rand() % K;
	Ordena(vet,0,TAM,Discriminante);
	printf("\n\n\n'''EXEMPLO''' ORDENADAS PELO DISCRIMINANTE %d / (rand() Percent K)\n\n",Discriminante);
	
    ExibeCoordenadasMatriz(vet);
	
	CriaKdTree(&KT,0,0,TAM-1,vet);
	
	printf("\n\n\n\n\n         ### KDTREE FORMADA ###\n\n\n\n\n"); 
	int n = -1;
	ExibeArvoreKdTree(KT,&n);
	
	GeraCoordenada(Coordenada);
	raio = (rand() % (MAX/2)) + (MAX/5);
	//raio = 10;
	printf("\n\n\n\nCOORDENADA GERADA : ");
	MostraCoordenada(Coordenada);
	printf("RAIO : %d\n\n\n\n",raio);
	printf("COORDENADAS DENTRO DO RAIO :\n\n");
	
	BuscaPontos(KT,Coordenada,raio);
	
	return 0;
}
