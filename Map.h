/*  *****************************************************

这里是关于  地图编辑  的声明
采用单向链表的方法来构造

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
	Node *front;		/*		头部		*/
	Node *rear;         /*		尾部		*/
	int items;          /*		个数		*/
}Queue;

//*****************************************************
//			基本工具

//			初始
void InitializeQueue(Queue *pq);

//			查满
bool QueueIsFull(const Queue *pq);

//			查空
bool QueueIsEmpty(const Queue *pq);

//			查数
int QueueItemCount(const Queue *pq);

//			添尾
bool EnQueue(Item item, Queue *pq);

//			删首
bool DeQueue(Item *pitem, Queue *pq);

//			清空
void EmptyQueue(Item item, Queue *pq);

//			迭代
//void QueueIterator(const Queue *ptree, void(*pfun)(Item item));

//*****************************************************
//			地图制作

Queue Map1();
Queue Map2();
Queue Map3();
Queue DiyMap();
int CHtoINT(char ch);

#endif
