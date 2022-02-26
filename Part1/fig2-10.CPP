#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
/*#include <iostream.h> */
#include "glut.h"

GLint pOney[2] = {190, 290};
GLint pTwoy[2] = {190, 290};

void drawDot(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void myKeyboard(unsigned char key, int mouseX, int mouseY)
{
	//GLint x = mouseX;
	//GLint y = 480 - mouseY; 
	glClear(GL_COLOR_BUFFER_BIT);
	if (key == 'w') {
		pOney[0] += 10;
		pOney[1] += 10;
	}
	else if (key == 's') {
		pOney[0] -= 10;
		pOney[1] -= 10;
	}
	else if (key == 'i') {
		pTwoy[0] += 10;
		pTwoy[1] += 10;
	}
	else if (key == 'k') {
		pTwoy[0] -= 10;
		pTwoy[1] -= 10;
	}


	glRecti(10, pOney[0], 20, pOney[1]);
	glRecti(620, pTwoy[0], 630, pTwoy[1]);
	glFlush();
}


void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRecti(10,pOney[0], 20, pOney[1]);
	glRecti(620, pTwoy[0], 630, pTwoy[1]);
   glFlush();
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
