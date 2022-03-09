#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
/*#include <iostream.h> */
#include "glut.h"

//Y location for players paddles
GLint pOney[2] = {190, 290};
GLint pTwoy[2] = {190, 290};

//Location of ball
GLint ball[4] = { 325, 245, 315, 235 };

//ballDir is used to indicate direction ball is moving
int ballDir = 3;

void drawDot(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void myKeyboard(unsigned char key, int mouseX, int mouseY)
{ 
	glClear(GL_COLOR_BUFFER_BIT);

	//change paddle locations
	if (key == 'w') {
		pOney[0] += 30;
		pOney[1] += 30;
	}
	else if (key == 's') {
		pOney[0] -= 30;
		pOney[1] -= 30;
	}
	else if (key == 'i') {
		pTwoy[0] += 30;
		pTwoy[1] += 30;
	}
	else if (key == 'k') {
		pTwoy[0] -= 30;
		pTwoy[1] -= 30;
	}

	
}


void Display()
{
	
	 
	glClear(GL_COLOR_BUFFER_BIT);

	glRecti(10, pOney[0], 20, pOney[1]);
	glRecti(620, pTwoy[0], 630, pTwoy[1]);
	glRecti(ball[0], ball[1], ball[2], ball[3]);

	glFlush();
	
	Sleep(50);


	//change ball location
	if (ballDir == 1) {
		ball[0] += 10;
		ball[1] += 10;
		ball[2] += 10;
		ball[3] += 10;
	}
	else if (ballDir == 2) {
		ball[0] += 10;
		ball[1] -= 10;
		ball[2] += 10;
		ball[3] -= 10;
	}
	else if (ballDir == 3) {
		ball[0] -= 10;
		ball[1] -= 10;
		ball[2] -= 10;
		ball[3] -= 10;
	}
	else {
		ball[0] -= 10;
		ball[1] += 10;
		ball[2] -= 10;
		ball[3] += 10;
	}
	//check if ball is bouncing off top and bottom
	if (ball[3] < 0) {
		if (ballDir == 2) {
			ballDir = 1;
		}
		else {
			ballDir = 4;
		}
	}
	if (ball[1] > 480) {
		if (ballDir == 1) {
			ballDir = 2;
		}
		else {
			ballDir = 3;
		}
	}
	//check if ball hit paddle
	if (ball[2] == 15) {
		if (ball[1] < pOney[1] && ball[3] > pOney[0]) {
			if (ballDir == 3) {
				ballDir = 2;
			}
			else {
				ballDir = 1;
			}
		}
	}
	if (ball[0] == 625) {
		if (ball[1] < pTwoy[1] && ball[3] > pTwoy[0]) {
			if (ballDir == 1) {
				ballDir = 4;
			}
			else {
				ballDir = 3;
			}
		}
	}
	//check if ball is out of bounds
	if (ball[2] < 0 || ball[0] > 640) {
		ball[0] = 325;
		ball[1] = 245;
		ball[2] = 315;
		ball[3] = 235;
	}


	glutPostRedisplay();

}

void Init()
{
	glClearColor(1.0,1.0,1.0,0.0);
   glColor3f(0.0f,0.0f,0.0f);
   glPointSize(4.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(1.0,640.0,0.0,480.0);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("my first attempt");
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(Display);
	Init();
	glutMainLoop();
}
