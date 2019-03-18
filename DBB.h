/*  *****************************************************

这里是关于  DBB （dot、board、block）  的声明

*****************************************************  */

#ifndef DBB_H_
#define DBB_H_

//*****************************************************
//		CONST
#define frameX 10		//左上坐标
#define frameY 10
#define frame_x 650		//右下坐标
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
	int c;  //状态
};

void moveDot(dot *adot);

void drawDot(const dot *adot);

//*****************************************************
//		BOARD

struct board {
	int x, y;//左上顶点
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

//		与边界碰撞
void setBoun1(dot *adot);
//		与底板碰撞	旧 未采用
void setBoun2(dot *adot, const board *aboard);
//		与实块碰撞	旧 未采用
void setBoun3(dot *adot, block *ablock);
//		与实块碰撞	考虑顶点 采用
int setBoun4(dot *adot, block *ablock);
//		与底板碰撞	考虑顶点 采用
void setBoun5(dot *adot, const board *aboard);

int SK4setBlock(dot *adot, block *ablock);
int SK3setBlock(dot *adot, block *ablock);
void SK3setBoun(dot *adot);
void MDSK01dot(dot *adot);



#endif 

