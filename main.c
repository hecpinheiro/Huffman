#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *arquivo;
	unsigned int c;

	arquivo = fopen("teste.txt","rb");

	while((c = fgetc(arquivo)) != EOF)
	{
		printf("%c",c);
	}
}