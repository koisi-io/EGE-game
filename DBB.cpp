#include "graphics.h"
#include <stdlib.h>
#include "DBB.h"

//*****************************************************

void moveDot(dot *adot) {
	adot->x += adot->Vx;
	adot->y += adot->Vy;
}

void drawDot(const dot *adot) {
	setcolor(WHITE);
	circle(adot->x, adot->y, adot->R);
	circle(adot->x, adot->y, adot->r);
	if (adot->c)
		setfillcolor(LIGHTRED);
	else
		setfillcolor(LIGHTBLUE);
	floodfill(adot->x, adot->y, WHITE);
}

//*****************************************************

void drawBoard(const board *aboard) {
	setcolor(WHITE);
	rectangle(aboard->x, aboard->y, aboard->x + aboard->w, aboard->y + aboard->h);
	setfillcolor(LIGHTGREEN);
	floodfill(aboard->x + 1, aboard->y + 1, WHITE);
	floodfill(aboard->x + aboard->w - 2, aboard->y + aboard->h - 2, WHITE);
}

void moveBoard(board *aboard) {
	aboard->x += aboard->V;
}

void boardV(board *aboard) {
	int mx, my, dx, mid;
	mid = aboard->x + ((aboard->w) / 2);
	int baseV = board_V;
	mousepos(&mx, &my);

	if (mx > frame_x)
		mx = frame_x;
	if (mx < frameX)
		mx = frameX;
	dx = mx - mid;

	if (dx > 120)
		aboard->V = 3 * baseV;
	else if (dx > 70)
		aboard->V = 2 * baseV;
	else if (dx > 0)
		aboard->V = 1 * baseV;
	else if (dx < -120)
		aboard->V = -3 * baseV;
	else if (dx < -70)
		aboard->V = -2 * baseV;
	else if (dx < 0)
		aboard->V = -1 * baseV;
	if (dx<3 && dx>-3)
		aboard->V = 0;

}

//*****************************************************

void drawBlock(const block *ablock) {
	if (ablock->exi) {
		if (ablock->vis) {
			setcolor(LIGHTCYAN);
			rectangle(ablock->x + 1, ablock->y + 1, ablock->x + ablock->w - 1, ablock->y + ablock->h - 1);
			switch (ablock->type)
			{
			case 1:
				setfillcolor(WHITE);
				break;
			case 2:
				setfillcolor(LIGHTGREEN);
				break;
			case 3:
				setfillcolor(LIGHTBLUE);
				break;
			case 4:
				setfillcolor(LIGHTRED);
				break;
			case 5:
				setfillcolor(DARKGRAY);
				break;
			default:
				setfillcolor(WHITE);
				break;
			}
			floodfill(ablock->x + 4, ablock->y + 4, LIGHTCYAN);
		}
	}
}

//*****************************************************

void setBoun1(dot *adot) {
	if ((adot->x + adot->r) >= frame_x || adot->x - adot->r <= frameX)
		adot->Vx = -adot->Vx;
	if (adot->y - adot->r <= frameY)
		adot->Vy = -adot->Vy;
}

void setBoun2(dot *adot, const board *aboard) {
	if ((adot->y + adot->R) == aboard->y && (adot->x) <= (aboard->x + aboard->w) && (adot->x) >= aboard->x)
		adot->Vy = -adot->Vy;
	if ((adot->x + adot->R) == aboard->x && (adot->y) <= (aboard->y + aboard->h) && (adot->y) >= aboard->y)
		adot->Vx = -adot->Vx;
	if ((adot->x - adot->R) == (aboard->x + aboard->w) && (adot->y) <= (aboard->y + aboard->h) && (adot->y) >= aboard->y)
		adot->Vx = -adot->Vx;
}

void setBoun3(dot *adot, block *ablock) {
	if (ablock->exi) {


		if ((adot->y + adot->R) == ablock->y || (adot->y - adot->R) == ablock->y + ablock->h)
			if ((adot->x) <= (ablock->x + ablock->w) && (adot->x) >= ablock->x) {
				adot->Vy = -adot->Vy;
				ablock->exi = 0;
				ablock->vis = 0;
			}


		if ((adot->x + adot->R) == ablock->x || (adot->x - adot->R) == ablock->x + ablock->w)
			if ((adot->y) <= (ablock->y + ablock->h) && (adot->y) >= ablock->y) {
				adot->Vx = -adot->Vx;
				ablock->exi = 0;
				ablock->vis = 0;
			}

	}
}

