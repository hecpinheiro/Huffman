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


// DEBUG
void printQueue(priorityQueue *q)
{
	node *aux;
	for(aux = q->head; aux != NULL; aux = aux->next)
	{
		printf("%c|%d\n",aux->c,aux->frequency);
	}
}

void print_pre_order(node *tree)
{
	if (tree != NULL) {
		printf("%c|%d\n", tree->c,tree->frequency);
		print_pre_order(tree->left);
		print_pre_order(tree->right);
	}
}

//END

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

void queue(priorityQueue *q, node *new)
{
	if(is_empty(q) || new->frequency < q->head->frequency)
	{
		new->next = q->head;
		q->head = new;
	}

	else
	{
		node *current = q->head;
		while((current->next != NULL) && (current->next->frequency < new->frequency))
		{
			current = current->next;
		}
		new->next = current->next;
		current->next = new;
	}
}

void dequeue(priorityQueue *q)
{

	int i;

	if(is_empty(q))
	{
		printf("Queue is empty\n");
	}
	else
	{	
		for (i = 0; i < 2; ++i)
		{
			node *new = q->head;
			q->head = q->head->next;
			new->next = NULL;
		}

	}
}

void getByteFrequency(FILE *file, int *frequency)
{
	unsigned char c;

	while((fscanf(file,"%c",&c)) != EOF)
	{
		frequency[c]++;
	}

}

void addToQueue(priorityQueue *q, int *frequency)
{
	unsigned int i;

	for(i = 0; i < 256; i++)
	{
		if(frequency[i])
		{
			node* node = createNode(i,frequency[i]);
			queue(q, node); 		
		}
	}
}

int sizeQueue(priorityQueue *q)
{
	int i;
	node *aux = q->head;

	for(i = 0; aux != NULL; i++)
	{
		aux = aux->next;
	}

	return i;
}

void createHuffmanTree(priorityQueue *q)
{
	if(sizeQueue(q) == 1) return;

	node *child1 = q->head;
	node *child2 = q->head->next;
	node *new = createNode('*',child1->frequency + child2->frequency);

	new->left = child1;
	new->right = child2;

	dequeue(q);
	queue(q,new);

	createHuffmanTree(q);
}

int is_child(node *t)
{
	if(t->right == NULL && t->left == NULL) return 1;
	else return 0;
}

void getcodeMap(int *codeMap[][256], priorityQueue *q)
{
	int i = 0;
	node *aux = q->head;

}

int compress(FILE *file)
{
	int frequency[256] = {0};
	unsigned char codeMap[10][256]= {0};
	priorityQueue *q  = createQueue();

	getByteFrequency(file, frequency);
	addToQueue(q,frequency);
	createHuffmanTree(q);

	//DEBUG
	printf("PRINT QUEUE ESTADO FINAL\n");
	printQueue(q);
	printf("FIM DA QUEUE\n");
	printf("PRINT DA ARVORE ESTADO FINAL");
	print_pre_order(q->head);
	printf("FIM DA ARVORE\n");
	//END
}

int main()
{
	FILE *file;
	file = fopen("teste.txt","rb");
	compress(file);
	fclose(file);	
}	
