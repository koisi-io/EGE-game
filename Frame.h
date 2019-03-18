/*  *****************************************************

��Ϸʱ�Ľ��������

*****************************************************  */
#ifndef FRAME_H_
#define FRAME_H_

#include "graphics.h"
#include <stdlib.h>
#include<stdio.h>
#include "DBB.h"
#include "Frame.h"
#include "Map.h"
#include "Index.h"
#define wordStyle ����

void mainFrame() {
	setcolor(WHITE);
	rectangle(1, 1, 859, 499);
}
void gameFrame() {
	setcolor(WHITE);
	rectangle(frameX, frameY, frame_x, frame_y);
}
void infoFrame(const info *pinfo) {
	setcolor(WHITE);
	rectangle(660, 10, 850, 290);
	setfont(-24, 0, "wordStyle");
	switch (pinfo->STAGE)
	{
	case 1:
		outtextxy(660 + 20, 10 + 15, "�ؿ���  һ");
		break;
	case 2:
		outtextxy(660 + 20, 10 + 15, "�ؿ���  ��");
		break;
	case 3:
		outtextxy(660 + 20, 10 + 15, "�ؿ���  ��");
		break;
	case 4:
		outtextxy(660 + 20, 10 + 15, "�ؿ���  Diy");
		break;
	default:
		outtextxy(660 + 20, 10 + 15, "�ؿ��� *");
		break;
	}


	setfont(-24, 0, "wordStyle");
	outtextxy(660 + 20, 10 + 70, "������");

	setfont(-16, 0, "wordStyle");
	outtextxy(660 + 60, 10 + 125, "	F2 :   ��ͣ  ");
	outtextxy(660 + 60, 10 + 145, "	F3 :   �浵");
	outtextxy(660 + 60, 10 + 165, "	F4 :   ���¿�ʼ");
	outtextxy(660 + 60, 10 + 185, "	F5 :   ���ز˵�");

}

void SP_Frame(const info *pinfo) {
	for (int i = 0; i < 10; i++) {
		setcolor(WHITE);
		rectangle(685 + i * 15, 240, 700 + i * 15, 255);
		if (i < pinfo->sk) {
			if (pinfo->sk >5)
				setfillcolor(LIGHTCYAN);
			else
				setfillcolor(LIGHTRED);
			floodfill(687 + i * 15, 242, WHITE);
		}
	}
}
void skillFrame1(const info *pinfo) {

	if (pinfo->sk01 == 0 && pinfo->sk >0)
		setcolor(GREEN);
	else
		setcolor(WHITE);
	rectangle(660, 300, 750, 390);
	PIMAGE img = newimage();
	getimage(img, "pic\\skill01.jpg");
	putimage(673, 313, img);
}
void skillFrame2(const info *pinfo) {

	if (pinfo->sk02 == 0 && pinfo->sk >1)
		setcolor(GREEN);
	else
		setcolor(WHITE);
	rectangle(760, 300, 850, 390);
	PIMAGE img = newimage();
	getimage(img, "pic\\skill02.jpg");
	putimage(773, 313, img);

}
void skillFrame3(const info *pinfo) {
	if (pinfo->sk03 == 0 && pinfo->sk >1)
		setcolor(GREEN);
	else
		setcolor(WHITE);
	rectangle(660, 400, 750, 490);
	PIMAGE img = newimage();
	getimage(img, "pic\\skill03.jpg");
	putimage(673, 413, img);
}
void skillFrame4(const info *pinfo) {
	if (pinfo->sk02 == 0 && pinfo->sk >3)
		setcolor(GREEN);
	else
		setcolor(WHITE);
	rectangle(760, 400, 850, 490);
	PIMAGE img = newimage();
	getimage(img, "pic\\skill04.jpg");
	putimage(773, 413, img);
}
void skFrame(const info *pinfo) {
	if (pinfo->sk01 == 0 && pinfo->sk >0)
		setcolor(GREEN);
	else
		setcolor(WHITE);
	rectangle(660, 300, 750, 390);
	if (pinfo->sk02 == 0 && pinfo->sk >1)
		setcolor(GREEN);
	else
		setcolor(WHITE);
	rectangle(760, 300, 850, 390);
	if (pinfo->sk03 == 0 && pinfo->sk >1)
		setcolor(GREEN);
	else
		setcolor(WHITE);
	rectangle(660, 400, 750, 490);
	if (pinfo->sk04 == 0 && pinfo->sk >3)
		setcolor(GREEN);
	else
		setcolor(WHITE);
	rectangle(760, 400, 850, 490);
}
void reSP_Frame(const info *pinfo) {
	for (int i = 0; i < 10; i++) {
		setcolor(WHITE);
		rectangle(685 + i * 15, 240, 700 + i * 15, 255);
		setfillcolor(0);
		floodfill(687 + i * 15, 242, WHITE);

	}
}

void Frame(const info *pinfo) {
	mainFrame();
	gameFrame();
	infoFrame(pinfo);
	SP_Frame(pinfo);
	skillFrame1(pinfo);
	skillFrame2(pinfo);
	skillFrame3(pinfo);
	skillFrame4(pinfo);
}

void FrameX() {
	mainFrame();
	gameFrame();
}


#endif
