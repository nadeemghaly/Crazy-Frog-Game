#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <string.h>
#include <glut.h>
#include <windows.h>

#define DEG2RAD 3.14159/180.0

int timeLeft = 60;
int score = 0;
int lanes = 0;
int finalScore = 0;

float charR = 20;
int charX = 390;
int charY = 40;

int PU1x = 0;
int PU1y = 0;
int PU2x = 0;
int PU2y = 0;
int PU3x = 0;
int PU3y = 0;

int Coin1x;
int Coin1y;
int Coin2x;
int Coin2y;
int Coin3x;
int Coin3y;
int Coin4x;
int Coin4y;
int coinRotation = 20;
int direction = 1;

int border = 15;

int numberOfLines;

int lines[8][4];

int flagEnd = 0;

int height;

void print(int x, int y, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void drawPlayer() {

	glPushMatrix();
	glColor3f(0, 1, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(charX, charY, 0);
	glVertex3d(charX - charR, charY + charR, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 1, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3d(charX, charY, 0);
	glVertex3d(charX + charR, charY + charR, 0);
	glEnd();
	glPopMatrix();



	glPushMatrix();
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3d(charX + charR / 8, charY, 0);
	glVertex3d(charX + charR / 8, charY - charR, 0);
	glVertex3d(charX + charR / 4, charY - charR, 0);
	glVertex3d(charX + charR / 4, charY, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3d(charX - charR / 8, charY, 0);
	glVertex3d(charX - charR / 8, charY - charR, 0);
	glVertex3d(charX - charR / 4, charY - charR, 0);
	glVertex3d(charX - charR / 4, charY, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(0.1, 0.63, 0.21);
	for (int i = 0;i < 360;i++)
	{
		float rad = i * DEG2RAD;
		glVertex2f(charX + cos(rad) * 0.4 * charR, charY + sin(rad) * 0.6 * charR);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex3d(charX - charR / 8, charY + charR, 0);
	glVertex3d(charX + charR / 8, charY + charR, 0);
	glVertex3d(charX, charY + 0.6 * charR, 0);
	glEnd();
	glPopMatrix();


}

void assignLines() {
	for (int i = 0;i < numberOfLines;i++) {
		int openingX = (rand() % 700) + (border + 5);

		lines[i][0] = 0;
		lines[i][1] = openingX;
		lines[i][2] = 100 + height * i;
		lines[i][3] = 105 + height * i;
	}

}

void assignPowerUps() {

	int heightnew = 0.5 * height;

	PU1x = (rand() % 730) + border + 15;
	PU1y = (rand() % heightnew) + 105 + ((rand() % (numberOfLines - 1)) * height) + 0.2 * height;

	PU2x = (rand() % 730) + border + 15;
	PU2y = (rand() % heightnew) + 105 + ((rand() % (numberOfLines - 1)) * height) + 0.2 * height;

	PU3x = (rand() % 730) + border + 15;
	PU3y = (rand() % heightnew) + 105 + ((rand() % (numberOfLines - 1)) * height) + 0.2 * height;
}

void spawnCoins() {

	int heightnew = 0.5 * height;

	Coin1x = (rand() % 730) + border + 15;
	Coin1y = (rand() % heightnew) + 105 + ((rand() % (numberOfLines - 1)) * height) + 0.2 * height;

	Coin2x = (rand() % 730) + border + 15;
	Coin2y = (rand() % heightnew) + 105 + ((rand() % (numberOfLines - 1)) * height) + 0.2 * height;

	Coin3x = (rand() % 730) + border + 15;
	Coin3y = (rand() % heightnew) + 105 + ((rand() % (numberOfLines - 1)) * height) + 0.2 * height;

	Coin4x = (rand() % 730) + border + 15;
	Coin4y = (rand() % heightnew) + 105 + ((rand() % (numberOfLines - 1)) * height) + 0.2 * height;
}

void drawCoins() {


	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(0.1, 0.63, 0.21);
	for (int i = 0;i < 360;i++)
	{
		float rad = i * DEG2RAD;
		glVertex2f(Coin1x + cos(rad) * coinRotation, Coin1y + sin(rad) * 20);
	}
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3d(Coin1x - coinRotation, Coin1y - 20, 0);
	glVertex3d(Coin1x + coinRotation, Coin1y + 18, 0);
	glVertex3d(Coin1x + coinRotation, Coin1y + 20, 0);
	glVertex3d(Coin1x - coinRotation, Coin1y - 18, 0);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(0.1, 0.63, 0.21);
	for (int i = 0;i < 360;i++)
	{
		float rad = i * DEG2RAD;
		glVertex2f(Coin2x + cos(rad) * coinRotation, Coin2y + sin(rad) * 20);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3d(Coin2x - coinRotation, Coin2y - 20, 0);
	glVertex3d(Coin2x + coinRotation, Coin2y + 18, 0);
	glVertex3d(Coin2x + coinRotation, Coin2y + 20, 0);
	glVertex3d(Coin2x - coinRotation, Coin2y - 18, 0);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(0.1, 0.63, 0.21);
	for (int i = 0;i < 360;i++)
	{
		float rad = i * DEG2RAD;
		glVertex2f(Coin3x + cos(rad) * coinRotation, Coin3y + sin(rad) * 20);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3d(Coin3x - coinRotation, Coin3y - 20, 0);
	glVertex3d(Coin3x + coinRotation, Coin3y + 18, 0);
	glVertex3d(Coin3x + coinRotation, Coin3y + 20, 0);
	glVertex3d(Coin3x - coinRotation, Coin3y - 18, 0);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(0.1, 0.63, 0.21);
	for (int i = 0;i < 360;i++)
	{
		float rad = i * DEG2RAD;
		glVertex2f(Coin4x + cos(rad) * coinRotation, Coin4y + sin(rad) * 20);
	}
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3d(Coin4x - coinRotation, Coin4y - 20, 0);
	glVertex3d(Coin4x + coinRotation, Coin4y + 18, 0);
	glVertex3d(Coin4x + coinRotation, Coin4y + 20, 0);
	glVertex3d(Coin4x - coinRotation, Coin4y - 18, 0);
	glEnd();
	glPopMatrix();
}

void drawLines() {

	for (int i = 0;i < numberOfLines;i++) {

		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslated(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3d(lines[i][0], lines[i][2], 0);
		glVertex3d(lines[i][0], lines[i][3], 0);
		glVertex3d(lines[i][1], lines[i][3], 0);
		glVertex3d(lines[i][1], lines[i][2], 0);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslated(0, 0, 0);
		glBegin(GL_QUADS);
		glVertex3d(lines[i][1] + 50, lines[i][2], 0);
		glVertex3d(lines[i][1] + 50, lines[i][3], 0);
		glVertex3d(800, lines[i][3], 0);
		glVertex3d(800, lines[i][2], 0);
		glEnd();
		glPopMatrix();
	}
}

void drawHeader() {
	glPushMatrix();
	glColor3f(0, 0.5, 0);
	glTranslated(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3d(0, 750, 0);
	glVertex3d(0, 800, 0);
	glVertex3d(800, 800, 0);
	glVertex3d(800, 750, 0);
	glEnd();
	glPopMatrix();
}

void drawBorders() {
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3d(0, 0, 0);
	glVertex3d(0, border, 0);
	glVertex3d(800, border, 0);
	glVertex3d(800, 0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3d(0, 750 - border, 0);
	glVertex3d(0, 750, 0);
	glVertex3d(800, 750, 0);
	glVertex3d(800, 750 - border, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 750, 0);
	glVertex3d(border, 750, 0);
	glVertex3d(border, 0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3d(800 - border, 0, 0);
	glVertex3d(800 - border, 750, 0);
	glVertex3d(800, 750, 0);
	glVertex3d(800, 0, 0);
	glEnd();
	glPopMatrix();
}

void drawPowerUps() {

	//PU1

	glPushMatrix();
	glColor3f(1, 0.63, 0.48);
	glTranslated(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3d(PU1x - 15, PU1y - 15, 0);
	glVertex3d(PU1x - 15, PU1y + 15, 0);
	glVertex3d(PU1x + 15, PU1y + 15, 0);
	glVertex3d(PU1x + 15, PU1y - 15, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glVertex3d(PU1x - 10, PU1y, 0);
	glVertex3d(PU1x + 10, PU1y, 0);
	glVertex3d(PU1x, PU1y - 10, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glVertex3d(PU1x - 10, PU1y + 10, 0);
	glVertex3d(PU1x + 10, PU1y + 10, 0);
	glVertex3d(PU1x, PU1y, 0);
	glEnd();
	glPopMatrix();

	//PU2

	glPushMatrix();
	glColor3f(0.8, 0.36, 0.36);
	glTranslated(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3d(PU2x - 15, PU2y - 15, 0);
	glVertex3d(PU2x - 15, PU2y + 15, 0);
	glVertex3d(PU2x + 15, PU2y + 15, 0);
	glVertex3d(PU2x + 15, PU2y - 15, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glVertex3d(PU2x - 12, PU2y, 0);
	glVertex3d(PU2x - 7, PU2y, 0);
	glVertex3d(PU2x - 7, PU2y + 5, 0);
	glVertex3d(PU2x - 7, PU2y, 0);
	glVertex3d(PU2x - 7, PU2y - 5, 0);
	glVertex3d(PU2x - 7, PU2y, 0);
	glVertex3d(PU2x - 2, PU2y, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glBegin(GL_LINE_STRIP);
	glVertex3d(PU2x + 12, PU2y + 5, 0);
	glVertex3d(PU2x + 5, PU2y + 5, 0);
	glVertex3d(PU2x + 5, PU2y + 1, 0);
	glVertex3d(PU2x + 12, PU2y + 1, 0);
	glVertex3d(PU2x + 12, PU2y - 5, 0);
	glVertex3d(PU2x + 4, PU2y - 5, 0);
	glEnd();
	glPopMatrix();

	//PU3

	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslated(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3d(PU3x - 15, PU3y - 15, 0);
	glVertex3d(PU3x - 15, PU3y + 15, 0);
	glVertex3d(PU3x + 15, PU3y + 15, 0);
	glVertex3d(PU3x + 15, PU3y - 15, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3d(PU3x - 10, PU3y - 10, 0);
	glVertex3d(PU3x - 10, PU3y - 8, 0);
	glVertex3d(PU3x + 10, PU3y - 8, 0);
	glVertex3d(PU3x + 10, PU3y - 10, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3d(PU3x - 3, PU3y - 10, 0);
	glVertex3d(PU3x - 3, PU3y - 8, 0);
	glVertex3d(PU3x + 3, PU3y - 8, 0);
	glVertex3d(PU3x + 3, PU3y - 10, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3d(PU3x - 1, PU3y, 0);
	glVertex3d(PU3x - 1, PU3y + 7, 0);
	glVertex3d(PU3x + 1, PU3y + 7, 0);
	glVertex3d(PU3x + 1, PU3y, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glVertex3d(PU3x - 4, PU3y + 7, 0);
	glVertex3d(PU3x + 4, PU3y + 7, 0);
	glVertex3d(PU3x, PU3y + 13, 0);
	glEnd();
	glPopMatrix();
}

void endGame() {

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 800, 0);
	glVertex3d(800, 800, 0);
	glVertex3d(800, 0, 0);
	glEnd();
	glPopMatrix();
}

void drawGoal() {
	glPushMatrix();
	glColor3f(0.5, 0.2, 0.7);
	glTranslated(0, 0, 0);
	glBegin(GL_POLYGON);

	glVertex3d(380, 700, 0);
	glVertex3d(380, 660, 0);
	glVertex3d(420, 660, 0);
	glVertex3d(420, 700, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.2, 0.7);
	glBegin(GL_TRIANGLES);
	glVertex3d(380, 700, 0);
	glVertex3d(380, 660, 0);
	glVertex3d(400, 680, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.2, 0.7);
	glBegin(GL_TRIANGLES);
	glVertex3d(420, 700, 0);
	glVertex3d(420, 660, 0);
	glVertex3d(400, 680, 0);
	glEnd();
	glPopMatrix();

}

void winGame() {

	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslated(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 800, 0);
	glVertex3d(800, 800, 0);
	glVertex3d(800, 0, 0);
	glEnd();
	glPopMatrix();
}

void Display() {

	char* p0s[20];
	if (flagEnd == 2) {
		winGame();

		glColor3f(0.1, 0.1, 0.1);

		sprintf((char*)p0s, "You have WON!!!");
		print(300, 400, (char*)p0s);

		sprintf((char*)p0s, "score : %d", finalScore);
		print(335, 335, (char*)p0s);
		glFlush();
		return;
	}

	if (flagEnd == 1) {
		endGame();

		glColor3f(0.1, 0.1, 0.1);

		sprintf((char*)p0s, "You have lost");
		print(300, 400, (char*)p0s);


		sprintf((char*)p0s, "score : %d", score);
		print(335, 335, (char*)p0s);

		glFlush();
		return;

	}


	glClearColor(1, 1, 1, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	drawPlayer();

	drawHeader();

	drawBorders();

	drawGoal();

	drawPowerUps();

	drawCoins();

	drawLines();

	glColor3f(0.1, 0.1, 0.1);


	sprintf((char*)p0s, "Time : %d", timeLeft);
	print(50, 765, (char*)p0s);

	sprintf((char*)p0s, "Score : %d", score);
	print(350, 765, (char*)p0s);

	sprintf((char*)p0s, "Lane : %d", lanes);
	print(650, 765, (char*)p0s);

	if (380 < charX && charX < 420 && 660 < charY && charY < 700) {
		flagEnd = 2;
		finalScore = score + timeLeft * 10;
		PlaySound(TEXT("smb_world_clear.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	glFlush();
}

void key(unsigned char k, int x, int y)// keyboard special key function takes 3 parameters
							// int k: is the special key pressed such as the keyboard arrows the f1,2,3 and so on
{
	if (k == 'd') {//if the right arrow is pressed, then the object will be translated in the x axis by 10. (moving right)
		if (!(charX + charR + 10 + border > 800)) {
			for (int i = 0;i < numberOfLines;i++) {
				if (((charY - charR < lines[i][2] && lines[i][2] < charY + charR) || (charY - charR < lines[i][3] && lines[i][3] < charY + charR)) && charX + charR + 10 > lines[i][1] + 50) {
					PlaySound(TEXT("smb_stomp.wav"), NULL, SND_ASYNC | SND_FILENAME);
					return;
				}
			}
			charX += 10;
		}
		else PlaySound(TEXT("smb_stomp.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	if (k == 'a') {//if the left arrow is pressed, then the object will be translated in the x axis by -10. (moving left)
		if (!(charX - charR - 10 - border < 0)) {
			for (int i = 0;i < numberOfLines;i++) {
				if (((charY - charR < lines[i][2] && lines[i][2] < charY + charR) || (charY - charR < lines[i][3] && lines[i][3] < charY + charR)) && charX - charR - 10 < lines[i][1]) {
					PlaySound(TEXT("smb_stomp.wav"), NULL, SND_ASYNC | SND_FILENAME);
					return;
				}
			}
			charX -= 10;
		}
		else PlaySound(TEXT("smb_stomp.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	if (k == 'w') {//if the up arrow is pressed, then the object will be translated in the y axis by 10. (moving upwords)
		if (!(charY + charR + 10 + border > 750)) {   //20 for radius, 10 for movement 15 for borders
			for (int i = 0;i < numberOfLines;i++) {
				if (((charY + charR + 10 > lines[i][2]) && charY - charR < lines[i][2]) && ((charX - charR < lines[i][1]) || (charX + charR > lines[i][1] + 50))) {
					PlaySound(TEXT("smb_stomp.wav"), NULL, SND_ASYNC | SND_FILENAME);
					return;
				}
			}
			charY += 10;
		}
		else PlaySound(TEXT("smb_stomp.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	if (k == 's') {//if the down arrow is pressed, then the object will be translated in the y axis by -10. (moving downwords)
		if (!(charY - charR - 10 - border < 0)) {   //20 for radius, 10 for movement 15 for borders
			for (int i = 0;i < numberOfLines;i++) {
				if (((charY - charR - 10 < lines[i][3]) && charY + charR > lines[i][3]) && ((charX - charR < lines[i][1]) || (charX + charR > lines[i][1] + 50))) {
					PlaySound(TEXT("smb_stomp.wav"), NULL, SND_ASYNC | SND_FILENAME);
					return;
				}
			}
			charY -= 10;
		}
		else PlaySound(TEXT("smb_stomp.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}


	lanes = 0;
	for (int i = 0;i < numberOfLines;i++) {
		if (charY - charR / 2 > lines[i][3])
			lanes += 1;
	}

	// POWER UPS 

	if (PU1x - 15 - charR < charX && charX < PU1x + 15 + charR && PU1y - 15 - charR < charY && charY < PU1y + 15 + charR) {
		PU1x = -200;
		PU1y = -200;
		charR = charR / 2;

		PlaySound(TEXT("smb_flagpole.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}

	if (PU2x - 15 - charR < charX && charX < PU2x + 15 + charR && PU2y - 15 - charR < charY && charY < PU2y + 15 + charR) {
		PU2x = -200;
		PU2y = -200;
		timeLeft += 5;

		PlaySound(TEXT("smb_pipe.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}

	if (PU3x - 15 - charR < charX && charX < PU3x + 15 + charR && PU3y - 15 - charR < charY && charY < PU3y + 15 + charR) {
		PU3x = -200;
		PU3y = -200;
		lines[lanes][1] = charX - 25;
		PlaySound(TEXT("smb_jump-super.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}


	if (Coin1x - 15 - charR < charX && charX < Coin1x + 15 + charR && Coin1y - 15 - charR < charY && charY < Coin1y + 15 + charR) {
		Coin1x = -200;
		Coin1y = -200;
		score += 50;

		PlaySound(TEXT("smb_coin.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}


	if (Coin2x - 15 - charR < charX && charX < Coin2x + 15 + charR && Coin2y - 15 - charR < charY && charY < Coin2y + 15 + charR) {
		Coin2x = -200;
		Coin2y = -200;
		score += 50;

		PlaySound(TEXT("smb_coin.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}


	if (Coin3x - 15 - charR < charX && charX < Coin3x + 15 + charR && Coin3y - 15 - charR < charY && charY < Coin3y + 15 + charR) {
		Coin3x = -200;
		Coin3y = -200;
		score += 50;

		PlaySound(TEXT("smb_coin.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}


	if (Coin4x - 15 - charR < charX && charX < Coin4x + 15 + charR && Coin4y - 15 - charR < charY && charY < Coin4y + 15 + charR) {
		Coin4x = -200;
		Coin4y = -200;
		score += 50;

		PlaySound(TEXT("smb_coin.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}

	glutPostRedisplay();//redisplay to update the screen with the changes
}

void timerLines(int val)//timer animation function, allows the user to pass an integer value to the timer function.
{
	assignLines();
	glutPostRedisplay();						// redraw 		
	glutTimerFunc(20000, timerLines, 0);					//recall the time function after 1000 ms and pass a zero value as an input to the time func.

}

void timer(int val)//timer animation function, allows the user to pass an integer value to the timer function.
{
	timeLeft -= 1;
	if (timeLeft == 0 && flagEnd != 2) {
		flagEnd = 1;
		PlaySound(TEXT("smb_gameover.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	glutPostRedisplay();						// redraw
	glutTimerFunc(1000, timer, 0);					//recall the time function after 1000 ms and pass a zero value as an input to the time func.

}

void timerPowerUps(int val)//timer animation function, allows the user to pass an integer value to the timer function.
{
	assignPowerUps();

	glutPostRedisplay();						// redraw
	glutTimerFunc(30000, timerPowerUps, 0);					//recall the time function after 1000 ms and pass a zero value as an input to the time func.

}

void timerCoinRotation(int val)//timer animation function, allows the user to pass an integer value to the timer function.
{
	if (direction == 1)
		coinRotation = coinRotation - 1;
	else
		coinRotation = coinRotation + 1;

	if (coinRotation == -20 || coinRotation == 20)
		direction = -direction;
	glutPostRedisplay();						// redraw
	glutTimerFunc(100, timerCoinRotation, 0);					//recall the time function after 1000 ms and pass a zero value as an input to the time func.

}

void main(int argc, char** argr) {

	srand((unsigned)time(0));
	numberOfLines = (rand() % 5) + 4;
	height = 600 / numberOfLines;

	spawnCoins();

	glutInit(&argc, argr);

	glutInitWindowSize(700, 700);
	glutInitWindowPosition(150, 0);
	glutCreateWindow("Control");
	glutDisplayFunc(Display);
	glutKeyboardFunc(key);			//call the keyboard function
	glutTimerFunc(0, timerLines, 0);		//call the timer function
	glutTimerFunc(0, timer, 0);
	glutTimerFunc(0, timerPowerUps, 0);
	glutTimerFunc(0, timerCoinRotation, 0);
	glPointSize(25);				//change the point size to be 25
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 800, 0.0, 800);

	glutMainLoop();
}
