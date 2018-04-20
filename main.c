#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef no no;
typedef filaPrioridade filaP;

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

filaP *criarfilaPrioridade(void)
{
	filaP *f = (filaP*)malloc(sizeof(filaP));
	f->cabeca = NULL;
	return f;
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
		//Procurar a posição e add
	}
}

int comprimir(FILE *arquivo)
{
	unsigned char c;
	int frequencia[126] = {0};
	
	while((fscanf(arquivo,"%c",&c)) != EOF)
	{
		frequencia[c]++;
		//Inserir fila
		//Se item ==, então atualizar frequencia.
		printf("%c",c);
	}
}

int main()
{
	FILE *arquivo;
	arquivo = fopen("teste.txt","rb");
	comprimir(arquivo);
	fclose(arquivo);
}	