#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comprimir(FILE *arquivo)
{
	unsigned char c;
	//Leitura do arquivo
	while((fscanf(arquivo,"%c",&c)) != EOF)
	{
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