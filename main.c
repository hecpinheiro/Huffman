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

node *createNode(char unsigned c, int frequency)
{
	node *new = (node*)malloc(sizeof(node));
	new->c = c;
	new->frequency = frequency;
	new->left = NULL;
	new->right = NULL;
	return new;
}

int is_empty(priorityQueue *q)
{
	if(q->head == NULL) return 1;
	else return 0;
}

priorityQueue *createQueue(void)
{
	priorityQueue *q = (priorityQueue*)malloc(sizeof(priorityQueue));
	q->head = NULL;
	return q;
}

void queue(priorityQueue *q, char unsigned c, int frequency)
{
	node *new = createNode(c, frequency);

	if(is_empty(q) || frequency < q->head->frequency)
	{
		new->next = q->head;
		q->head = new;
	}

	else
	{
		node *current = q->head;
		while((current->next != NULL) && (current->next->frequency < frequency))
		{
			current = current->next;
		}
		new->next = current->next;
		current->next = new;
	}
}

node *dequeue(priorityQueue *q)
{
	if(is_empty(q))
	{
		printf("Queue is empty\n");
	}
	else
	{	
		node *new = q->head;
		q->head = q->head->next;
		new->next = NULL;
		return new;
	}
}

void printQueue(priorityQueue *q)
{
	node *aux;
	for(aux = q->head; aux != NULL; aux = aux->next)
	{
		printf("%c|%d\n",aux->c,aux->frequency);
	}
}

void getByteFrequency(FILE *file, int *frequency)
{

	while((fscanf(file,"%c",&c)) != EOF)
	{
		frequency[c]++;
	}

}

int compress(FILE *file)
{
	unsigned char c;
	unsigned int i;
	int frequency[256] = {0};
	priorityQueue *q  = createQueue();

	getByteFrequency(file, frequency);
	
	for(i = 0; i < 256; i++)
	{
		if(frequency[i])
		{
			queue(q, i, frequency[i]);
		}
	}

	printQueue(q);
}

int main()
{
	FILE *file;
	file = fopen("teste.txt","rb");
	compress(file);
	fclose(file);	
}	