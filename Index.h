/*  *****************************************************

这里是游戏前界面设计
含S/L Fun

*****************************************************  */

#ifndef INDEX_H_
#define INDEX_H_
#include "graphics.h"
#include <stdbool.h>
#include "DBB.h"

//*****************************
static int mouseX = 0;
static int mouseY = 0;
static int VFx = 0;
static int VFy = 0;
static int isInFrame(int mx, int my, int X, int Y, int x, int y);
int asdsa = 0;
struct info {
	int SCORE;
	int STAGE;
	int gameV;
	int BGM;
	int sk, sk01, sk02, sk03, sk04;
	Queue MAP;
	dot DOT;
	board BOARD;
};
struct HSform {
	int  S;
	char NAME[20];
};
HSform aHS = { 0,"###" };


//*****************************
void gameSave(info *pinfo);
void gameLoad(info *pinfo);
//*****************************

static void loadHS(HSform *hsf) {
	const char *file = "saveHS.poi";
	FILE *savefile;
	if ((savefile = fopen(file, "rb")) == NULL) {
		fprintf(stderr, "Could not open %s for random access.\n", file);
		for (int i = 0; i < 4; i++) {
			hsf[i] = aHS;			
		}
		return;
	}
	for (int i = 0; i < 4; i++) {
		fread(&hsf[i], sizeof(HSform), 1, savefile);
	}
	fclose(savefile);
}
void saveHS(const HSform *hsf) {
	const char *file = "saveHS.poi";
	FILE *savefile;
	if ((savefile = fopen(file, "wb")) == NULL) {
		fprintf(stderr, "Could not open %s for output.\n", file);
		exit(71);
	}
	for (int i = 0; i < 4; i++) {
		fwrite(&hsf[i], sizeof(HSform), 1, savefile);
	}
	fclose(savefile);
}

