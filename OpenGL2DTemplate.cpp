
#include <stdlib.h> 
#include <cmath>
#include <string.h>
#include <glut.h>
#include <math.h>
#include <ctime>
#include <cstdio>
#include <windows.h>
#include <mmsystem.h>
using namespace std;

double move = 0;
//double moveCloud = 0;
char* lastGame = "";
int state = 1;
int stateFire = false;
int clicked = 0;
int clicked2 = 0;
int shift = 650;
int shiftFirst = 100;
float t = 0;
int p0[2];
int p1[2];
int p2[2];
int p3[2];
int incUp = 0;
int incForward = 0;
int level[] = { -200,-100,0,100,150};
int disapper = 1;
float jumpLeft = 0;
int jL = 0;
float jumpRight = 0;
int jR = 0;
bool fristPlayer = true;
double drawingLim = 7;
clock_t timeMain = clock();
double fanRot = 0; 
double fanWeaponsRot = 0; 
double rainDown = 0;
int firstPlayerLife = 3;
int secondPlayerLife = 3;
double firstTimer = 0;
double secondTimer = 0;
bool mouseDown = false;
bool switchIT = false;
int handRaisedFirst = 0;
int handRaisedSecond = 0;
double goCall = 0;
int incCall = 1;


void rest() {
	stateFire = false;
	fristPlayer = !fristPlayer;
	handRaisedFirst = 0;
	handRaisedSecond = 0;
	if (fristPlayer) {
		t = 1;
		disapper = 1;
		
	}
	else {
		t = 0;
		disapper = 1;
		
	}
}

void print(int x, int y, char* string)
{
	int len, i;

	glRasterPos2f(x, y);

	len = (int)strlen(string);

	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void weapon(int res[2]) {
	glPushMatrix();
	glTranslated(res[0], res[1], 0);
	glRotated(fanWeaponsRot, 0, 0, 1);
	
	if (fristPlayer) {
		glBegin(GL_QUADS);
		glVertex3f(-5, 0 - 5, 0.0f);
		glVertex3f(-5, 0 + 10 - 5, 0.0f);
		glVertex3f(5, 0 + 10 - 5, 0.0f);
		glVertex3f(5, 0 - 5, 0.0f);

		glVertex3f(0 + 3 - 5, 0 + 10 - 5, 0.0f);
		glVertex3f(0 + 3 - 5, 0 + 13 - 5, 0.0f);
		glVertex3f(0 + 7 - 5, 0 + 13 - 5, 0.0f);
		glVertex3f(0 + 7 - 5, 0 + 10 - 5, 0.0f);

		glVertex3f(0 + 3 - 5, 1 - 3 - 5, 0.0f);
		glVertex3f(0 + 3 - 5, 1 - 5, 0.0f);
		glVertex3f(0 + 7 - 5, 1 - 5, 0.0f);
		glVertex3f(0 + 7 - 5, 1 - 3 - 5, 0.0f);

		glVertex3f(13 - 5, 3 - 5, 0.0f);
		glVertex3f(13 - 5, 7 - 5, 0.0f);
		glVertex3f(10 - 5, 7 - 5, 0.0f);
		glVertex3f(10 - 5, 3 - 5, 0.0f);

		glVertex3f(0 - 5, 3 - 5, 0.0f);
		glVertex3f(0 - 5, 7 - 5, 0.0f);
		glVertex3f(-3 - 5, 7 - 5, 0.0f);
		glVertex3f(-3 - 5, 3 - 5, 0.0f);

		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(-8, 13 - 5, 0.0f);
		glVertex3f(8, 13 - 5, 0.0f);
		glVertex3f(0, 23, 0.0f);

		glVertex3f(-8, -8, 0.0f);
		glVertex3f(8, -8, 0.0f);
		glVertex3f(0, -23, 0.0f);

		glVertex3f(8, 8, 0.0f);
		glVertex3f(8, -8, 0.0f);
		glVertex3f(23, 0, 0.0f);

		glVertex3f(-8, 8, 0.0f);
		glVertex3f(-8, -8, 0.0f);
		glVertex3f(-23, 0, 0.0f);

		glEnd();
	}
	else {
		glBegin(GL_QUADS);
		glColor3f(160.0/255.0, 82.0 / 255.0, 45.0 / 255.0);
		glVertex3f(-10, 3 , 0.0f);
		glVertex3f(-10, 0 , 0.0f);
		glVertex3f(10, 0 , 0.0f);
		glVertex3f(10, 3 , 0.0f);

		glVertex3f(-5, -12, 0.0f);
		glVertex3f(-5, 0, 0.0f);
		glVertex3f(5, 0, 0.0f);
		glVertex3f(5, -25, 0.0f);

		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(128.0/255.0, 128.0 / 255.0, 128.0 / 255.0);
		glVertex3f(-8, 3, 0.0f);
		glVertex3f(0, 3, 0.0f);
		glVertex3f(0, 30, 0.0f);

		glColor3f(192.0 / 255.0, 192.0 / 255.0, 192.0 / 255.0);
		glVertex3f(8, 3, 0.0f);
		glVertex3f(0, 3, 0.0f);
		glVertex3f(0, 30, 0.0f);

		glEnd();

	}
	glPopMatrix();

}

void bezier(float t, int* p0, int* p1, int* p2, int* p3)
{
	int res[2];
	res[0] = pow((1 - t), 3) * p0[0] + 3 * t * pow((1 - t), 2) * p1[0] + 3 * pow(t, 2) * (1 - t) * p2[0] + pow(t, 3) * p3[0];
	res[1] = pow((1 - t), 3) * p0[1] + 3 * t * pow((1 - t), 2) * p1[1] + 3 * pow(t, 2) * (1 - t) * p2[1] + pow(t, 3) * p3[1];

	weapon(res);

	//if hits shield
	if ((res[0] >= -130.0f + move) && (res[0] <= 290.0f + move) && (res[1] >= 380.0f) && (res[1] <= 450.0f)) {
		
		rest();
	}
	if ((res[0] + 10 >= -130.0f + move) && (res[0] + 10 <= 290.0f + move) && (res[1] + 10 >= 380.0f) && (res[1] + 10 <= 450.0f)) {
	
		rest();
	}

	//if hits border
	if ((res[0] >= 500) && (res[0] <= 550) && (res[1] >= 0) && (res[1] <= 350)) {
		
		rest();
	}
	if ((res[0] + 10 >= 500) && (res[0] + 10 <= 550) && (res[1] + 10 >= 0) && (res[1] + 10 <= 350)) {
		
		rest();
	}

	//if hits oponent
	if (fristPlayer) {
		if ((res[0] >= 740) && (res[0] <= 810) && (res[1] >= 50) && (res[1] <= 200)) {
			jR = 50;
			if (secondPlayerLife == 1) {
				lastGame = "LAST GAME: BATMAN WINS";
				firstPlayerLife = 3;
				secondPlayerLife = 3;
			}
			else
				secondPlayerLife--;
		
			rest();
		}
		if ((res[0] + 10 >= 740) && (res[0] + 10 <= 810) && (res[1] + 10 >= 50) && (res[1] + 10 <= 200)) {
			jR = 50;
			if (secondPlayerLife == 1) {
				lastGame = "LAST GAME: BATMAN WINS";
				firstPlayerLife = 3;
				secondPlayerLife = 3;
			}
			else
				secondPlayerLife--;
			
			rest();
		}
	}
	if (!fristPlayer) {
		if ((res[0] >= 190) && (res[0] <= 260) && (res[1] >= 50) && (res[1] <= 200)) {
			jL = 50;
			if (firstPlayerLife == 1) {
				lastGame = "LAST GAME: JOKER WINS";
				firstPlayerLife = 3;
				secondPlayerLife = 3;
			}
			else
				firstPlayerLife--;
		
			rest();
		}
		if ((res[0] + 10 >= 190) && (res[0] + 10 <= 260) && (res[1] + 10 >= 50) && (res[1] + 10 <= 200)) {
			jL = 50;
			if (firstPlayerLife == 1) {
				lastGame = "LAST GAME: JOKER WINS";
				firstPlayerLife = 3;
				secondPlayerLife = 3;
			}
			else
				firstPlayerLife--;
			
			rest();
		}
	}
	
	if (res[1] < 100) {
		
		rest();
	}


	
}

void batmanCall2() {
	glColor3f(220.0 / 255.0, 220.0 / 255.0, 220.0 / 255.0);
	glBegin(GL_POLYGON);
	glVertex2f(310 - 2 * goCall, 550);
	glVertex2f(250 - 2 * goCall, 550);
	glVertex2f(270, 300);
	glVertex2f(291, 300);
	glEnd();

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(280, 550, 0);
	glScaled(2, 2, 1);

	for (double i = 0; i <= 3.14; i += 0.02) {
		double xCor = 15 * cos(i);
		double yCor = 15 * sin(i);

		glBegin(GL_LINES);
		glVertex2f(xCor - goCall, yCor);
		glVertex2f(xCor - goCall, -yCor);
		glEnd();
	}

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);

	for (double xcord = 7; xcord >= 4; xcord -= 0.01)
	{

		double ycordPos = 2 * sqrt((double)(-1 * (abs(abs(xcord) - 1)) * abs(3 - abs(xcord)) / ((abs(xcord) - 1) * (3 - abs(xcord))))) *
			(1 + abs(abs(xcord) - 3) / (abs(xcord) - 3)) * sqrt((double)(1 - pow((xcord / 7), 2))) +
			(5 + 0.97 * (abs(xcord - 0.5) + abs(xcord + 0.5)) - 3 * (abs(xcord - 0.75) + abs(xcord + 0.75))) *
			(1 + abs(1 - abs(xcord)) / (1 - abs(xcord)));
		glVertex3d(xcord - goCall, ycordPos, 0);

		double ycordNeg = -3 * sqrt((double)(1 - pow((xcord / 7), 2))) * sqrt((double)(abs(abs(xcord) - 4) / (abs(xcord) - 4)));
		glVertex3d(xcord - goCall, ycordNeg, 0);
		glVertex3d(-xcord - goCall, ycordPos, 0);
		glVertex3d(-xcord - goCall, ycordNeg, 0);



	}

	for (double xcord = 3.99; xcord >= 0; xcord -= 0.01)
	{

		double ycordPos;
		if (xcord >= 3 || xcord <= 1)
		{
			ycordPos = 2 * sqrt((double)(-1 * (abs(abs(xcord) - 1)) * abs(3 - abs(xcord)) / ((abs(xcord) - 1) * (3 - abs(xcord))))) *
				(1 + abs(abs(xcord) - 3) / (abs(xcord) - 3)) * sqrt((double)(1 - pow((xcord / 7), 2))) +
				(5 + 0.97 * (abs(xcord - 0.5) + abs(xcord + 0.5)) - 3 * (abs(xcord - 0.75) + abs(xcord + 0.75))) *
				(1 + abs(1 - abs(xcord)) / (1 - abs(xcord)));
		}
		else
		{
			ycordPos = 2.71052 + (1.5 - 0.5 * abs(xcord)) - 1.35526 * sqrt((double)(4 - pow(abs(xcord) - 1, 2))) *
				sqrt((double)(abs(abs(xcord) - 1) / (abs(xcord) - 1))) + 0.9;
		}
		glVertex3d(xcord - goCall, ycordPos, 0);

		double ycordNeg = abs(xcord / 2) - 0.0913722 * pow(xcord, 2) - 3 + sqrt((double)(1 - pow((abs(abs(xcord) - 2) - 1), 2)));
		glVertex3d(xcord - goCall, ycordNeg, 0);
		glVertex3d(-xcord - goCall, ycordPos, 0);
		glVertex3d(-xcord - goCall, ycordNeg, 0);

	}
	glEnd();
	glPopMatrix();

}

