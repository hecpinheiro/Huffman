#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;
typedef struct priorityQueue priorityQueue;

struct node
{
	unsigned char c;
	int frequency;
	node *next;
	node *left;
	node *right;
};

struct priorityQueue
{
	node *head;
};

no *criarNo(char unsigned item, int frequencia)
{
	no *novo = (no*)malloc(sizeof(no));
	novo->item = item;
	novo->frequencia = frequencia;
	novo->esquerda = NULL;
	novo->direita = NULL;
	return novo;
}

int filaVazia(filaP *q)
{
	if(q->cabeca == NULL) return 1;
	else return 0;
}

filaP *criarfilaP(void)
{
	filaP *q = (filaP*)malloc(sizeof(filaP));
	q->cabeca = NULL;
	return q;
}

void inserirfilaP(filaP *q, char unsigned item, int frequencia)
{
	no *novo = criarNo(item, frequencia);

	if(filaVazia(q) || frequencia < q->cabeca->frequencia)
	{
		novo->proximo = q->cabeca;
		q->cabeca = novo;
	}

	else
	{
		no *atual = q->cabeca;
		while((atual->proximo != NULL) && (atual->proximo->frequencia < frequencia))
		{
			atual = atual->proximo;
		}
		novo->proximo = atual->proximo;
		atual->proximo = novo;
	}
}

no *removerfilaP(filaP *q)
{
	if(filaVazia(q))
	{
		printf("Fila vazia\n");
	}
	else
	{	
		no *novo = q->cabeca;
		q->cabeca = q->cabeca->proximo;
		novo->proximo = NULL;
		return novo;
	}
}

void imprimefilaP(filaP *q)
{
	no *auxiliar;
	for(auxiliar = q->cabeca; auxiliar != NULL; auxiliar = auxiliar->proximo)
	{
		printf("%c|%d\n",auxiliar->item,auxiliar->frequencia);
	}
}

int comprimir(FILE *arquivo)
{
	unsigned char c;
	unsigned int i;
	int frequencia[256] = {0};
	filaP *q  = criarfilaP();
	
	while((fscanf(arquivo,"%c",&c)) != EOF)
	{
		frequencia[c]++;
	}

	for(i = 0; i < 256; i++)
	{
		if(frequencia[i])
		{
			inserirfilaP(q, i, frequencia[i]);
		}
	}

	imprimefilaP(q);
}

int main()
{
	FILE *arquivo;
	arquivo = fopen("teste.txt","rb");
	comprimir(arquivo);
	fclose(arquivo);
}	