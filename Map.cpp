#include "Map.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

static void CopyToNode(Item item, Node *pn);
static void CopyToItem(Node *pn, Item *pi);

void InitializeQueue(Queue *pq) {
	pq->front = pq->rear = NULL;
	pq->items = 0;
}

bool QueueIsFull(const Queue *pq) {
	return pq->items == MAXQUEUE;
}

bool QueueIsEmpty(const Queue *pq) {
	return pq->items == 0;
}

int QueueItemCount(const Queue *pq) {
	return pq->items;
}

bool EnQueue(Item item, Queue *pq) {
	Node *pnew;
	if (QueueIsFull(pq))
		return false;
	pnew = (Node *)malloc(sizeof(Node));
	if (pnew == NULL)
	{
		fprintf(stderr, "Unable to allocate memory!\n");
		exit(1);
	}
	CopyToNode(item, pnew);
	pnew->next = NULL;
	if (QueueIsEmpty(pq))
		pq->front = pnew;
	else
		pq->rear->next = pnew;
	pq->rear = pnew;
	pq->items++;

	return true;
}

bool DeQueue(Item *pitem, Queue *pq) {
	Node *pt;

	if (QueueIsEmpty(pq))
		return false;
	CopyToItem(pq->front, pitem);
	pt = pq->front;
	pq->front = pq->front->next;
	free(pt);
	pq->items--;
	if (pq->items == 0)
		pq->rear = NULL;
	return true;
}

void EmptyQueue(Item item, Queue *pq) {
	Item dummy = {
		0,0,0,0,
		0,0,0
	};
	while (!QueueIsEmpty(pq))
		DeQueue(&dummy, pq);
}

void CopyToNode(Item item, Node *pn) {
	pn->item = item;
}

void CopyToItem(Node *pn, Item *pi) {
	*pi = pn->item;
}

//*****************************************************
//			µØÍ¼ÖÆ×÷
Queue Map1() {
	Queue map;
	InitializeQueue(&map);
	block Blocks[15][7];
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 7; j++) {
			Blocks[i][j] = {
				frameX + 40 + j * blockW ,	//x
				frameY + 24 + i * blockH ,	//y
				blockW,		//w
				blockH,		//h
				1,		//vis
				1,		//exi
				1		//type
			};
			EnQueue(Blocks[i][j], &map);
		}
	return map;
}

Queue Map2() {
	Queue map;
	InitializeQueue(&map);
	block Blocks[5][7];
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 7; j++) {
			Blocks[i][j] = {
				frameX + 40 + j * blockW ,	//x
				frameY + 24 + i * blockH ,	//y
				blockW,		//w
				blockH,		//h
				1,		//vis
				1,		//exi
				1		//type
			};
			EnQueue(Blocks[i][j], &map);
		}
	return map;
}

Queue Map3() {
	Queue map;
	InitializeQueue(&map);
	block Blocks[15][7];
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 7; j++) {
			Blocks[i][j] = {
				frameX + 40 + j * blockW ,	//x
				frameY + 24 + i * blockH ,	//y
				blockW,		//w
				blockH,		//h
				1,		//vis
				1,		//exi
				1		//type
			};
			EnQueue(Blocks[i][j], &map);
		}
	return map;
}

Queue DiyMap() {

	Queue map;
	InitializeQueue(&map);
	block ablock;
	FILE *in;

	char test[] = "diy.txt";

	if ((in = fopen(test, "r")) == NULL) {
		fprintf(stderr, "Failed to open the file.\n");
		exit(73);
	}
	//********************************
	char ch;
	int i = 0;
	int j = 0;
	while ((ch = getc(in)) != EOF) {
		if (ch == 'b') {
			ch = getc(in);
			ablock = {
				frameX + 40 + j * blockW ,	//x
				frameY + 24 + i * blockH ,	//y
				blockW,		//w
				blockH,		//h
				0,		//vis
				0,		//exi
				0		//type
			};
			if (isdigit(ch)) {
				ablock.vis = CHtoINT(ch);
				ch = getc(in);
				if (isdigit(ch)) {
					ablock.exi = CHtoINT(ch);
					ch = getc(in);
					if (isdigit(ch))
						ablock.type = CHtoINT(ch);
				}
			}
			EnQueue(ablock, &map);
			j++;
		}
		if (j == 7) {
			while (ch != '\n')
				ch = getc(in);
		}
		if (ch == '\n') {
			i++;
			j = 0;
		}
		if (i == 15)
			break;
	}
	//********************************
	if (fclose(in) != 0) {
		fprintf(stderr, "Error in closing files\n");
		exit(74);
	}

	return map;
}

int CHtoINT(char ch) {
	switch (ch)
	{
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	default:
		break;
	}
}