static void setBkpic() {
	PIMAGE img = newimage();
	getimage(img, "pic\\IndexBK.png");
	putimage(0, 0, img);
	delimage(img);
}
static int StartFrame() {
	setcolor(WHITE);
	rectangle(230, 50, 630, 200);


	PIMAGE imgdest = newimage();
	PIMAGE imgsrc = newimage();
	int picSet = 0x50;
	getimage(imgsrc, "pic\\IndexBK.png");
	getimage(imgdest, "pic\\Start.PNG");
	putimage_alphablend(imgdest, imgsrc, 0, 0, picSet, 250, 55, 0, 0);
	putimage(250, 55, imgdest);
	delimage(imgsrc);
	delimage(imgdest);

	if (isInFrame(mouseX, mouseY, 230, 50, 630, 200))
		return 1;
	else
		return 0;


}
static int LoadFrame() {
	setcolor(WHITE);
	rectangle(100, 260, 240, 300);
	PIMAGE imgdest = newimage();
	PIMAGE imgsrc = newimage();
	int picSet = 0x50;
	getimage(imgsrc, "pic\\IndexBK.png");
	getimage(imgdest, "pic\\dudang.PNG");
	putimage_alphablend(imgdest, imgsrc, 0, 0, picSet, 110, 262, 0, 0);
	putimage(110, 262, imgdest);
	delimage(imgsrc);
	delimage(imgdest);


	if (isInFrame(mouseX, mouseY, 100, 260, 240, 300))
		return 1;
	else
		return 0;

}
static int HSFrame() {
	setcolor(WHITE);
	rectangle(100, 340, 240, 380);
	PIMAGE imgdest = newimage();
	PIMAGE imgsrc = newimage();
	int picSet = 0x50;
	getimage(imgsrc, "pic\\IndexBK.png");
	getimage(imgdest, "pic\\gaofen.PNG");
	putimage_alphablend(imgdest, imgsrc, 0, 0, picSet, 110, 342, 0, 0);
	putimage(110, 342, imgdest);
	delimage(imgsrc);
	delimage(imgdest);
	if (isInFrame(mouseX, mouseY, 100, 340, 240, 380))
		return 1;
	else
		return 0;

}
static int HelpFrame() {
	setcolor(WHITE);
	rectangle(100, 420, 240, 460);
	PIMAGE imgdest = newimage();
	PIMAGE imgsrc = newimage();
	int picSet = 0x50;
	getimage(imgsrc, "pic\\IndexBK.png");
	getimage(imgdest, "pic\\bangzhu.PNG");
	putimage_alphablend(imgdest, imgsrc, 0, 0, picSet, 110, 422, 0, 0);
	putimage(110, 422, imgdest);
	delimage(imgsrc);
	delimage(imgdest);

	if (isInFrame(mouseX, mouseY, 100, 420, 240, 460))
		return 1;
	else
		return 0;
}
static void MapFrame(info *pinfo) {
	setcolor(WHITE);
	int x, y;
	x = 480;
	y = 300;
	int picSet;
	PIMAGE imgdest = newimage();
	PIMAGE imgsrc = newimage();
	getimage(imgsrc, "pic\\IndexBK.png");

	picSet = 0x30;
	getimage(imgdest, "pic\\stage.png");
	putimage_alphablend(imgdest, imgsrc, 0, 0, picSet, x - 120, y - 12, 0, 0);
	putimage(x - 120, y - 12, imgdest);


	rectangle(x, y, x + 40, y + 40);
	if (isInFrame(mouseX, mouseY, x, y, x + 40, y + 40) || pinfo->STAGE == 1) {
		pinfo->STAGE = 1;
		picSet = 0x10;
	}
	else
		picSet = 0x50;
	getimage(imgdest, "pic\\num1.png");
	putimage_alphablend(imgdest, imgsrc, 0, 0, picSet, x + 2, y + 2, 0, 0);
	putimage(x + 2, y + 2, imgdest);


	rectangle(x + 80, y, x + 120, y + 40);
	if (isInFrame(mouseX, mouseY, x + 80, y, x + 120, y + 40) || pinfo->STAGE == 2) {
		pinfo->STAGE = 2;
		picSet = 0x10;
	}
	else
		picSet = 0x50;
	getimage(imgdest, "pic\\num2.png");
	putimage_alphablend(imgdest, imgsrc, 0, 0, picSet, x + 80 + 2, y + 2, 0, 0);
	putimage(x + 80 + 2, y + 2, imgdest);


	rectangle(x + 160, y, x + 200, y + 40);
	if (isInFrame(mouseX, mouseY, x + 160, y, x + 200, y + 40) || pinfo->STAGE == 3) {
		pinfo->STAGE = 3;
		picSet = 0x10;
	}
	else
		picSet = 0x50;
	getimage(imgdest, "pic\\num3.png");
	putimage_alphablend(imgdest, imgsrc, 0, 0, picSet, x + 160 + 2, y + 2, 0, 0);
	putimage(x + 160 + 2, y + 2, imgdest);


	rectangle(x + 240, y, x + 280, y + 40);
	if (isInFrame(mouseX, mouseY, x + 240, y, x + 280, y + 40) || pinfo->STAGE == 4) {
		pinfo->STAGE = 4;
		picSet = 0x10;
	}
	else
		picSet = 0x50;
	getimage(imgdest, "pic\\diy.png");
	putimage_alphablend(imgdest, imgsrc, 0, 0, picSet, x + 240 + 2, y + 2, 0, 0);
	putimage(x + 240 + 2, y + 2, imgdest);

	delimage(imgsrc);
	delimage(imgdest);
}
static void VFrame(info *pinfo) {



	setcolor(WHITE);
	int x, y;
	x = 480;
	y = 380;
	int picSet;
	PIMAGE imgdest = newimage();
	PIMAGE imgsrc = newimage();
	getimage(imgsrc, "pic\\IndexBK.png");


	picSet = 0x30;
	getimage(imgdest, "pic\\speed.png");
	putimage_alphablend(imgdest, imgsrc, 0, 0, picSet, x - 120, y - 12, 0, 0);
	putimage(x - 120, y - 12, imgdest);

	rectangle(x, y, x + 40, y + 40);
	if (isInFrame(mouseX, mouseY, x, y, x + 40, y + 40) || pinfo->gameV == 1) {
		pinfo->gameV = 1;
		picSet = 0x10;
	}
	else
		picSet = 0x50;
	getimage(imgdest, "pic\\num1.png");
	putimage_alphablend(imgdest, imgsrc, 0, 0, picSet, x + 2, y + 2, 0, 0);
	putimage(x + 2, y + 2, imgdest);


	rectangle(x + 80, y, x + 120, y + 40);
	if (isInFrame(mouseX, mouseY, x + 80, y, x + 120, y + 40) || pinfo->gameV == 2) {
		pinfo->gameV = 2;
		picSet = 0x10;
	}
	else
		picSet = 0x50;
	getimage(imgdest, "pic\\num2.png");
	putimage_alphablend(imgdest, imgsrc, 0, 0, picSet, x + 80 + 2, y + 2, 0, 0);
	putimage(x + 80 + 2, y + 2, imgdest);


	rectangle(x + 160, y, x + 200, y + 40);
	if (isInFrame(mouseX, mouseY, x + 160, y, x + 200, y + 40) || pinfo->gameV == 3) {
		pinfo->gameV = 3;
		picSet = 0x10;
	}
	else
		picSet = 0x50;
	getimage(imgdest, "pic\\num3.png");
	putimage_alphablend(imgdest, imgsrc, 0, 0, picSet, x + 160 + 2, y + 2, 0, 0);
	putimage(x + 160 + 2, y + 2, imgdest);


	rectangle(x + 240, y, x + 280, y + 40);

	if (isInFrame(mouseX, mouseY, x + 240, y, x + 280, y + 40) && mouseX != VFx && mouseY != VFy) {
		VFx = mouseX;
		VFy = mouseY;
		if (pinfo->BGM == 1)
			pinfo->BGM = 0;
		else
			pinfo->BGM = 1;
	}
	if (pinfo->BGM == 1)
		picSet = 0x10;
	else
		picSet = 0x50;
	getimage(imgdest, "pic\\BGM.png");
	putimage_alphablend(imgdest, imgsrc, 0, 0, picSet, x + 240 + 2, y + 2, 0, 0);
	putimage(x + 240 + 2, y + 2, imgdest);

	delimage(imgsrc);
	delimage(imgdest);

}
static int isInFrame(int mx, int my, int X, int Y, int x, int y) {
	if (mx > X && mx<x && my>Y && my < y)
		return 1;
	else
		return 0;
}
static void HelpView() {
	PIMAGE img = newimage();
	getimage(img, "pic\\HV.png");
	putimage(0, 0, img);
	delimage(img);
	getch();
	delay_ms(30);
}
static void ScoreView() {
	cleardevice();
	rectangle(5, 5, 855, 495);
	setfont(-32, 0, "宋体");

	HSform hs[4];
	loadHS(hs);
	for (int i = 0; i < 4; i++) {
		setcolor(WHITE);
		char s1[] = "Stage ";
		outtextxy(220, 30+i*100, s1);
		char s11[4];
		sprintf(s11, "%d", i+1);
		outtextxy(340, 30 + i * 100, s11);
		setcolor(LIGHTGREEN);
		char s12[16];
		sprintf(s12, "%d", hs[i].S);
		outtextxy(430, 70 + i * 100, s12);
	
		outtextxy(600, 70 + i * 100, hs[i].NAME);

	}
	setcolor(WHITE);
	setfont(-20, 0, "宋体");
	char s4[] = "按任意键返回开始菜单";
	outtextxy(600, 450, s4);

	saveHS(hs);
	getch();
}