int setBoun4(dot *adot, block *ablock) {
	if (ablock->exi) {


		if (((adot->y + adot->r) >= ablock->y && adot->y <= ablock->y)
			||
			((adot->y - adot->r) <= ablock->y + ablock->h && adot->y >= ablock->y + ablock->h))
			if ((adot->x) <= (ablock->x + ablock->w) && (adot->x) >= ablock->x) {
				adot->Vy = -adot->Vy;
				ablock->exi--;
				ablock->type--;
				return 1;
			}


		if (((adot->x + adot->r) >= ablock->x && adot->x <= ablock->x)
			||
			((adot->x - adot->r) <= ablock->x + ablock->w && adot->x >= ablock->x + ablock->w))
			if ((adot->y) <= (ablock->y + ablock->h) && (adot->y) >= ablock->y) {
				adot->Vx = -adot->Vx;
				ablock->exi--;
				ablock->type--;
				return 1;
			}

		int dd1, dd2, dd3, dd4, rr, dr1, dr2, dr3, dr4;
		rr = (adot->r) * (adot->r);
		dr1 = (adot->x - ablock->x);
		dr2 = (adot->x - ablock->x - ablock->w);
		dr3 = (adot->y - ablock->y);
		dr4 = (adot->y - ablock->y - ablock->h);
		dd1 = dr1 * dr1 + dr3 * dr3;
		dd2 = dr1 * dr1 + dr4 * dr4;
		dd3 = dr2 * dr2 + dr3 * dr3;
		dd4 = dr2 * dr2 + dr4 * dr4;

		if (dd1 < rr || dd2 < rr || dd3 < rr || dd4 < rr) {
			double dx;
			double dotx = (float)adot->x;
			dx = 0.70710678 * dotx;
			if (adot->x < ablock->x + dx && adot->x > ablock->x - dx) {
				adot->Vx = -adot->Vx;
				ablock->exi--;
				ablock->type--;
				return 1;
			}
			else {
				adot->Vy = -adot->Vy;
				ablock->exi--;
				ablock->type--;
				return 1;
			}
		}

		return 0;

	}
	return 0;
}

void setBoun5(dot *adot, const board *aboard) {

	if ((adot->y + adot->r) >= aboard->y && (adot->x) <= (aboard->x + aboard->w) && (adot->x) >= aboard->x)
		adot->Vy = -adot->Vy;
	if ((adot->x + adot->r) >= aboard->x && (adot->y) <= (aboard->y + aboard->h) && (adot->y) >= aboard->y)
		adot->Vx = -adot->Vx;
	if ((adot->x - adot->r) <= (aboard->x + aboard->w) && (adot->y) <= (aboard->y + aboard->h) && (adot->y) >= aboard->y)
		adot->Vx = -adot->Vx;

	int dd1, dd2, rr, dr1, dr2, dr3;
	rr = (adot->r) * (adot->r);
	dr1 = (adot->x - aboard->x);
	dr2 = (adot->x - aboard->x - aboard->w);
	dr3 = (adot->y - aboard->y);
	dd1 = dr1 * dr1 + dr3 * dr3;
	dd2 = dr2 * dr2 + dr3 * dr3;

	if (dd1 < rr || dd2 < rr) {
		adot->Vy = -adot->Vy;
	}



}

