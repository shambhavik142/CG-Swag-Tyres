#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>    // Header File For The OpenGL32 Library
#include <GL/glu.h>    // Header File For The GLu32 Library
//#include <unistd.h>     // Header File For sleeping.
#include "terrain.h"

/* ASCII code for the escape key. */
#define ESCAPE 27

/* The number of our GLUT window */
int window; 

/* rotation angle for the triangle. */
float rtri = -7.0f;

/* rotation angle for the quadrilateral. */
float rquad = 0.0f;

float up1 = 8.6f;
float jitterx = 2.0f;
float jittery = 0.0f;
int goupx = 0;
int goupy = 0;

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
// We call this right after our OpenGL window is created.
void InitGL(int Width, int Height)         
{
  // This Will Clear The Background Color To Black
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);     
  glClearDepth(1.0);                // Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);                // The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);            // Enables Depth Testing
  glShadeModel(GL_SMOOTH);            // Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();                // Reset The Projection Matrix

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);  

  glMatrixMode(GL_MODELVIEW);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)                // Prevent A Divide By Zero If The Window Is Too Small
    Height=1;

  glViewport(0, 0, Width, Height);        // Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
}

float fballu = -0.3f;
float fpart1u = -0.3;
float fpart2u = -0.7;
float fpart3u = -0.9;

float fballd = 0.55f;
float fpart1d = 0.6;
float fpart2d = 0.2;
float fpart3d = 0.0;

void drawBall(void) {
        glColor3f(0.0, 0.0, 0.0); //set ball colour

        	glTranslatef(-1.7f,-0.8f,0.0f);
        	glutSolidSphere (0.3, 20, 20); //create ball.

        if(rtri < 0.5) {
        	if (rtri > -1.3) fballd -= 0.005;
        	glTranslatef(2.0f,fballd,0.0f); //moving it toward the screen a bit on creation
        }
        else if(rtri < 6.7) {
        	if (rtri > 5.0) fballu += 0.005;
           	glTranslatef(2.0f,fballu,0.0f);
        }
        else
          	glTranslatef(2.0f,0.65f,0.0f);
        glutSolidSphere (0.3, 20, 20); //
        }

void drawBall2(void) {
        glColor3f(0.0, 0.0, 0.0); //set ball colour

        	glTranslatef(-1.7f,-0.8f,0.0f);
        	glutSolidSphere (0.3, 20, 20); //create ball.

        	glTranslatef(2.0f,0.55f,0.0f); //moving it toward the screen a bit on creation
        	glutSolidSphere (0.3, 20, 20); //
        }

void hill() {
    glBegin(GL_POLYGON);
    glColor3f(101.0/255.0, 67.0/255.0, 33.0/255.0);

        glVertex3f(8.3f, 0.0f, 0.0f);
        glVertex3f(-8.3f, 0.0f, 0.0f);
        glVertex3f(-8.3f, 1.0f, 0.0f);

        glVertex3f(-8.1f, 0.5f, 0.0f);
        glVertex3f(-1.0f, 2.5f, 0.0f);
        glVertex3f(4.0f, 1.6f, 0.0f);

        glVertex3f(8.3f, 3.0f, 0.0f);

    glEnd();
}

void truck1() {
	//glRotatef(rtri,1.0f,0.0f,0.0f);        // Rotate The Triangle On The Y axis
	  // draw a triangle (in smooth coloring mode)
	  glBegin(GL_POLYGON);
	  // start drawing a polygon

	  if(rtri < 0.5) {
		  if (rtri > -1.3) {
			  fpart1d -= 0.005;
			  fpart2d -= 0.005;
			  fpart3d -= 0.005;
		  }               // start drawing a polygon
		    glColor3f(0.0f,0.0f,0.0f);            // Set The Color To Red
		    glVertex3f(-2.5f, 0.0f, 0.0f);        // Top left
		    glVertex3f(0.4f, fpart1d, 0.0f);

		    glVertex3f(1.0f, fpart2d, 0.0f);

		    glColor3f(0.0, 1.0, 0.0);            // Set The Color To Green
		    glVertex3f( 1.0f, fpart3d, 0.0f);        // Bottom Right
		    glColor3f(0.0, 1.0, 0.5);            // Set The Color To Blue
		    glVertex3f(-2.5f,-1.0f, 0.0f);// Bottom Left
	  }
	  else if(rtri < 6.7) {
		  glColor3f(0.3f,0.5f,1.0f);            // Set The Color To Red
		  if (rtri > 5.0) {
			  fpart1u += 0.005;
			  fpart2u += 0.005;
			  fpart3u += 0.005;
		  }
			  glColor3f(0.0f,0.0f,0.0f);            // Set The Color To Red
			  glVertex3f(-2.5f, 0.0f, 0.0f);        // Top left
			  glVertex3f(0.4f, fpart1u, 0.0f);

			  glVertex3f(1.0f, fpart2u, 0.0f);

			  glColor3f(0.0, 1.0, 0.0);            // Set The Color To Green
			  glVertex3f( 1.0f, fpart3u, 0.0f);        // Bottom Right
			  glColor3f(0.0, 1.0, 0.5);            // Set The Color To Blue
			  glVertex3f(-2.5f,-1.0f, 0.0f);// Bottom Left
		  }
	  else {
		  glColor3f(0.0f,0.0f,0.0f);            // Set The Color To Red
		  glVertex3f(-2.5f, 0.0f, 0.0f);        // Top left
		  glVertex3f(0.4f, 0.6, 0.0f);

		  glVertex3f(1.0f, 0.2, 0.0f);
		  glColor3f(0.0, 1.0, 0.0);            // Set The Color To Green
	    glVertex3f( 1.0f, 0.0, 0.0f);        // Bottom Right
	    glColor3f(0.0, 1.0, 0.5);           // Set The Color To Blue
	    glVertex3f(-2.5f,-1.0f, 0.0f);// Bottom Left
	  }

	  glEnd();                    // we're done with the polygon (smooth color interpolation)
	  drawBall();

	  rtri+=0.01f;                    // Increase The Rotation Variable For The Triangle
	  if(rtri>13)
	      rtri=-7.0f;

	  if(rtri<0.5)
		  up1+=0.003f;                    // Increase The Rotation Variable For The Triangle
	  else if(rtri<6.7)
		  up1-=0.002f;
	  else if(rtri<11.82)
		  up1+=0.003f;
	  else {
	      up1=8.6f;
	      fballu = -0.3f;
	      fpart1u = -0.2;
	      fpart2u = -0.6;
	      fpart3u = -0.8;
	      fballd = 0.55f;
	      fpart1d = 0.6;
	      fpart2d = 0.2;
	      fpart3d = 0.0;
	  }

	  rquad-=10.0f;                    // Decrease The Rotation Variable For The Quad

}