int index(info *pinfo) {
	int toStart = 0;
	int toHelp = 0;
	int toLoad = 0;
	int toHigh = 0;

	
		MUSIC mus;
		mus.OpenFile("MUS\\BK01.WAV");

	do {

	
		if (mus.GetPlayStatus() == MUSIC_MODE_STOP && pinfo->BGM) 
			mus.Play(0);
		if (!pinfo->BGM)
			mus.Stop();

		mouse_msg msg;
		while (mousemsg()) {
			msg = getmouse();
			if (msg.is_left()) {
				mouseX = msg.x;
				mouseY = msg.y;
				break;
			}
		}


		cleardevice();
		setBkpic();
		toStart = StartFrame();
		toLoad = LoadFrame();
		toHigh = HSFrame();
		toHelp = HelpFrame();
		MapFrame(pinfo);
		VFrame(pinfo);


		delay_ms(30);
		mouseX = 0;
		mouseY = 0;
		delay_ms(30);


		if (toStart) {
			delay_ms(30);
			break;
		}
		if (toLoad) {
			delay_ms(30);
			break;
		}
		if (toHelp) {
			HelpView();
			toHelp = 0;
		}
		if (toHigh) {
			ScoreView();
			toHigh = 0;
		}


	} while (1);

	if (toLoad) {
		gameLoad(pinfo);
		cleardevice();
		return 0;
	}

	cleardevice();
	return 1;

}