int SK4setBlock(dot *adot, block *ablock) {
	if (ablock->exi) {

		int dd1, dd2, dd3, dd4, rr, dr1, dr2, dr3, dr4;
		rr = (adot->R) * (adot->R);
		dr1 = (adot->x - ablock->x);
		dr2 = (adot->x - ablock->x - ablock->w);
		dr3 = (adot->y - ablock->y);
		dr4 = (adot->y - ablock->y - ablock->h);
		dd1 = dr1 * dr1 + dr3 * dr3;
		dd2 = dr1 * dr1 + dr4 * dr4;
		dd3 = dr2 * dr2 + dr3 * dr3;
		dd4 = dr2 * dr2 + dr4 * dr4;

		if (dd1 < rr || dd2 < rr || dd3 < rr || dd4 < rr) {
			double dx;
			double dotx = (float)adot->x;
			dx = 0.70710678 * dotx;
			if (adot->x < ablock->x + dx && adot->x > ablock->x - dx) {
				ablock->exi--;
				ablock->type--;
				return 3;
			}
			else {
				ablock->exi--;
				ablock->type--;
				return 3;
			}
		}

		return 0;
	}
	return 0;
}
int SK3setBlock(dot *adot, block *ablock) {
	if (ablock->exi) {


		if (((adot->y + adot->r) >= ablock->y && adot->y <= ablock->y)
			||
			((adot->y - adot->r) <= ablock->y + ablock->h && adot->y >= ablock->y + ablock->h))
			if ((adot->x) <= (ablock->x + ablock->w) && (adot->x) >= ablock->x) {

				ablock->exi--;
				ablock->type--;
				return 2;
			}


		if (((adot->x + adot->r) >= ablock->x && adot->x <= ablock->x)
			||
			((adot->x - adot->r) <= ablock->x + ablock->w && adot->x >= ablock->x + ablock->w))
			if ((adot->y) <= (ablock->y + ablock->h) && (adot->y) >= ablock->y) {

				ablock->exi--;
				ablock->type--;
				return 2;
			}

		int dd1, dd2, dd3, dd4, rr, dr1, dr2, dr3, dr4;
		rr = (adot->r) * (adot->r);
		dr1 = (adot->x - ablock->x);
		dr2 = (adot->x - ablock->x - ablock->w);
		dr3 = (adot->y - ablock->y);
		dr4 = (adot->y - ablock->y - ablock->h);
		dd1 = dr1 * dr1 + dr3 * dr3;
		dd2 = dr1 * dr1 + dr4 * dr4;
		dd3 = dr2 * dr2 + dr3 * dr3;
		dd4 = dr2 * dr2 + dr4 * dr4;

		if (dd1 < rr || dd2 < rr || dd3 < rr || dd4 < rr) {
			double dx;
			double dotx = (float)adot->x;
			dx = 0.70710678 * dotx;
			if (adot->x < ablock->x + dx && adot->x > ablock->x - dx) {

				ablock->exi--;
				ablock->type--;
				return 2;
			}
			else {

				ablock->exi--;
				ablock->type--;
				return 2;
			}
		}

		return 0;

	}
	return 0;
}
void SK3setBoun(dot *adot) {
	if (adot->y - adot->r >= frame_y)
		adot->Vy = -adot->Vy;
}
void MDSK01dot(dot *adot) {

	setcolor(WHITE);
	circle(adot->x, adot->y, adot->R);
	circle(adot->x, adot->y, adot->r);

	setfillcolor(LIGHTCYAN);
	floodfill(adot->x, adot->y, WHITE);

	adot->x += adot->Vx;
	adot->y += adot->Vy;

}


//*****************************************************
//			·ÏÆú²Ö¿â
/*

int setBoun4(dot *adot, block *ablock) {
if (ablock->exi) {



if ((adot->y + adot->R) == ablock->y || (adot->y - adot->R) == ablock->y + ablock->h)
if ((adot->x) <= (ablock->x + ablock->w) && (adot->x) >= ablock->x) {
adot->Vy = -adot->Vy;
ablock->exi = 0;
ablock->vis = 0;
}


if ((adot->x + adot->R) == ablock->x || (adot->x - adot->R) == ablock->x + ablock->w)
if ((adot->y) <= (ablock->y + ablock->h) && (adot->y) >= ablock->y) {
adot->Vx = -adot->Vx;
ablock->exi = 0;
ablock->vis = 0;
}

int dd1, dd2, dd3, dd4, rr, dr1, dr2, dr3, dr4;
rr = (adot->R) * (adot->R);
dr1 = (adot->x - ablock->x);
dr2 = (adot->x - ablock->x - ablock->w);
dr3 = (adot->y - ablock->y);
dr4 = (adot->y - ablock->y - ablock->h);
dd1 = dr1 * dr1 + dr3 * dr3;
dd2 = dr1 * dr1 + dr4 * dr4;
dd3 = dr2 * dr2 + dr3 * dr3;
dd4 = dr2 * dr2 + dr4 * dr4;

if (dd1 < rr || dd2 < rr || dd3 < rr || dd4 < rr) {
double dx;
double dotx = (float)adot->x;
dx = 0.70710678 * dotx;
if (adot->x < ablock->x + dx && adot->x > ablock->x - dx) {
adot->Vy = -adot->Vy;
ablock->exi = 0;
ablock->vis = 0;
}
else {
adot->Vx = -adot->Vx;
ablock->exi = 0;
ablock->vis = 0;
}
}




}
}


*/