void batmanCall(){
	glColor3f(220.0/255.0, 220.0 / 255.0, 220.0 / 255.0);
	glBegin(GL_POLYGON);
	glVertex2f(830+2*goCall, 500);
	glVertex2f(770 + 2*goCall, 500);
	glVertex2f(790, 400);
	glVertex2f(811, 400);
	glEnd();

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(800, 500 , 0);
	glScaled(2, 2, 1);

	for (double i = 0; i <= 3.14; i += 0.02) {
		double xCor = 15 * cos(i);
		double yCor = 15 * sin(i);

		glBegin(GL_LINES);
		glVertex2f(xCor + goCall,  yCor);
		glVertex2f(xCor + goCall,  -yCor);
		glEnd();
	}

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);

	for (double xcord = 7; xcord >= 4; xcord -= 0.01)
	{

		double ycordPos = 2 * sqrt((double)(-1 * (abs(abs(xcord) - 1)) * abs(3 - abs(xcord)) / ((abs(xcord) - 1) * (3 - abs(xcord))))) *
			(1 + abs(abs(xcord) - 3) / (abs(xcord) - 3)) * sqrt((double)(1 - pow((xcord / 7), 2))) +
			(5 + 0.97 * (abs(xcord - 0.5) + abs(xcord + 0.5)) - 3 * (abs(xcord - 0.75) + abs(xcord + 0.75))) *
			(1 + abs(1 - abs(xcord)) / (1 - abs(xcord)));
		glVertex3d(xcord + goCall, ycordPos, 0);

		double ycordNeg = -3 * sqrt((double)(1 - pow((xcord / 7), 2))) * sqrt((double)(abs(abs(xcord) - 4) / (abs(xcord) - 4)));
		glVertex3d(xcord + goCall, ycordNeg, 0);
		glVertex3d(-xcord + goCall, ycordPos, 0);
		glVertex3d(-xcord + goCall, ycordNeg, 0);



	}

	for (double xcord = 3.99; xcord >= 0; xcord -= 0.01)
	{

		double ycordPos;
		if (xcord >= 3 || xcord <= 1)
		{
			ycordPos = 2 * sqrt((double)(-1 * (abs(abs(xcord) - 1)) * abs(3 - abs(xcord)) / ((abs(xcord) - 1) * (3 - abs(xcord))))) *
				(1 + abs(abs(xcord) - 3) / (abs(xcord) - 3)) * sqrt((double)(1 - pow((xcord / 7), 2))) +
				(5 + 0.97 * (abs(xcord - 0.5) + abs(xcord + 0.5)) - 3 * (abs(xcord - 0.75) + abs(xcord + 0.75))) *
				(1 + abs(1 - abs(xcord)) / (1 - abs(xcord)));
		}
		else
		{
			ycordPos = 2.71052 + (1.5 - 0.5 * abs(xcord)) - 1.35526 * sqrt((double)(4 - pow(abs(xcord) - 1, 2))) *
				sqrt((double)(abs(abs(xcord) - 1) / (abs(xcord) - 1))) + 0.9;
		}
		glVertex3d(xcord + goCall, ycordPos, 0);

		double ycordNeg = abs(xcord / 2) - 0.0913722 * pow(xcord, 2) - 3 + sqrt((double)(1 - pow((abs(abs(xcord) - 2) - 1), 2)));
		glVertex3d(xcord + goCall, ycordNeg, 0);
		glVertex3d(-xcord + goCall, ycordPos, 0);
		glVertex3d(-xcord + goCall, ycordNeg, 0);

	}
	glEnd();
	glPopMatrix();

}