void gameLoad(info *pinfo) {
	const char *file = "save.poi";
	FILE *savefile;
	if ((savefile = fopen(file, "rb")) == NULL) {
		fprintf(stderr, "Could not open %s for random access.\n", file);
		exit(72);
	}
	fread(&(pinfo->SCORE), sizeof(int), 1, savefile);
	fread(&(pinfo->STAGE), sizeof(int), 1, savefile);
	fread(&(pinfo->gameV), sizeof(int), 1, savefile);
	fread(&(pinfo->BGM), sizeof(int), 1, savefile);
	fread(&(pinfo->sk), sizeof(int), 1, savefile);
	fread(&(pinfo->sk01), sizeof(int), 1, savefile);
	fread(&(pinfo->sk02), sizeof(int), 1, savefile);
	fread(&(pinfo->sk03), sizeof(int), 1, savefile);
	fread(&(pinfo->sk04), sizeof(int), 1, savefile);
	fread(&(pinfo->MAP.items), sizeof(int), 1, savefile);

	fread(&(pinfo->DOT), sizeof(dot), 1, savefile);
	fread(&(pinfo->BOARD), sizeof(board), 1, savefile);

	//Map
	Queue map;
	InitializeQueue(&map);
	block ablock;
	int n = pinfo->MAP.items;
	for (int i = 0; i < n; i++) {
		fread(&ablock, sizeof(block), 1, savefile);
		EnQueue(ablock, &map);
	}
	pinfo->MAP = map;

	fclose(savefile);


}
void gameSave(info *pinfo) {
	const char *file = "save.poi";
	FILE *savefile;
	if ((savefile = fopen(file, "wb")) == NULL) {
		fprintf(stderr, "Could not open %s for output.\n", file);
		exit(71);
	}
	int num[10] = {
		pinfo->SCORE,pinfo->STAGE,pinfo->gameV,pinfo->BGM,
		pinfo->sk ,pinfo->sk01 ,pinfo->sk02 ,pinfo->sk03 ,pinfo->sk04 ,
		pinfo->MAP.items
	};
	fwrite(num, sizeof(int), 10, savefile);
	fwrite(&(pinfo->DOT), sizeof(dot), 1, savefile);
	fwrite(&(pinfo->BOARD), sizeof(board), 1, savefile);
	//Map
	Node  *ablock, *tempNode;
	ablock = pinfo->MAP.front;
	do {
		fwrite(&(ablock->item), sizeof(block), 1, savefile);
		tempNode = ablock;
		ablock = ablock->next;
	} while (tempNode->next != NULL);

	fclose(savefile);
}


#endif
