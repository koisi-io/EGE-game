/*  *****************************************************

这里是	Main函数  所在的地方

*****************************************************  */

#include "graphics.h"
#include <stdlib.h>
#include<stdio.h>
#include  <math.h>
#include "DBB.h"
#include "Frame.h"
#include "Map.h"
#include "Index.h"

//*******************************************
//			声明区


//	游戏信息
info INFO = {
	1000,
	1,
	1,
	1,
	6,0,0,0,0,
	NULL,
	NULL,
	NULL,
};
info reINFO = {
	1000,
	1,
	1,
	1,
	6,0,0,0,0,
	NULL,
	NULL,
	NULL,
};
dot SK01dot = { -103,-111,0,0,16,8,0 };

//	分数处理
int  baseS = 0;
int  EXS = 1;
int  oldS = 0;
//	游戏设置
int  toPa = 0;
int  toSt = 0;
int  toRe = 0;
int  toSa = 0;
int  ballR = 16;
int  ballr = 16;
int  ballv = 2;
int  SK1hit = 0;
key_msg keyMsg = { 0 };
char charKey;
int  recSP = 0;
const int addSP = 200;

//	游戏流程
void gameCir();
void setCir();
void SaveFun();
void ShowScore(info *pinfo);
void getSkill();
void frSkill();
void getSP();
void acSk01();
void acSk02();
void acSk03();
void acSk04();
int myAbs(int a);
void getSK01dotV(int x, int y, int *px, int *py);


//*******************************************

int main()
{

	//*******************************************
	//			准备工作
	setrendermode(RENDER_MANUAL);
	initgraph(860, 500);

	//********************
	do {


		INFO = reINFO;
		toSt = 0;
		int isNoC = 1;	/*	非通过读档加入游戏	*/
		if (!toRe) {
			isNoC = index(&INFO);
		}
		reINFO = INFO;
		toRe = 0;
		if (isNoC) {
			//************************
			//			地图选择
			InitializeQueue(&INFO.MAP);
			switch (INFO.STAGE)
			{
			case 1:
				INFO.MAP = Map1();
				break;
			case 2:
				INFO.MAP = Map2();
				break;
			case 3:
				INFO.MAP = Map3();
				break;
			case 4:
				INFO.MAP = DiyMap();
				break;
			default:
				break;
			}
			//************************
			switch (INFO.gameV)
			{
			case 1:
				ballv = 2;
				break;
			case 2:
				ballv = 4;
				break;
			case 3:
				ballv = 8;
				break;
			case 4:
				INFO.MAP = DiyMap();
				break;
			default:
				break;
			}
			INFO.DOT = { frameX + 8 * 30,frameY + 8 * 25,ballv,-ballv,ballR,ballr,0 };
			INFO.BOARD = { frameX + 8 * 1,frame_y - 8 * 2,160,12 };
			//*******************************************
		}
		gameCir();

	} while (toSt || toRe);
	//********************
	getch();
	closegraph();
	return 0;
	//*******************************************
}

//*******************************************