void truck2() {
	//glRotatef(rtri,1.0f,0.0f,0.0f);        // Rotate The Triangle On The Y axis
	  // draw a triangle (in smooth coloring mode)
	  glBegin(GL_POLYGON);
	  // start drawing a polygon
               // start drawing a polygon
		    glColor3f(0.0f,0.0f,0.0f);            // Set The Color To Red
		    glVertex3f(-2.5f, 0.0f, 0.0f);        // Top left
		    glVertex3f(0.4f, 0.6f, 0.0f);

		    glVertex3f(1.0f, 0.2f, 0.0f);

		    glColor3f(238.0/255.0f,145.0/255.0f,41.0/255.0f);            // Set The Color To Green
		    glVertex3f( 1.0f, 0.0f, 0.0f);        // Bottom Right
		    glColor3f(242.0/255.0, 242.0/255.0, 15.0/255.0);            // Set The Color To Blue
		    glVertex3f(-2.5f,-1.0f, 0.0f);// Bottom Left

	  glEnd();                    // we're done with the polygon (smooth color interpolation)
	  drawBall2();
}


/* The main drawing function. */
void terrain_display()
{
  glClearColor(115/255.0, 194/255.0, 251/255.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        // Clear The Screen And The Depth Buffer
  glLoadIdentity();                // Reset The View

  glTranslatef(0.0,0.0f,-15.0f);
  	hill();

  glTranslatef(0.0,-6.3f,0.0f);
  	hill();

  glTranslatef(rtri,up1,-5.0f); // Move Left 1.5 Units And Into The Screen 6.0
  	truck1();

 if (rtri < -3.0)
  	glTranslatef(0.0,-8.1f,0.0f);        // Move Left 1.5 Units And Into The Screen 6.0
 else {
	if (goupx == 0)
		jitterx += 0.01;
	else
		jitterx -= 0.01	;

	if (jitterx > 4.0f) goupx = 1;
	else if (jitterx < 2.0f) goupx = 0;

	if (goupy == 0)
		jittery += 0.004;
	else
		jittery -= 0.004;

	if (jittery > 0.8f) goupy = 1;
	else if (jittery < 0.0f) goupy = 0;

	if(rtri < 0.5)
		glTranslatef(-rtri-jitterx,-up1-fballd+2.65-jittery,0.0f);
	else if(rtri < 6.7)
		glTranslatef(-rtri-jitterx,-up1-fballu+2.65-jittery,0.0f);
	else
		glTranslatef(-rtri-jitterx,-up1-0.65+2.65-jittery,0.0f);
 	 }
  truck2();

  // swap the buffers to display, since double buffering is used.
  glutSwapBuffers();
}

/* The function called whenever a key is pressed. */
void keyPressedTerrain(unsigned char key, int x, int y)
{
    if(key == (unsigned char)'b')
    	menuMain();
}

int terrainMain()
{
  //glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

  /* get a 640 x 480 window */
  //glutInitWindowSize(640, 480);

  /* the window starts at the upper left corner of the screen */
  //glutInitWindowPosition(0, 0);

  /* Open a window */
  //window = glutCreateWindow("Moving Car");

  glutKeyboardFunc(keyPressedTerrain);

  /* Register the function to do all our OpenGL drawing. */
  glutDisplayFunc(&terrain_display);

  /* Go fullscreen.  This is as soon as possible. */
  glutFullScreen();

  /* Even if there are no events, redraw our gl scene. */
  glutIdleFunc(&terrain_display);

  /* Register the function called when our window is resized. */
  glutReshapeFunc(&ReSizeGLScene);

  /* Initialize our window. */
  InitGL(640, 480);

  /* Start Event Processing Engine */
  glutMainLoop();

  return 1;
}