void batmanSign() {
	
	glColor3f(25.0 / 255.0, 25.0 / 255.0, 112.0 / 255.0);
	glPushMatrix();
	glTranslated(225, 115.5 + jumpLeft, 0);
	glScaled(3, 3, 1);


	glBegin(GL_LINES);

	for (double xcord = 7; xcord >= 4; xcord -= 0.01)
	{
		
			double ycordPos = 2 * sqrt((double)(-1 * (abs(abs(xcord) - 1)) * abs(3 - abs(xcord)) / ((abs(xcord) - 1) * (3 - abs(xcord))))) *
				(1 + abs(abs(xcord) - 3) / (abs(xcord) - 3)) * sqrt((double)(1 - pow((xcord / 7), 2))) +
				(5 + 0.97 * (abs(xcord - 0.5) + abs(xcord + 0.5)) - 3 * (abs(xcord - 0.75) + abs(xcord + 0.75))) *
				(1 + abs(1 - abs(xcord)) / (1 - abs(xcord)));
			glVertex3d(xcord, ycordPos, 0);

			double ycordNeg = -3 * sqrt((double)(1 - pow((xcord / 7), 2))) * sqrt((double)(abs(abs(xcord) - 4) / (abs(xcord) - 4)));
			glVertex3d(xcord, ycordNeg, 0);
			glVertex3d(-xcord, ycordPos, 0);
			glVertex3d(-xcord, ycordNeg, 0);
		


	}

	for (double xcord = 3.99; xcord >= 0; xcord -= 0.01)
	{
		
			double ycordPos;
			if (xcord >= 3 || xcord <= 1)
			{
				ycordPos = 2 * sqrt((double)(-1 * (abs(abs(xcord) - 1)) * abs(3 - abs(xcord)) / ((abs(xcord) - 1) * (3 - abs(xcord))))) *
					(1 + abs(abs(xcord) - 3) / (abs(xcord) - 3)) * sqrt((double)(1 - pow((xcord / 7), 2))) +
					(5 + 0.97 * (abs(xcord - 0.5) + abs(xcord + 0.5)) - 3 * (abs(xcord - 0.75) + abs(xcord + 0.75))) *
					(1 + abs(1 - abs(xcord)) / (1 - abs(xcord)));
			}
			else
			{
				ycordPos = 2.71052 + (1.5 - 0.5 * abs(xcord)) - 1.35526 * sqrt((double)(4 - pow(abs(xcord) - 1, 2))) *
					sqrt((double)(abs(abs(xcord) - 1) / (abs(xcord) - 1))) + 0.9;
			}
			glVertex3d(xcord, ycordPos, 0);

			double ycordNeg = abs(xcord / 2) - 0.0913722 * pow(xcord, 2) - 3 + sqrt((double)(1 - pow((abs(abs(xcord) - 2) - 1), 2)));
			glVertex3d(xcord, ycordNeg, 0);
			glVertex3d(-xcord, ycordPos, 0);
			glVertex3d(-xcord, ycordNeg, 0);
		
	}
	glEnd();
	glPopMatrix();

	

}
void upPower(int value) {
	if (fristPlayer && firstTimer<180)
		firstTimer += 0.12;
	else if(!fristPlayer && secondTimer<180)
		secondTimer += 0.12;

	if(mouseDown)
	 glutTimerFunc(1, upPower, 0);

}
void mouseFunc(int button, int state, int x, int y)
{
	clock_t timeReq = timeMain;
	
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		timeMain = clock();
		mouseDown = true;
		glutTimerFunc(1, upPower, 0);

	}
	if (button == GLUT_LEFT_BUTTON && (state == GLUT_UP)) {
		if (fristPlayer)
			handRaisedFirst = 152;
		else {
			handRaisedSecond = 152;
		}
		stateFire = true;
		mouseDown = false;
		if (fristPlayer)
			firstTimer = 0;
		else
			secondTimer = 0;
		timeReq = clock() - timeReq;
		float timeLevel = (float)timeReq/CLOCKS_PER_SEC;
		printf("%.3f",timeLevel);
		printf(fristPlayer ? "true" : "false");
		if (timeLevel <= 0.25) {
			incForward = level[0];
			incUp = level[0];
		}
		else if(timeLevel > 0.25 && timeLevel <= 1) {
		incForward = level[1];
		incUp = level[1];
		}
		else if (timeLevel > 1 && timeLevel <= 1.5) {
			incForward = level[2];
			incUp = level[2];
		}
		else if (timeLevel > 1.5 && timeLevel <= 1.8) {
			incForward = level[3];
			incUp = level[3];
		}
		else if (timeLevel > 1.8) {
			incForward = level[4];
			incUp = level[4];
		}

		if (fristPlayer) {
			//right up
			p2[0] = 800+incForward;
			p2[1] = 500+incUp;

			//right down
			p3[0] = 800+incForward;
			p3[1] = 20;
			disapper = 0;
			t = 0;

		}
		else {

			//left down
			p0[0] = 200 - incForward;
			p0[1] = 20 + incUp;

			//left up
			p1[0] = 200 - incForward;
			p1[1] = 500;
			
			disapper = 0;
			t = 1;
			

		}
	}
}

