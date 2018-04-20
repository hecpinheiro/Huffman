#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no no;
typedef struct filaPrioridade filaP;

struct no
{
	unsigned char item;
	int frequencia;
	no *proximo;
};

struct filaPrioridade
{
	no *cabeca;
};

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
	no *novo = (no*)malloc(sizeof(no));
	novo->item = item;
	novo->frequencia = frequencia;

	if(filaVazia(q) || frequencia > q->cabeca->frequencia)
	{
		novo->proximo = q->cabeca;
		q->cabeca = novo;
	}

	else
	{
		no *atual = q->cabeca;
		while((atual->proximo != NULL) && (atual->proximo->frequencia > frequencia))
		{
			atual = atual->proximo;
		}
		novo->proximo = atual->proximo;
		atual->proximo = novo;
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
	int frequencia[126] = {0};
	filaP *q  = criarfilaP();
	
	while((fscanf(arquivo,"%c",&c)) != EOF)
	{
		frequencia[c]++;
		//printf("%c",c);
	}

	for(i = 0; i < 126; i++)
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