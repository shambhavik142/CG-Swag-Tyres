#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>    // Header File For The OpenGL32 Library
#include <GL/glu.h>
#include<math.h>
#include<stdlib.h>
// Header File For The GLu32 Library
//#include <unistd.h>     // Header File For sleeping.
#include "roadGrip.h"

/* ASCII code for the escape key. */
#define ESCAPE 27

/* The number of our GLUT window */
int windowrg;

/* rotation angle for the triangle. */
float rtrirg = -4.0f;
float xrtrirg = -0.75f;
int lr = 1;

/* rotation angle for the quadrilateral. */
float rquadrg = 0.0f;

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
// We call this right aftrger our OpenGL window is created.
void InitGLR(int Width, int Height)
{
	// This Will Clear The Background Color To Black
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0);                // Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LESS);                // The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST);            // Enables Depth Testing
	glShadeModel(GL_SMOOTH);            // Enables Smooth Color Shading

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();                // Reset The Projection Matrix

	gluPerspective(45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeSceneRG(int Width, int Height)
{
	if (Height == 0)                // Prevent A Divide By Zero If The Window Is Too Small
		Height = 1;

	glViewport(0, 0, Width, Height);        // Reset The Current Viewport And Perspective Transformation

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}









void drawRoad1() {


	glLineWidth(6);
	glBegin(GL_LINES);
	glColor3ub(255, 255, 255);

	//divider
	glVertex2f(-5.0f, 6.0f);
	glVertex2f(-5.0f, 3.0f);

	glVertex2f (- 5.0f, 2.0f);
	glVertex2f(-5.0f, -1.0f);

	glVertex2f(-5.0f, -2.0f);
	glVertex2f(-5.0f, -5.0f);
	glEnd();
	glLineWidth(3);

	//road
	glBegin(GL_POLYGON);
	glColor3ub(80, 80, 80);
	glVertex2f(-7.0f, 8.0f);
	glVertex2f(-3.0f, 8.0f);
	glVertex2f(-2.5, -8.0f);
	glVertex2f(-7.5f, -8.0f);
	glEnd();
}

void drawCar1()
{
	glBegin(GL_POLYGON);
	glColor3ub(256, 234, 90);
	glVertex3f(-5.6f, 1.5f,1.0);
	glVertex3f(-3.8f, 1.5f,1.0);
	glVertex3f(-3.4f, -1.5f,1.0);
	glVertex3f(-6.0f, -1.5f,1.0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(246, 244, 90);
	glVertex3f(-5.0f, 0.75f, 1.5);
	glVertex3f(-4.0f, 0.75f, 1.5);
	glVertex3f(-3.8f, -0.75f, 1.5);
	glVertex3f(-5.2f, -0.75f, 1.5);
	glEnd();

	rtrirg += 0.015f;                    // Increase The Rotation Variable For The Triangle
	if (rtrirg > 4.0)
		rtrirg = -4.0;
}

void drawRoad2() {


	glLineWidth(6);
	glBegin(GL_LINES);
	glColor3ub(255, 255, 255);

	//divider
	glVertex2f(5.5f, 6.0f);
	glVertex2f (5.5f, 3.0f);

	glVertex2f(5.5f, 2.0f);
	glVertex2f(5.5f, -1.0f);

	glVertex2f(5.5f, -2.0f);
	glVertex2f(5.5f, -5.0f);
	glEnd();
	glLineWidth(3);

	//road
	glBegin(GL_POLYGON);
	glColor3ub(80, 80, 80);
	glVertex2f(3.5f, 8.0f);
	glVertex2f(7.5f, 8.0f);
	glVertex2f(8.0, -8.0f);
	glVertex2f(3.0f, -8.0f);
	glEnd();
}

void drawCar2()
{
	glBegin(GL_POLYGON);
	glColor3ub(246, 244, 90);
	glVertex3f(4.3f-xrtrirg/3, 1.5f, 1.0);
	glVertex3f(6.1f-xrtrirg/3, 1.5f, 1.0);
	glVertex3f(6.5f+xrtrirg, -1.5f, 1.0);
	glVertex3f(3.9f+xrtrirg, -1.5f, 1.0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(256, 234, 90);
	glVertex3f(4.5f-xrtrirg/5, 0.75f, 1.5);
	glVertex3f(5.5f-xrtrirg/5, 0.75f, 1.5);
	glVertex3f(5.7f+xrtrirg/2, -0.75f, 1.5);
	glVertex3f(4.3f+xrtrirg/2, -0.75f, 1.5);
	glEnd();

	if (xrtrirg > 0.5)
		lr = 0;
	if (xrtrirg < -0.5)
		lr = 1;

	if (lr == 1)
		xrtrirg += 0.005f;                    // Increase The Rotation Variable For The Triangle
	else
		xrtrirg -= 0.005f;

}


/* The main drawing function. */
void roadGrip_display()
{

	glClearColor(115 / 255.0, 194 / 255.0, 251 / 255.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        // Clear The Screen And The Depth Buffer
	glLoadIdentity();                // Reset The View



	glTranslatef(0.0f, 0.0f, -15.0f);

	glColor3f(0.5, 0.5, 1.0);
	   glBegin(GL_LINES);
	      if(glutGet(GLUT_ELAPSED_TIME) % 3 == 0) {
	       	  for (int i=0; i<50; i++) {
	       		  int x = -8 + (rand() % 17);
	       		  int y = -5 + (rand() % 11);
	       		  glVertex2d(x,y);
	       		  glVertex2d(0.15+x,0.5+y);
	       	  }
	      }
	   glEnd();

	drawRoad1();
	glTranslatef(0.0, rtrirg, 0.0f);
		drawCar1();
	glTranslatef(0.0, -rtrirg, 0.0f);

	drawRoad2();
	glTranslatef(0.0f, rtrirg, 0.0f);
		drawCar2();
	glTranslatef(0.0f, -rtrirg, 0.0f);


	        // Move Leftrg 1.5 Units And Into The Screen 6.0
		   // Move Leftrg 1.5 Units And Into The Screen 6.0




	// swap the buffers to display, since double buffering is used.
	glutSwapBuffers();
}

/* The function called whenever a key is pressed. */
void keyPressedRoadGrip(unsigned char key, int x, int y)
{
	if (key == (unsigned char)'b')
		menuMain();
}

int roadGripMain()
{
	//glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

	/* get a 640 x 480 window */
	//glutInitWindowSize(640, 480);

	/* the window starts at the upper leftrg corner of the screen */
	//glutInitWindowPosition(0, 0);

	/* Open a window */
	//window = glutCreateWindow("Moving Car");

	glutKeyboardFunc(keyPressedRoadGrip);

	/* Register the function to do all our OpenGL drawing. */
	glutDisplayFunc(roadGrip_display);

	/* Go fullscreen.  This is as soon as possible. */
	glutFullScreen();

	/* Even if there are no events, redraw our gl scene. */
	glutIdleFunc(&roadGrip_display);

	/* Register the function called when our window is resized. */
	glutReshapeFunc(&ReSizeSceneRG);

	/* Initialize our window. */
	InitGLR(640, 480);

	glEnable(GL_DEPTH_TEST);

	/* Start Event Processing Engine */
	glutMainLoop();

	return 1;
}