void gameCir() {

	Node  *ablock, *tempNode;
	Frame(&INFO);
	int num=0;
	char str[20];
	setviewport(0, 0, frame_x + 5, frame_y + 5);
	//***************
	//		MUS set
	MUSIC musBK02;
	musBK02.OpenFile("MUS\\BK02.WAV");
	MUSIC musSK04;
	musSK04.OpenFile("MUS\\SK04.WAV");
	//***************
	do {

		for (; ; delay_ms(20)) {

			//***************
			//		MUS set
			if (musBK02.GetPlayStatus() == MUSIC_MODE_STOP && INFO.BGM)
				musBK02.Play(0);
			if (!INFO.BGM)
				musBK02.Stop();
		

			if (INFO.sk04 == 62 && INFO.BGM) {
				musSK04.Play(0);
				musBK02.Pause();
			}
			if (musSK04.GetPlayStatus() == MUSIC_MODE_STOP && INFO.BGM)
				musBK02.Play();

			//***************

			setfillcolor(0);
			clearviewport();
			FrameX();
			moveDot(&INFO.DOT);
			drawDot(&INFO.DOT);
			boardV(&INFO.BOARD);
			moveBoard(&INFO.BOARD);
			drawBoard(&INFO.BOARD);

			if (INFO.sk03 != 0)
			{
				acSk03();
				SK3setBoun(&INFO.DOT);

			}
			//**********************
			//			地图相关
			ablock = INFO.MAP.front;
			do {
				baseS += setBoun4(&INFO.DOT, &(ablock->item));
				drawBlock(&(ablock->item));
				tempNode = ablock;
				ablock = ablock->next;
			} while (tempNode->next != NULL);
			//**********************
			//			碰撞处理
			setBoun1(&INFO.DOT);
			setBoun5(&INFO.DOT, &INFO.BOARD);
			//**********************
			//			菜单命令
			setCir();
			if (toPa || toRe || toSt)
				break;
			if (toSa) {
				toSa = 0;
				SaveFun();
			}
			//**********************
			//			技能触发
			getSkill();
			frSkill();
			getSP();

			if (INFO.sk02 != 0)
				acSk02();
			if (INFO.sk04 != 0)
				acSk04();
			if (INFO.sk01 != 0)
				acSk01();

			//**********************
			//			分数处理
			if (INFO.SCORE != oldS) {
				oldS = INFO.SCORE;
				ShowScore(&INFO);
			}
			INFO.SCORE += (baseS*EXS);
			baseS = 0;
			//**********************
			//			结束处理
			if ((INFO.DOT.y - 128) > frame_y) {
				toSt = 1;
				inputbox_getline("You Lose",
					"即将返回开始界面",
					str,
					sizeof(str) / sizeof(*str));
			}
			ablock = INFO.MAP.front;
			do {
				num+=ablock->item.exi;
				tempNode = ablock;
				ablock = ablock->next;
			} while (tempNode->next != NULL);
			if (num == 0) {
				toSt = 1;
				inputbox_getline("You Win",
					"请输入你的昵称：",
					str,
					sizeof(str) / sizeof(*str));

				HSform hs[4];
				loadHS(hs);
				int thisI = INFO.STAGE-1;
				if (INFO.SCORE > hs[thisI].S) {
					hs[thisI].S = INFO.SCORE;
					strcpy(hs[thisI].NAME, str);
				}
				saveHS(hs);
			}
			else
				num = 0;
			//**********************

		}

		if (toSt || toRe)
		{
			delay_ms(100);
			closegraph();
			initgraph(860, 500);
			delay_ms(100);
			break;
		}
		keyMsg = getkey();
		while (keyMsg.key != key_f2 || keyMsg.msg != key_msg_down)
			keyMsg = getkey();
		toPa = 0;

	} while (!toPa);
}
void setCir() {
	if (kbmsg()) {
		keyMsg = getkey();
		if (keyMsg.key == key_f2 &&  keyMsg.msg == key_msg_down)
		{
			toPa = 1;
			getkey();
		}
		else if (keyMsg.key == key_f3 &&  keyMsg.msg == key_msg_down)
		{
			toSa = 1;
			getkey();
		}
		else if (keyMsg.key == key_f4 &&  keyMsg.msg == key_msg_down)
		{
			toRe = 1;
			getkey();
		}
		else if (keyMsg.key == key_f5 &&  keyMsg.msg == key_msg_down)
		{
			toSt = 1;
			getkey();
		}
	}
}
void SaveFun() {
	setviewport(0, 0, 861, 501);
	delay_ms(50);
	gameSave(&INFO);
	setfont(-12, 0, "宋体");
	outtextxy(680, 270, "保存成功！");
	delay_ms(300);
	outtextxy(680, 270, "          ");
	setviewport(0, 0, frame_x + 5, frame_y + 5);
}
void ShowScore(info *pinfo) {
	delay_ms(10);
	setviewport(0, 0, 861, 501);
	char s[7];
	sprintf(s, "%d", pinfo->SCORE);
	setfont(-24, 0, "wordStyle");
	outtextxy(760, 10 + 70, "       ");
	outtextxy(760, 10 + 70, s);
	setviewport(0, 0, frame_x + 5, frame_y + 5);
}
void getSkill() {
	if (kbhit()) {
		charKey = getch();
		if ((charKey == 'q' || charKey == 'Q') && INFO.sk > 0 && INFO.sk01 == 0) {
			INFO.sk01 = 128;
			INFO.sk += 1;
		}
		if ((charKey == 'w' || charKey == 'W') && INFO.sk > 1 && INFO.sk02 == 0) {
			INFO.sk02 = 128;
			INFO.sk -= 2;
		}
		if ((charKey == 'e' || charKey == 'E') && INFO.sk > 1 && INFO.sk03 == 0) {
			INFO.sk03 = 64;
			INFO.sk -= 2;
		}
		if ((charKey == 'r' || charKey == 'R') && INFO.sk > 3 && INFO.sk04 == 0) {
			INFO.sk04 = 64;
			INFO.sk -= 4;

		}
	}
}
void frSkill() {
	setviewport(0, 0, 861, 501);
	skFrame(&INFO);
	reSP_Frame(&INFO);
	SP_Frame(&INFO);
	setviewport(0, 0, frame_x + 5, frame_y + 5);
}
void getSP() {
	recSP++;
	if (recSP > addSP) {
		recSP = 0;
		if (INFO.sk < 11)
			INFO.sk++;
	}
}
void acSk04() {
	INFO.sk04--;
	INFO.DOT.R = 128;
	static Node  *ablock, *tempNode;
	ablock = INFO.MAP.front;
	do {
		baseS += SK4setBlock(&INFO.DOT, &(ablock->item));
		tempNode = ablock;
		ablock = ablock->next;
	} while (tempNode->next != NULL);
	if (INFO.sk04 == 0)
		INFO.DOT.R = ballR;
}
void acSk02() {
	INFO.sk02--;
	INFO.DOT.c = 1;
	INFO.DOT.R = 40;
	INFO.DOT.r = 32;
	EXS = 5;
	if (INFO.sk02 == 0)
	{
		INFO.DOT.c = 0;
		INFO.DOT.R = ballR;
		INFO.DOT.r = ballr;
		EXS = 1;
	}
}
void acSk03() {
	INFO.sk03--;
	if (myAbs(INFO.DOT.Vx) == ballv) {
		INFO.DOT.Vx = 4 * INFO.DOT.Vx;
		INFO.DOT.Vy = 4 * INFO.DOT.Vy;
	}
	static Node  *ablock, *tempNode;
	ablock = INFO.MAP.front;
	do {
		baseS += SK3setBlock(&INFO.DOT, &(ablock->item));
		tempNode = ablock;
		ablock = ablock->next;
	} while (tempNode->next != NULL);
	if (INFO.sk03 == 0)
	{
		INFO.DOT.Vx = INFO.DOT.Vx / 4;
		INFO.DOT.Vy = INFO.DOT.Vy / 4;
	}
}
int myAbs(int a) {
	if (a < 0)
		return -a;
	else
		return a;
}
void acSk01() {

	INFO.sk01--;

	//*****************
	while (SK01dot.Vx == 0 && SK01dot.Vy == 0 && !SK1hit) {
		int dx, dy, newVx, newVy;
		mouse_msg msg;
		while (mousemsg())
			msg = getmouse();
		while (!msg.is_left())
			msg = getmouse();
		if (msg.is_left()) {
			mouseX = msg.x;
			mouseY = msg.y;
		}
		else
			break;
		dx = mouseX - INFO.DOT.x;
		dy = mouseY - INFO.DOT.y;
		getSK01dotV(dx, dy, &newVx, &newVy);
		SK01dot.Vx = newVx;
		SK01dot.Vy = newVy;
	}
	//*****************

	if (SK01dot.x == -103 && SK01dot.y == -111) {
		SK01dot.x = INFO.DOT.x;
		SK01dot.y = INFO.DOT.y;
	}

	//*****************
	if (SK01dot.Vx != 0) {

		MDSK01dot(&SK01dot);
		static Node  *ablock, *tempNode;

		ablock = INFO.MAP.front;

		do {
			SK1hit = setBoun4(&SK01dot, &(ablock->item));
			tempNode = ablock;
			ablock = ablock->next;
		} while (tempNode->next != NULL && !SK1hit);

		if (SK1hit) {
			SK01dot = { -103,-111,0,0,16,8,0 };
			baseS += 24;
		}

	}
	if (INFO.sk01 == 0) {
		SK01dot = { -103,-111,0,0,16,8,0 };
		SK1hit = 0;
	}
}
void getSK01dotV(int x, int y, int *px, int *py) {
	double douX, douY, douXy;
	double Vv = 16 * 16;
	douX = x; douY = y;
	douXy = douX / douY;
	double Vy, Vx;
	double vYY;
	vYY = Vv / (1 + douXy*douXy);

	if (y<0)
		Vy = -sqrt(vYY);
	else
		Vy = sqrt(vYY);

	Vx = douXy*Vy;

	*px = Vx;
	*py = Vy;

}



