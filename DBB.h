/*  *****************************************************

�����ǹ���  DBB ��dot��board��block��  ������

*****************************************************  */

#ifndef DBB_H_
#define DBB_H_

//*****************************************************
//		CONST
#define frameX 10		//��������
#define frameY 10
#define frame_x 650		//��������
#define frame_y 490
#define blockW 80
#define blockH 24
#define board_V 4

//*****************************************************
//		DOT

struct dot {
	int x;
	int y;
	int Vx;
	int Vy;
	int R;
	int r;
	int c;  //״̬
};

void moveDot(dot *adot);

void drawDot(const dot *adot);

//*****************************************************
//		BOARD

struct board {
	int x, y;//���϶���
	int w, h;
	int V;
};

struct board;

void drawBoard(const board *aboard);

void moveBoard(board *aboard);

void boardV(board *aboard);

//*****************************************************
//		BLOCK

struct block {
	int x, y;
	int w, h;
	int vis;
	int exi;
	int type;
};

void drawBlock(const block *ablock);

//*****************************************************
//		FUN

//		��߽���ײ
void setBoun1(dot *adot);
//		��װ���ײ	�� δ����
void setBoun2(dot *adot, const board *aboard);
//		��ʵ����ײ	�� δ����
void setBoun3(dot *adot, block *ablock);
//		��ʵ����ײ	���Ƕ��� ����
int setBoun4(dot *adot, block *ablock);
//		��װ���ײ	���Ƕ��� ����
void setBoun5(dot *adot, const board *aboard);

int SK4setBlock(dot *adot, block *ablock);
int SK3setBlock(dot *adot, block *ablock);
void SK3setBoun(dot *adot);
void MDSK01dot(dot *adot);



#endif 