void createLeftHero() {
	//left hero
	//head
	glBegin(GL_POLYGON);
	glColor3f(25.0 / 255.0, 25.0 / 255.0, 112.0 / 255.0);
	glVertex3f(150.0f + shiftFirst, 160.0f + jumpLeft, 0.0f);
	glVertex3f(150.0f + shiftFirst, 200.0f + jumpLeft, 0.0f);
	glVertex3f(100.0f + shiftFirst, 200.0f + jumpLeft, 0.0f);
	glVertex3f(100.0f + shiftFirst, 160.0f + jumpLeft, 0.0f);
	glEnd();

	//jaw
	glBegin(GL_POLYGON);
	glColor3f(232.0 / 255.0, 227.0 / 255.0, 130.0 / 255.0);
	glVertex3f(140.0f + shiftFirst, 165.0f + jumpLeft, 0.0f);
	glVertex3f(140.0f + shiftFirst, 175.0f + jumpLeft, 0.0f);
	glVertex3f(110.0f + shiftFirst, 175.0f + jumpLeft, 0.0f);
	glVertex3f(110.0f + shiftFirst, 165.0f + jumpLeft, 0.0f);
	glEnd();

	//mouth
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0 , 1.0);
	glVertex3f(131.0f + shiftFirst, 168.0f + jumpLeft, 0.0f);
	glVertex3f(131.0f + shiftFirst, 171.0f + jumpLeft, 0.0f);
	glVertex3f(115.0f + shiftFirst, 172.0f + jumpLeft, 0.0f);
	glVertex3f(115.0f + shiftFirst, 168.0f + jumpLeft, 0.0f);
	glEnd();

	//eyes
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(117.0f + shiftFirst, 188.0f + jumpLeft, 0.0f);
	glVertex3f(117.0f + shiftFirst, 185.0f + jumpLeft, 0.0f);
	glVertex3f(110.0f + shiftFirst, 185.0f + jumpLeft, 0.0f);
	glVertex3f(110.0f + shiftFirst, 190.0f + jumpLeft, 0.0f);
	glEnd();

	//eyes
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(133.0f + shiftFirst, 188.0f + jumpLeft, 0.0f);
	glVertex3f(133.0f + shiftFirst, 185.0f + jumpLeft, 0.0f);
	glVertex3f(140.0f + shiftFirst, 185.0f + jumpLeft, 0.0f);
	glVertex3f(140.0f + shiftFirst, 190.0f + jumpLeft, 0.0f);
	glEnd();

	//ears
	glBegin(GL_TRIANGLES);
	glColor3f(25.0 / 255.0, 25.0 / 255.0, 112.0 / 255.0);
	glVertex3f(100.0f + shiftFirst, 200.0f + jumpLeft, 0.0f);
	glVertex3f(110.0f + shiftFirst, 200.0f + jumpLeft, 0.0f);
	glVertex3f(105.0f + shiftFirst, 220.0f + jumpLeft, 0.0f);

	glVertex3f(150.0f + shiftFirst, 200.0f + jumpLeft, 0.0f);
	glVertex3f(140.0f + shiftFirst, 200.0f + jumpLeft, 0.0f);
	glVertex3f(145.0f + shiftFirst, 220.0f + jumpLeft, 0.0f);
	glEnd();

	//neck
	glBegin(GL_POLYGON);
	glColor3f(117.0 / 255.0, 114.0 / 255.0, 113.0 / 255.0);
	glVertex3f(105.0f + shiftFirst, 160.0f + jumpLeft, 0.0f);
	glVertex3f(145.0f + shiftFirst, 160.0f + jumpLeft, 0.0f);
	glVertex3f(145.0f + shiftFirst, 155.0f + jumpLeft, 0.0f);
	glVertex3f(105.0f + shiftFirst, 155.0f + jumpLeft, 0.0f);
	glEnd();

	//body 70 90 180 160
	glBegin(GL_POLYGON);
	glVertex3f(90.0f + shiftFirst, 155.0f + jumpLeft, 0.0f);
	glVertex3f(160.0f + shiftFirst, 155.0f + jumpLeft, 0.0f);
	glVertex3f(160.0f + shiftFirst, 50.0f + jumpLeft, 0.0f);
	glVertex3f(90.0f + shiftFirst, 50.0f + jumpLeft, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(237.0 / 255.0, 181.0 / 255.0, 14.0 / 255.0);
	glVertex3f(95.0f + shiftFirst, 132.0f + jumpLeft, 0.0f);
	glVertex3f(155.0f + shiftFirst, 132.0f + jumpLeft, 0.0f);
	glVertex3f(155.0f + shiftFirst, 105.0f + jumpLeft, 0.0f);
	glVertex3f(95.0f + shiftFirst, 105.0f + jumpLeft, 0.0f);
	glEnd();

	//belt
	glBegin(GL_QUADS);
	glColor3f(255.0/255.0, 215/255.0, 0);
	glVertex3f(90.0f + shiftFirst, 68.0f + jumpLeft, 0.0f);
	glVertex3f(105.0f + shiftFirst,68.0f + jumpLeft, 0.0f);
	glVertex3f(105.0f + shiftFirst, 88.0f + jumpLeft, 0.0f);
	glVertex3f(90.0f + shiftFirst, 88.0f + jumpLeft, 0.0f);

	glVertex3f(105.0f + shiftFirst, 71.0f + jumpLeft, 0.0f);
	glVertex3f(110.0f + shiftFirst, 71.0f + jumpLeft, 0.0f);
	glVertex3f(110.0f + shiftFirst, 85.0f + jumpLeft, 0.0f);
	glVertex3f(105.0f + shiftFirst, 85.0f + jumpLeft, 0.0f);

	glVertex3f(110.0f + shiftFirst, 68.0f + jumpLeft, 0.0f);
	glVertex3f(125.0f + shiftFirst, 68.0f + jumpLeft, 0.0f);
	glVertex3f(125.0f + shiftFirst, 88.0f + jumpLeft, 0.0f);
	glVertex3f(110.0f + shiftFirst, 88.0f + jumpLeft, 0.0f);

	glVertex3f(125.0f + shiftFirst, 71.0f + jumpLeft, 0.0f);
	glVertex3f(130.0f + shiftFirst, 71.0f + jumpLeft, 0.0f);
	glVertex3f(130.0f + shiftFirst, 85.0f + jumpLeft, 0.0f);
	glVertex3f(125.0f + shiftFirst, 85.0f + jumpLeft, 0.0f);

	glVertex3f(130.0f + shiftFirst, 68.0f + jumpLeft, 0.0f);
	glVertex3f(145.0f + shiftFirst, 68.0f + jumpLeft, 0.0f);
	glVertex3f(145.0f + shiftFirst, 88.0f + jumpLeft, 0.0f);
	glVertex3f(130.0f + shiftFirst, 88.0f + jumpLeft, 0.0f);


	glVertex3f(145.0f + shiftFirst, 71.0f + jumpLeft, 0.0f);
	glVertex3f(150.0f + shiftFirst, 71.0f + jumpLeft, 0.0f);
	glVertex3f(150.0f + shiftFirst, 85.0f + jumpLeft, 0.0f);
	glVertex3f(145.0f + shiftFirst, 85.0f + jumpLeft, 0.0f);

	glVertex3f(150.0f + shiftFirst, 68.0f + jumpLeft, 0.0f);
	glVertex3f(160.0f + shiftFirst, 68.0f + jumpLeft, 0.0f);
	glVertex3f(160.0f + shiftFirst, 88.0f + jumpLeft, 0.0f);
	glVertex3f(150.0f + shiftFirst, 88.0f + jumpLeft, 0.0f);

	glEnd();

	glBegin(GL_LINES);
	glColor3f(0,0,0);

	glVertex3f(105.0f + shiftFirst, 68.0f + jumpLeft, 0.0f);
	glVertex3f(105.0f + shiftFirst, 88.0f + jumpLeft, 0.0f);

	glVertex3f(125.0f + shiftFirst, 68.0f + jumpLeft, 0.0f);
	glVertex3f(125.0f + shiftFirst, 88.0f + jumpLeft, 0.0f);

	glVertex3f(145.0f + shiftFirst, 68.0f + jumpLeft, 0.0f);
	glVertex3f(145.0f + shiftFirst, 88.0f + jumpLeft, 0.0f);

	glVertex3f(160.0f + shiftFirst, 68.0f + jumpLeft, 0.0f);
	glVertex3f(160.0f + shiftFirst, 88.0f + jumpLeft, 0.0f);
	glEnd();

	//right leg
	glBegin(GL_POLYGON);
	glColor3f(117.0 / 255.0, 114.0 / 255.0, 113.0 / 255.0);
	glVertex3f(130.0f + shiftFirst, 50.0f + jumpLeft, 0.0f);
	glVertex3f(160.0f + shiftFirst, 50.0f + jumpLeft, 0.0f);
	glVertex3f(160.0f + shiftFirst, 10.0f + jumpLeft, 0.0f);
	glVertex3f(130.0f + shiftFirst, 10.0f + jumpLeft, 0.0f);
	glEnd();

	//left leg
	glBegin(GL_POLYGON);
	glVertex3f(120.0f + shiftFirst, 50.0f + jumpLeft, 0.0f);
	glVertex3f(90.0f + shiftFirst, 50.0f + jumpLeft, 0.0f);
	glVertex3f(90.0f + shiftFirst, 10.0f + jumpLeft, 0.0f);
	glVertex3f(120.0f + shiftFirst, 10.0f + jumpLeft, 0.0f);
	glEnd();

	//left arm
	glBegin(GL_POLYGON);
	glVertex3f(90.0f + shiftFirst, 145.0f + jumpLeft, 0.0f);
	glVertex3f(80.0f + shiftFirst, 145.0f + jumpLeft, 0.0f);
	glVertex3f(80.0f + shiftFirst, 70.0f + jumpLeft + handRaisedFirst, 0.0f);
	glVertex3f(90.0f + shiftFirst, 70.0f + jumpLeft + handRaisedFirst, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(95.0f + shiftFirst, 145.0f + jumpLeft, 0.0f);
	glVertex3f(77.0f + shiftFirst, 145.0f + jumpLeft, 0.0f);
	glVertex3f(77.0f + shiftFirst, 159.0f + jumpLeft, 0.0f);
	glVertex3f(95.0f + shiftFirst, 159.0f + jumpLeft, 0.0f);
	glEnd();


	//right arm
	glBegin(GL_POLYGON);
	glVertex3f(160.0f + shiftFirst, 145.0f + jumpLeft, 0.0f);
	glVertex3f(170.0f + shiftFirst, 145.0f + jumpLeft, 0.0f);
	glVertex3f(170.0f + shiftFirst, 70.0f + jumpLeft, 0.0f);
	glVertex3f(160.0f + shiftFirst, 70.0f + jumpLeft, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(155.0f + shiftFirst, 145.0f + jumpLeft, 0.0f);
	glVertex3f(173.0f + shiftFirst, 145.0f + jumpLeft, 0.0f);
	glVertex3f(173.0f + shiftFirst, 159.0f + jumpLeft, 0.0f);
	glVertex3f(155.0f + shiftFirst, 159.0f + jumpLeft, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(25.0 / 255.0, 25.0 / 255.0, 112.0 / 255.0);
	glVertex3f(80.0f + shiftFirst, 145.0f + jumpLeft, 0.0f);
	glVertex3f(80.0f + shiftFirst, 70.0f + jumpLeft, 0.0f);
	glVertex3f(65.0f + shiftFirst, 90.0f + jumpLeft, 0.0f);
	glVertex3f(170.0f + shiftFirst, 145.0f + jumpLeft, 0.0f);
	glVertex3f(170.0f + shiftFirst, 70.0f + jumpLeft, 0.0f);
	glVertex3f(185.0f + shiftFirst, 90.0f + jumpLeft, 0.0f);
	glEnd();

	//left arm line
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(90.0f + shiftFirst, 145.0f + jumpLeft, 0.0f);
	glVertex3f(90.0f + shiftFirst, 70.0f + jumpLeft, 0.0f);
	glEnd();

	//right arm line
	glBegin(GL_LINES);
	glVertex3f(160.0f + shiftFirst, 145.0f + jumpLeft, 0.0f);
	glVertex3f(160.0f + shiftFirst, 70.0f + jumpLeft, 0.0f);
	glEnd();

	//left leg lines
	glBegin(GL_LINES);
	glVertex3f(120.0f + shiftFirst, 40.0f + jumpLeft, 0.0f);
	glVertex3f(90.0f + shiftFirst, 40.0f + jumpLeft, 0.0f);
	glVertex3f(90.0f + shiftFirst, 30.0f + jumpLeft, 0.0f);
	glVertex3f(120.0f + shiftFirst, 30.0f + jumpLeft, 0.0f);
	glEnd();

	//right leg lines
	glBegin(GL_LINES);
	glVertex3f(130.0f + shiftFirst, 40.0f + jumpLeft, 0.0f);
	glVertex3f(160.0f + shiftFirst, 40.0f + jumpLeft, 0.0f);
	glVertex3f(160.0f + shiftFirst, 30.0f + jumpLeft, 0.0f);
	glVertex3f(130.0f + shiftFirst, 30.0f + jumpLeft, 0.0f);
	glEnd();

}

void createRightHero() {
	//right hero
	

	//hair
	glBegin(GL_POLYGON);
	glColor3f(0.0, 153.0 / 255.0, 0.0);
	glVertex3f(150.0f + shift, 160.0f + jumpRight, 0.0f);
	glVertex3f(150.0f + shift, 200.0f + jumpRight, 0.0f);
	glVertex3f(100.0f + shift, 200.0f + jumpRight, 0.0f);
	glVertex3f(100.0f + shift, 160.0f + jumpRight, 0.0f);
	glVertex3f(95.0f + shift, 170.0f + jumpRight, 0.0f);
	glVertex3f(95.0f + shift, 180.0f + jumpRight, 0.0f);
	glVertex3f(95.0f + shift, 190.0f + jumpRight, 0.0f);
	glVertex3f(95.0f + shift, 200.0f + jumpRight, 0.0f);
	glVertex3f(110.0f + shift, 220.0f + jumpRight, 0.0f);
	glVertex3f(125.0f + shift, 230.0f + jumpRight, 0.0f);
	glVertex3f(140.0f + shift, 220.0f + jumpRight, 0.0f);
	glVertex3f(155.0f + shift, 200.0f + jumpRight, 0.0f);
	glVertex3f(155.0f + shift, 190.0f + jumpRight, 0.0f);
	glVertex3f(155.0f + shift, 180.0f + jumpRight, 0.0f);
	glVertex3f(155.0f + shift, 170.0f + jumpRight, 0.0f);
	glEnd();

	//hair lines

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(110.0f + shift, 220.0f + jumpRight, 0.0f);
	glVertex3f(115.0f + shift, 160.0f + jumpRight, 0.0f);
	glVertex3f(140.0f + shift, 220.0f + jumpRight, 0.0f);
	glVertex3f(135.0f + shift, 160.0f + jumpRight, 0.0f);
	glVertex3f(125.0f + shift, 230.0f + jumpRight, 0.0f);
	glVertex3f(125.0f + shift, 160.0f + jumpRight, 0.0f);
	glEnd();
	

	//head
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(150.0f + shift, 160.0f + jumpRight, 0.0f);
	glVertex3f(150.0f + shift, 200.0f + jumpRight, 0.0f);
	glVertex3f(100.0f + shift, 200.0f + jumpRight, 0.0f);
	glVertex3f(100.0f + shift, 160.0f + jumpRight, 0.0f);
	glEnd();

	//eyes
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(114.0f + shift, 190.0f + jumpRight, 0.0f);
	glVertex3f(114.0f + shift, 185.0f + jumpRight, 0.0f);
	glVertex3f(111.0f + shift, 185.0f + jumpRight, 0.0f);
	glVertex3f(111.0f + shift, 190.0f + jumpRight, 0.0f);
	glEnd();

	//eyes brows
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(107.0f + shift, 192.0f + jumpRight, 0.0f);
	glVertex3f(115.0f + shift, 194.0f + jumpRight, 0.0f);
	glVertex3f(115.0f + shift, 194.0f + jumpRight, 0.0f);
	glVertex3f(117.0f + shift, 192.0f + jumpRight, 0.0f);
	glEnd();

	//eyes
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(136.0f + shift, 190.0f + jumpRight, 0.0f);
	glVertex3f(136.0f + shift, 185.0f + jumpRight, 0.0f);
	glVertex3f(139.0f + shift, 185.0f + jumpRight, 0.0f);
	glVertex3f(139.0f + shift, 190.0f + jumpRight, 0.0f);
	glEnd();

	//eyes brows
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(132.0f + shift, 192.0f + jumpRight, 0.0f);
	glVertex3f(140.0f + shift, 194.0f + jumpRight, 0.0f);
	glVertex3f(140.0f + shift, 194.0f + jumpRight, 0.0f);
	glVertex3f(142.0f + shift, 192.0f + jumpRight, 0.0f);
	glEnd();

	//mouth
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(132.0f + shift, 167.0f + jumpRight, 0.0f);
	glVertex3f(132.0f + shift, 175.0f + jumpRight, 0.0f);
	glVertex3f(114.0f + shift, 175.0f + jumpRight, 0.0f);
	glVertex3f(114.0f + shift, 167.0f + jumpRight, 0.0f);
	glEnd();

	

	//teeth
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(132.0f  + shift, 167.0f + jumpRight, 0.0f);
	glVertex3f(132.0f  + shift, 175.0f + jumpRight, 0.0f);
	glVertex3f(128.0f + shift, 167.0f + jumpRight, 0.0f);
	glVertex3f(128.0f  + shift, 175.0f + jumpRight, 0.0f);
	glVertex3f(124.0f + shift, 167.0f + jumpRight, 0.0f);
	glVertex3f(124.0f + shift, 175.0f + jumpRight, 0.0f);
	glVertex3f(120.0f + shift, 167.0f + jumpRight, 0.0f);
	glVertex3f(120.0f + shift, 175.0f + jumpRight, 0.0f);
	glVertex3f(116.0f + shift, 167.0f + jumpRight, 0.0f);
	glVertex3f(116.0f + shift, 175.0f + jumpRight, 0.0f);
	glEnd();

	//lips
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(132.0f + shift, 167.0f + jumpRight, 0.0f);
	glVertex3f(132.0f + shift, 175.0f + jumpRight, 0.0f);
	glVertex3f(114.0f + shift, 175.0f + jumpRight, 0.0f);
	glVertex3f(114.0f + shift, 167.0f + jumpRight, 0.0f);
	glVertex3f(114.0f + shift, 167.0f + jumpRight, 0.0f);
	glVertex3f(132.0f + shift, 167.0f + jumpRight, 0.0f);
	glVertex3f(114.0f + shift, 175.0f + jumpRight, 0.0f);
	glVertex3f(132.0f + shift, 175.0f + jumpRight, 0.0f);

	glVertex3f(132.0f + shift, 171.0f + jumpRight, 0.0f);
	glVertex3f(138.0f + shift, 176.0f + jumpRight, 0.0f);

	glVertex3f(114.0f + shift, 171.0f + jumpRight, 0.0f);
	glVertex3f(108.0f + shift, 176.0f + jumpRight, 0.0f);

	glEnd();


	


	//neck
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(105.0f + shift, 160.0f + jumpRight, 0.0f);
	glVertex3f(145.0f + shift, 160.0f + jumpRight, 0.0f);
	glVertex3f(145.0f + shift, 155.0f + jumpRight, 0.0f);
	glVertex3f(105.0f + shift, 155.0f + jumpRight, 0.0f);
	glEnd();

	//body 70 90 180 160
	glBegin(GL_POLYGON);
	glColor3f(204.0/255.0, 0.0/255.0, 204.0/255.0);
	glVertex3f(90.0f + shift, 155.0f + jumpRight, 0.0f);
	glVertex3f(160.0f + shift, 155.0f + jumpRight, 0.0f);
	glVertex3f(160.0f + shift, 50.0f + jumpRight, 0.0f);
	glVertex3f(90.0f + shift, 50.0f + jumpRight, 0.0f);
	glEnd();

	//chmiz
	glBegin(GL_TRIANGLES);
	glColor3f(0, 1, 0);
	glVertex3f(125.0f + shift, 155.0f + jumpRight, 0.0f);
	glVertex3f(125.0f + shift, 70.0f + jumpRight, 0.0f);
	glVertex3f(105.0f + shift, 140.0f + jumpRight, 0.0f);
	
	glVertex3f(125.0f + shift, 155.0f + jumpRight, 0.0f);
	glVertex3f(125.0f + shift, 70.0f + jumpRight, 0.0f);
	glVertex3f(145.0f + shift, 140.0f + jumpRight, 0.0f);

	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(125.0f + shift, 155.0f + jumpRight, 0.0f);
	glVertex3f(125.0f + shift, 50.0f + jumpRight, 0.0f);

	glEnd();

	int clips = 70;
	glPointSize(3);
	glBegin(GL_POINTS);
	glColor3f(1,0, 0);
	while (clips < 155) {
		glVertex3f(129.0f + shift, clips + jumpRight, 0.0f);
		clips += 20;
	}
	glEnd();



	//left arm
	glBegin(GL_POLYGON);
	glColor3f(204.0 / 255.0, 0.0 / 255.0, 204.0 / 255.0);
	glVertex3f(90.0f + shift, 145.0f + jumpRight, 0.0f);
	glVertex3f(80.0f + shift, 145.0f + jumpRight, 0.0f);
	glVertex3f(80.0f + shift, 70.0f + jumpRight, 0.0f);
	glVertex3f(90.0f + shift, 70.0f + jumpRight, 0.0f);
	glEnd();


	//right arm
	glBegin(GL_POLYGON);
	glVertex3f(160.0f + shift, 145.0f + jumpRight, 0.0f);
	glVertex3f(170.0f + shift, 145.0f + jumpRight, 0.0f);
	glVertex3f(170.0f + shift, 70.0f + jumpRight+ handRaisedSecond, 0.0f);
	glVertex3f(160.0f + shift, 70.0f + jumpRight+ handRaisedSecond, 0.0f);
	glEnd();

	//right leg
	glBegin(GL_POLYGON);
	glColor3f(0.0, 153.0 / 255.0, 0.0);
	glVertex3f(130.0f + shift, 50.0f + jumpRight, 0.0f);
	glVertex3f(160.0f + shift, 50.0f + jumpRight, 0.0f);
	glVertex3f(160.0f + shift, 10.0f + jumpRight, 0.0f);
	glVertex3f(130.0f + shift, 10.0f + jumpRight, 0.0f);
	glEnd();

	//left leg
	glBegin(GL_POLYGON);
	glVertex3f(120.0f + shift, 50.0f + jumpRight, 0.0f);
	glVertex3f(90.0f + shift, 50.0f + jumpRight, 0.0f);
	glVertex3f(90.0f + shift, 10.0f + jumpRight, 0.0f);
	glVertex3f(120.0f + shift, 10.0f + jumpRight, 0.0f);
	glEnd();


	//left arm line
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(90.0f + shift, 145.0f + jumpRight, 0.0f);
	glVertex3f(90.0f + shift, 70.0f + jumpRight, 0.0f);
	glEnd();

	//right arm line
	glBegin(GL_LINES);
	glVertex3f(160.0f + shift, 145.0f + jumpRight, 0.0f);
	glVertex3f(160.0f + shift, 70.0f + jumpRight, 0.0f);
	glEnd();

	//left leg lines
	glBegin(GL_LINES);
	glVertex3f(120.0f + shift, 40.0f + jumpRight, 0.0f);
	glVertex3f(90.0f + shift, 40.0f + jumpRight, 0.0f);
	glVertex3f(90.0f + shift, 30.0f + jumpRight, 0.0f);
	glVertex3f(120.0f + shift, 30.0f + jumpRight, 0.0f);
	glEnd();

	//right leg lines
	glBegin(GL_LINES);
	glVertex3f(130.0f + shift, 40.0f + jumpRight, 0.0f);
	glVertex3f(160.0f + shift, 40.0f + jumpRight, 0.0f);
	glVertex3f(160.0f + shift, 30.0f + jumpRight, 0.0f);
	glVertex3f(130.0f + shift, 30.0f + jumpRight, 0.0f);
	glEnd();

	
}

void fans(int p) {
	glPushMatrix();
	glColor3f(0, 0, 0);
	if(p==2)
	glTranslated(240.0f + move, 430, 0);
	else
	glTranslated(-85.0f + move, 430, 0);

	//tubes
		glPointSize(15);
	for (double i = 0; i <= 2 * 3.14; i += 0.1) {
		double xCor = 57 * cos(i);
		double yCor = 57 * sin(i);
		glBegin(GL_POINTS);
		glColor3f(0,0,0);
		glVertex2f(xCor, yCor);
		glEnd();
	}
	

	glScaled(5, 5, 1);
	glRotated(fanRot, 0, 0, 1);


	for (int wingers = 0; wingers < 10; wingers++)
	{
		glPushMatrix();

		glRotated(36 * wingers, 0, 0, 1);

		glBegin(GL_QUADS);

		glColor3f(192.0 / 255.0, 192.0 / 255.0, 192.0 / 255.0);
		glVertex3d(0, 0, 0);
		glVertex3d(1, 0, 0);
		glVertex3d(0, 10, 0);
		glVertex3d(1, 10, 0);


		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
	glEnd();


}

void createBorder() {
	glBegin(GL_POLYGON);
	glColor3f(181.0/255.0, 71.0 / 255.0, 71.0 / 255.0);
	glVertex3f(500.0f , 350.0f, 0.0f);
	glVertex3f(525.0f , 350.0f, 0.0f);
	glVertex3f(525.0f , 0.0f, 0.0f);
	glVertex3f(500.0f , 0.0f, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(525.0f, 350.0f, 0.0f);
	glVertex3f(550.0f, 350.0f, 0.0f);
	glVertex3f(550.0f, 0.0f, 0.0f);
	glVertex3f(525.0f, 0.0f, 0.0f);
	glEnd();

	int up = 30;
	int eflag = 0;
	while (true) {
		glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(500.0f, 0.0f+up, 0.0f);
		glVertex3f(550.0f, 0.0f+up, 0.0f);
		if (eflag == 0) {
		   glVertex3f(520.0f, 0.0f + up-30, 0.0f);
		   glVertex3f(520.0f, 0.0f + up, 0.0f);
		   eflag = 1;
		}
		else {
			glVertex3f(540.0f, 0.0f + up-30, 0.0f);
		    glVertex3f(540.0f, 0.0f + up, 0.0f);
			eflag = 0;

		}
		glEnd();
		up += 30;
		if (up >= 350)
			break;
	}

}

void createShield() {
	
	glBegin(GL_POLYGON);
	glColor3f(106.0 / 255.0, 216 / 255.0, 252 / 255.0);
	glVertex3f(10.0f + move, 450.0f, 0.0f);
	glVertex3f(150.0f + move, 450.0f, 0.0f);
	glVertex3f(130.0f + move, 500.0f, 0.0f);
	glVertex3f(30.0f + move, 500.0f, 0.0f);
	glEnd();

	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(70.0f + move, 450.0f, 0.0f);
	glVertex3f(90.0f + move, 450.0f, 0.0f);
	glVertex3f(120.0f + move, 500.0f, 0.0f);
	glVertex3f(100.0f + move, 500.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(50.0f + move, 450.0f, 0.0f);
	glVertex3f(60.0f + move, 450.0f, 0.0f);
	glVertex3f(90.0f + move, 500.0f, 0.0f);
	glVertex3f(80.0f + move, 500.0f, 0.0f);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(80.0f + move, 500.0f, 0.0f);
	glVertex3f(80.0f + move, 520.0f, 0.0f);

	glVertex3f(80.0f + move, 520.0f, 0.0f);
	glVertex3f(105.0f + move, 520.0f, 0.0f);
	glVertex3f(105.0f + move, 520.0f, 0.0f);
	glVertex3f(105.0f + move, 535.0f, 0.0f);

	glVertex3f(80.0f + move, 520.0f, 0.0f);
	glVertex3f(55.0f + move, 520.0f, 0.0f);
	glVertex3f(55.0f + move, 520.0f, 0.0f);
	glVertex3f(55.0f + move, 535.0f, 0.0f);
	glEnd();
	

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	
	glVertex3f(130.0f + move, 500.0f, 0.0f);
	glVertex3f(30.0f + move, 500.0f, 0.0f);
	
	glVertex3f(10.0f + move, 450.0f, 0.0f);	
	glVertex3f(30.0f + move, 500.0f, 0.0f);

	glVertex3f(30.0f + move, 450.0f, 0.0f);
	glVertex3f(30.0f + move, 500.0f, 0.0f);

	glVertex3f(130.0f + move, 450.0f, 0.0f);
	glVertex3f(130.0f + move, 500.0f, 0.0f);

	glVertex3f(150.0f + move, 450.0f, 0.0f);
	glVertex3f(130.0f + move, 500.0f, 0.0f);

	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(25.0 / 255.0, 25.0 / 255.0, 112.0 / 255.0);
	glVertex3f(10.0f + move, 450.0f, 0.0f);
	glVertex3f(150.0f + move, 450.0f, 0.0f);
	glVertex3f(150.0f + move, 400.0f, 0.0f);
	glVertex3f(10.0f + move, 400.0f, 0.0f);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3f(192.0/255.0, 192.0 / 255.0, 192.0 / 255.0);
	glVertex3f(50.0f + move, 450.0f, 0.0f);
	glVertex3f(110.0f + move, 450.0f, 0.0f);
	glVertex3f(80.0f + move, 422.0f, 0.0f);
	//
	glColor3f(128.0/255.0, 128.0 / 255.0, 128.0 / 255.0);
	glVertex3f(50.0f + move, 400.0f, 0.0f);
	glVertex3f(110.0f + move, 400.0f, 0.0f);
	glVertex3f(80.0f + move, 422.0f, 0.0f);
	//
	glColor3f(169.0/255.0, 169.0 / 255.0, 169.0 / 255.0);
	glVertex3f(50.0f + move, 450.0f, 0.0f);
	glVertex3f(50.0f + move, 400.0f, 0.0f);
	glVertex3f(80.0f + move, 422.0f, 0.0f);
	//
	glVertex3f(110.0f + move, 450.0f, 0.0f);
	glVertex3f(110.0f + move, 400.0f, 0.0f);
	glVertex3f(80.0f + move, 422.0f, 0.0f);

	glEnd();
	
	
	// wings

	glBegin(GL_POLYGON);
	glColor3f(25.0 / 255.0, 25.0 / 255.0, 112.0 / 255.0);
	glVertex3f(190.0f + move, 380.0f, 0.0f);
	glVertex3f(290.0f + move, 380.0f, 0.0f);
	glVertex3f(290.0f + move, 480.0f, 0.0f);
	glVertex3f(190.0f + move, 480.0f, 0.0f);
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(25.0 / 255.0, 25.0 / 255.0, 112.0 / 255.0);
	glVertex3f(-130.0f + move, 380.0f, 0.0f);
	glVertex3f(-30.0f + move, 380.0f, 0.0f);
	glVertex3f(-30.0f + move, 480.0f, 0.0f);
	glVertex3f(-130.0f + move, 480.0f, 0.0f);
	glEnd();

	glLineWidth(10);
	glBegin(GL_LINES);
	glVertex3f(17.0f + move, 470.0f, 0.0f);
	glVertex3f(-30.0f + move, 460.0f, 0.0f);
	glVertex3f(143.0f + move, 470.0f, 0.0f);
	glVertex3f(190.0f + move, 460.0f, 0.0f);

	glEnd();
	glLineWidth(3);
	
}

void rain() {


	int down = 0;
	for (int j = 0; j < 100; j++) {
		down += 20;
		int step = 0;
		if (j % 2 == 0)
			step = 0;
		else
			step = 20;
	for (int i = 0; i < 30; i++) {
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	//700
	//680
	glVertex3f(13.0f+step , 700.0f-down-rainDown, 0.0f);
	glVertex3f(10.0f+step , 680.0f-down-rainDown, 0.0f);
	step += 40;
	glEnd();
	}
	}
}

void lifebars() {
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(20.0f, 580.0f, 0.0f);
	glVertex3f(20.0f , 550.0f, 0.0f);
	glVertex3f(20+firstPlayerLife*50.0f , 550.0f, 0.0f);
	glVertex3f(20+firstPlayerLife*50.0f , 580.0f, 0.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(20.0f, 580.0f, 0.0f);
	glVertex3f(20.0f, 550.0f, 0.0f);
	glVertex3f(20+150.0f, 550.0f, 0.0f);
	glVertex3f(20+150.0f, 580.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(980.0f, 580.0f, 0.0f);
	glVertex3f(980.0f, 550.0f, 0.0f);
	glVertex3f(980-secondPlayerLife*50.0f, 550.0f, 0.0f);
	glVertex3f(980 - secondPlayerLife*50.0f, 580.0f, 0.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(980.0f, 580.0f, 0.0f);
	glVertex3f(980.0f, 550.0f, 0.0f);
	glVertex3f(980 - 3*50.0f, 550.0f, 0.0f);
	glVertex3f(980 - 3*50.0f, 580.0f, 0.0f);
	glEnd();

}

void powerbars() {
	glBegin(GL_POLYGON);
	glColor3f(235.0/255.0, 137.0 / 255.0, 52.0 / 255.0);
	glVertex3f(20.0f, 20.0f, 0.0f);
	glVertex3f(20.0f, 20+firstTimer, 0.0f);
	glVertex3f(40.0f, 20+firstTimer, 0.0f);
	glVertex3f(40.0f, 20.0f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(20.0f, 20.0f, 0.0f);
	glVertex3f(20.0f, 200.0f, 0.0f);
	glVertex3f(40.0f, 200.0f, 0.0f);
	glVertex3f(40.0f, 20.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(235.0 / 255.0, 137.0 / 255.0, 52.0 / 255.0);
	glVertex3f(980.0f, 20.0f, 0.0f);
	glVertex3f(980.0f, 20+secondTimer, 0.0f);
	glVertex3f(960.0f, 20+secondTimer, 0.0f);
	glVertex3f(960.0f, 20.0f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(980.0f, 20.0f, 0.0f);
	glVertex3f(980.0f, 200.0f, 0.0f);
	glVertex3f(960.0f, 200.0f, 0.0f);
	glVertex3f(960.0f, 20.0f, 0.0f);
	glEnd();

	

}

void clouds() {
	int nextCloud = 50;
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glTranslated(nextCloud, 550, 0);
	   glColor3f(169.0/255.0, 169.0 / 255.0, 169.0 / 255.0);
		for (double i = 0; i <= 3.14; i += 0.02) {
			double xCor = 50 * cos(i);
			double yCor = 50 * sin(i);
			
			glBegin(GL_LINES);
			glVertex2f(xCor, yCor);
			glVertex2f(xCor, -yCor - 10);
			glEnd();
		}
		for (double i = 0; i <= 3.14; i += 0.02) {
			double xCor = 40 * cos(i);
			double yCor = 40 * sin(i);
			
			glBegin(GL_LINES);
			glVertex2f(50 + xCor, yCor);
			glVertex2f(50 + xCor, -yCor - 10);
			glEnd();
		}
		for (double i = 0; i <= 3.14; i += 0.02) {
			double xCor = 30 * cos(i);
			double yCor = 30 * sin(i);
			
			glBegin(GL_LINES);
			glVertex2f(100 + xCor, yCor);
			glVertex2f(100 + xCor, -yCor - 10);
			glEnd();
		}
		for (double i = 0; i <= 3.14; i += 0.02) {
			double xCor = 40 * cos(i);
			double yCor = 40 * sin(i);
			
			glBegin(GL_LINES);
			glVertex2f(xCor - 50, yCor);
			glVertex2f(xCor - 50, -yCor - 10);
			glEnd();
		}
		for (double i = 0; i <= 3.14; i += 0.02) {
			double xCor = 30 * cos(i);
			double yCor = 30 * sin(i);
			
			glBegin(GL_LINES);
			glVertex2f(xCor - 100, yCor);
			glVertex2f(xCor - 100, -yCor - 10);
			glEnd();
		}
		nextCloud += 310;
		glPopMatrix();
	}
}

void buildings (){
	
	int ground = 0;
	int skyer = 100;
	for (int i = 0; i < 5; i++) {
	glBegin(GL_POLYGON);
	if (i % 2 != 0)
		skyer = 100;
	else
		skyer = 0;
	if (i % 3 == 0)
		skyer -= 25;
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.0f + ground, 0.0f, 0.0f);
	glVertex3f(0.0f + ground, 300.0f+skyer, 0.0f);
	glVertex3f(100.0f+ground, 300.0f+skyer, 0.0f);
	glVertex3f(100.0f + ground, 0.0f, 0.0f);
	glEnd();

	if (i % 2 == 0) {
		int dec = 10;
		for (int j = 0; j < 5; j++) {
			int sh = 0;
			for (int k = 0; k < 3; k++) {
				glBegin(GL_POLYGON);
				glColor3f(240.0 / 255.0, 230.0 / 255.0, 140.0 / 255.0);
				glVertex3f(15.0f + sh + ground, 300.0f+skyer - dec - 35, 0.0f);
				glVertex3f(15.0f + sh + ground, 300.0f + skyer - dec, 0.0f);
				glVertex3f(25.0f + sh + ground, 300.0f + skyer - dec, 0.0f);
				glVertex3f(25.0f + sh + ground, 300.0f + skyer - dec - 35, 0.0f);
				glEnd();
				sh += 20;
			}
			dec += 40;
		}
	}
	else {
	int dec = 10;
	for (int j = 0; j < 5; j++) {
	glBegin(GL_POLYGON);
	glColor3f(240.0/255.0, 230.0 / 255.0, 140.0 / 255.0);
	glVertex3f(15.0f + ground, 300.0f + skyer - dec-25, 0.0f);
	glVertex3f(15.0f + ground, 300.0f + skyer-dec, 0.0f);
	glVertex3f(45.0f + ground, 300.0f + skyer - dec, 0.0f);
	glVertex3f(45.0f + ground, 300.0f + skyer - dec - 25, 0.0f);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(55.0f + ground, 300.0f + skyer - dec - 25, 0.0f);
	glVertex3f(55.0f + ground, 300.0f + skyer - dec, 0.0f);
	glVertex3f(85.0f + ground, 300.0f + skyer- dec, 0.0f);
	glVertex3f(85.0f + ground, 300.0f + skyer - dec - 25, 0.0f);
	glEnd();

	dec += 35;
	}
	}

	ground += 100;
	}

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f + 500, 0.0f, 0.0f);
	glVertex3f(0.0f + 500, 400.0f , 0.0f);
	glVertex3f(62.0f + 500, 450.0f, 0.0f);
	glVertex3f(100.0f + 525, 400.0f , 0.0f);
	glVertex3f(100.0f + 525, 0.0f, 0.0f);
	glEnd();

	int dec = 10;
	for (int j = 0; j < 3; j++) {
		int sh = 0;
		for (int k = 0; k < 2; k++) {
		glBegin(GL_POLYGON);
		glColor3f(240.0 / 255.0, 230.0 / 255.0, 140.0 / 255.0);
		glVertex3f(520.0f  + sh, 400.0f  - dec - 35, 0.0f);
		glVertex3f(520.0f  + sh, 400.0f  - dec, 0.0f);
		glVertex3f(550.0f  + sh, 400.0f  - dec, 0.0f);
		glVertex3f(550.0f  + sh, 400.0f  - dec - 35, 0.0f);
		glEnd();
		sh += 50;
		}
		dec += 40;
	}



	 ground = 0;
	for (int i = 0; i < 5; i++) {
		glBegin(GL_POLYGON);
		if (i % 2 != 0)
			skyer = 100;
		else
			skyer = 0;
		if (i % 3 == 0)
			skyer -= 25;
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(625.0f + ground, 0.0f, 0.0f);
		glVertex3f(625.0f + ground, 300.0f + skyer, 0.0f);
		glVertex3f(725.0f + ground, 300.0f + skyer, 0.0f);
		glVertex3f(725.0f + ground, 0.0f, 0.0f);
		glEnd();
		if (i % 2 == 0) {
			int dec = 10;
			for (int j = 0; j < 5; j++) {
				int sh = 0;
				for (int k = 0; k < 3; k++) {
					glBegin(GL_POLYGON);
					glColor3f(240.0 / 255.0, 230.0 / 255.0, 140.0 / 255.0);
					glVertex3f(640.0f + sh + ground, 300.0f + skyer - dec - 35, 0.0f);
					glVertex3f(640.0f + sh + ground, 300.0f + skyer - dec, 0.0f);
					glVertex3f(650.0f + sh + ground, 300.0f + skyer - dec, 0.0f);
					glVertex3f(650.0f + sh + ground, 300.0f + skyer - dec - 35, 0.0f);
					glEnd();
					sh += 20;
				}
				dec += 40;
			}
		}
		else {
			int dec = 10;
			for (int j = 0; j < 5; j++) {
				glBegin(GL_POLYGON);
				glColor3f(240.0 / 255.0, 230.0 / 255.0, 140.0 / 255.0);
				glVertex3f(640.0f + ground, 300.0f + skyer - dec - 25, 0.0f);
				glVertex3f(640.0f + ground, 300.0f + skyer - dec, 0.0f);
				glVertex3f(670.0f + ground, 300.0f + skyer - dec, 0.0f);
				glVertex3f(670.0f + ground, 300.0f + skyer - dec - 25, 0.0f);
				glEnd();

				glBegin(GL_POLYGON);
				glVertex3f(680.0f + ground, 300.0f + skyer - dec - 25, 0.0f);
				glVertex3f(680.0f + ground, 300.0f + skyer - dec, 0.0f);
				glVertex3f(710.0f + ground, 300.0f + skyer - dec, 0.0f);
				glVertex3f(710.0f + ground, 300.0f + skyer - dec - 25, 0.0f);
				glEnd();

				dec += 35;
			}
		}
		ground += 100;

	}


}

void Display() {
	glClearColor(219.0/255.0, 0.0, 0, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	print(400, 550, (char*)lastGame);
	glLineWidth(1);
	buildings();
	batmanCall();
	//batmanCall2();
	rain();
	//clouds();
	createLeftHero();
	createRightHero();
	batmanSign();
	glLineWidth(3);

	createBorder();
	createShield();

	lifebars();
	powerbars();

	if(disapper==0)
     bezier(t, p0, p1, p2, p3);

	
	fans(1);
	fans(2);
	
	
	
	
	


	glFlush();
}

void Anim()
{
	fanWeaponsRot += 0.5;
	fanRot +=1.0;
	//moveCloud += 0.07;

	if (goCall < 20 && incCall)
		goCall+=0.05;
	else {
		incCall = 0;
		goCall-=0.05;
		if (goCall < -20)
			incCall = 1;
	}

	if (move < 1400 && state == 1) {
		move += 0.1;
	}
	else {
		move = -300;
		//state = 0;
		//move -= 0.1;
		//if (move < 10)
		//	state = 1;
	}

	if (stateFire &&fristPlayer && t < 1 ) {
		//left down
		p0[0] = 200;
		p0[1] = 100;

		//left up
		p1[0] = 200;
		p1[1] = 500;

		t += 0.0005;
	}
	//else if(fristPlayer && t>=1) {
		//rest();
		//t = 1;
		//disapper = 1;
		//fristPlayer = false;
		//switchIT = false;
		
	//}
	else if (stateFire && !fristPlayer && t > -0.2) {
		//right up
		p2[0] = 800;
		p2[1] = 500;

		//right down
		p3[0] = 800;
		p3[1] = 100;

		t -= 0.0005;
		
	}
	//else if(!fristPlayer && t<=0){
		//rest();
		//t = 0;
		//disapper = 1;
		//fristPlayer = true;
		//switchIT = false;
	//}

	if (jL > jumpLeft) {
		jumpLeft += 0.1;
	}
	else {
		jL = 0;
		jumpLeft = 0;
	}
	if (jR > jumpRight) {
		jumpRight += 0.1;
	}
	else {
		jR = 0;
		jumpRight = 0;
	}
	rainDown += 0.1;
	if (rainDown > 100)
		rainDown = 0;
	glutPostRedisplay();
}

void main(int argc, char** argr) {
	
	glutInit(&argc, argr);
	PlaySound(TEXT("bkSound.wav"), NULL, SND_ASYNC | SND_LOOP);

	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(200, 200);
	
	//left down
	p0[0] = 200;
	p0[1] = 100;

	//left up
	p1[0] = 200;
	p1[1] = 500;

	//right up
	p2[0] = 800;
	p2[1] = 500;

	//right down
	p3[0] = 800;
	p3[1] = 100;

	glutCreateWindow("OpenGL - 2D Template");
	glutDisplayFunc(Display);
	//PlaySound(TEXT("rain.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	glutIdleFunc(Anim);
	glutMouseFunc(mouseFunc);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	gluOrtho2D(0.0, 1000, 0, 600);

	glutMainLoop();
}


