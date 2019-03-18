/*  *****************************************************

�����ǹ���  ��ͼ�༭  ������
���õ�������ķ���������

*****************************************************  */




#ifndef MAP_H_
#define MAP_H_

#include "DBB.h"
#include <stdbool.h>

typedef block Item;
#define MAXQUEUE 105


typedef struct node {
	Item item;
	struct node *next;
}Node;

typedef struct queue {
	Node *front;		/*		ͷ��		*/
	Node *rear;         /*		β��		*/
	int items;          /*		����		*/
}Queue;

//*****************************************************
//			��������

//			��ʼ
void InitializeQueue(Queue *pq);

//			����
bool QueueIsFull(const Queue *pq);

//			���
bool QueueIsEmpty(const Queue *pq);

//			����
int QueueItemCount(const Queue *pq);

//			��β
bool EnQueue(Item item, Queue *pq);

//			ɾ��
bool DeQueue(Item *pitem, Queue *pq);

//			���
void EmptyQueue(Item item, Queue *pq);

//			����
//void QueueIterator(const Queue *ptree, void(*pfun)(Item item));

//*****************************************************
//			��ͼ����

Queue Map1();
Queue Map2();
Queue Map3();
Queue DiyMap();
int CHtoINT(char ch);

#endif
