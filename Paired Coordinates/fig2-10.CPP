#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <iostream>
#include "glut.h"
// #include <String>
#include <fstream>

using namespace std;

class GLintPoint {
public:
	GLint x, y;
};

class GLintPointArray {
	const int MAX_NUM = 100;
	public:
		int num;
		GLintPoint pt[100];
};

void Display();
void Init(void);
void drawDot(int x, int y);
void drawPolyLine(GLintPointArray poly, int closed);
void drawCartesianPlane(int numAtts);
void drawData(string file);

int random(int m) { return rand() % m; }

void main (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 860);
	glutInitWindowPosition(100,150);
	glutCreateWindow("Group 4: Paired Coordinates");
   glutDisplayFunc(Display);
   Init();
	glutMainLoop();


}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawData("cancer_wisconsin_origional.txt");
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

void drawDot(int x, int y, int colorClass)
{

	// set a different color based on class
	switch (colorClass)
	{
		case -1:
			glColor3f(1.0, 0.0, 0.0);	//set color to red
			break;
		
		case 0:
			glColor3f(0.0, 1.0, 0.0);	// set color to green
			break;

		case 1:
			glColor3f(0.0, 0.0, 1.0);	// set color to blue
			break;

		case 2:
			glColor3f(0.0, 1.0, 1.0);	// set color to cyan
			break;

		case 3:
			glColor3f(1.0, 1.0, 0.0);	// set color to yellow
			break;

		default:
			glColor3f(0.0, 0.0, 0.0);	// default is black
			break;
	}

	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
}

void drawPolyLine(GLintPointArray poly, int closed, int colorClass)
{
	// set a different color based on class
	switch (colorClass)
	{
	case -1:
		glColor3f(1.0, 0.0, 0.0);	//set color to red
		break;

	case 0:
		glColor3f(0.0, 1.0, 0.0);	// set color to green
		break;

	case 1:
		glColor3f(0.0, 0.0, 1.0);	// set color to blue
		break;

	case 2:
		glColor3f(0.0, 1.0, 1.0);	// set color to cyan
		break;

	case 3:
		glColor3f(1.0, 1.0, 0.0);	// set color to yellow
		break;

	default:
		glColor3f(0.0, 0.0, 0.0);	// default is black
		break;
	}

	glBegin(closed ? GL_LINE_LOOP : GL_LINE_STRIP);
		for (int i = 0; i < poly.num; i++)
		{
			glVertex2i((poly.pt[i].x * 10) + (5 + (i * 120)), ((poly.pt[i].y * 10) + 5));	// values adjusted to fit better on screen
		}
	glEnd();
	glFlush();
}

// draw cartesian plane
void drawCartesianPlane(int numAtts)
{
	// variable to hold num planes
	int numPlanes = 1;

	// get how many planes are needed
	if (numAtts % 2 == 0)
	{
		numPlanes = numAtts / 2;
	}
	else
	{
		numPlanes = (numAtts / 2) + 1;
	}

	// draw planes
	for (int i = 0; i < numPlanes; i++)
	{
		float vert1X = 5 + (i * 120);


		float vert1Y = 5;

		float vert2X = vert1X;
		float vert2Y = 120;

		float vert3X = vert1X;
		float vert3Y = 5;

		float vert4X = 120 + (i * 120);


		float vert4Y = 5;

		glBegin(GL_LINES);
			// pane drawing
			glVertex2f(vert1X, vert1Y);
			glVertex2f(vert2X, vert2Y);
			glVertex2f(vert3X, vert3Y);
			glVertex2f(vert4X, vert4Y);
		glEnd();
		glFlush();
	}
}

// read the file 
void drawData(string file)
{
	ifstream myFile (file);

	// pt array
	GLintPointArray data;

	if (myFile.is_open())
	{
		int numAttributes;

		myFile >> numAttributes;

		
		// numAttributes--;

		int numPoints = 0;

		bool isEven;

		// reduce by one to account for class designation
		if (numAttributes - 1 % 2 == 0)
		{
			isEven = true;
			numPoints = (numAttributes - 1) / 2; 
		}
		else
		{
			isEven = false;
			numPoints = ((numAttributes - 1) / 2) + 1;
		}

		data.num = numPoints;

		int dataClass;

		drawCartesianPlane(numAttributes);
		
		while (myFile) 
		{

			// read a single line of data
			for (int i = 0; i < numPoints; i++)
			{
				if (i < numPoints - 1)
				{

					myFile >> data.pt[i].x;
					myFile >> data.pt[i].y;



				}
				else
				{
					if (isEven == false && i == numPoints - 1)	// handles case where odd number of attributes needing to be duplicated for last point
					{
						myFile >> data.pt[i].x;
						data.pt[i].y = data.pt[i].x;
						myFile >> dataClass; // get the class from the end of the line
					}
					else
					{
						myFile >> data.pt[i].x;
						myFile >> data.pt[i].y;
						myFile >> dataClass; // get the class from the end of the line
					}

				}

			}
			
			// for loop to draw points
			for (int i = 0; i < numPoints; i++)
			{
				// draw the points
				drawDot((data.pt[i].x * 10) + (5 + (i * 120)), ((data.pt[i].y * 10) + 5), dataClass);	//values adjusted to fit better on screen

				// draw the lines
				drawPolyLine(data, 0, dataClass);	// data array, 0 for closed, class
			}

		}
		
	}

}