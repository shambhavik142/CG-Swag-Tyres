
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include "./end.h"

float swxe = -450.0;

void print_string(/*void* font,*/ char* s)
{

      while (*s) {
         glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *s);
         s++;
      }

}

void my_reshapeE(int w, int h)
{
   GLdouble size;
   GLdouble aspect;

   /* Use the whole window. */
   glViewport(0, 0, w, h);

   /* We are going to do some 2-D orthographic drawing. */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   size = (GLdouble)((w >= h) ? w : h) / 2.0;
   if (w <= h) {
      aspect = (GLdouble)h/(GLdouble)w;
      glOrtho(-size, size, -size*aspect, size*aspect, -100000.0, 100000.0);
   }
   else {
      aspect = (GLdouble)w/(GLdouble)h;
      glOrtho(-size*aspect, size*aspect, -size, size, -100000.0, 100000.0);
   }

   /* Make the world and window coordinates coincide so that 1.0 in */
   /* model space equals one pixel in window space.                 */
   glScaled(aspect, aspect, 1.0);

   /* Now determine where to draw things. */
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

}

void squareE(double x1, double y1, double sidelength, int colorGray)
{
    double halfside = sidelength / 2;

    if(colorGray == 1)
    	glColor3d(0.25, 0.25, 0.25);
    else
    	glColor3d(115/255.0, 194/255.0, 251/255.0);
    glBegin(GL_POLYGON);

    glVertex2d(x1 + halfside, y1 + halfside);
    glVertex2d(x1 + halfside, y1 - halfside);
    glVertex2d(x1 - halfside, y1 - halfside);
    glVertex2d(x1 - halfside, y1 + halfside);

    glEnd();
}

void circleE(float x1, float y1, double radius, int color)
{
	float x2,y2;
	float angle;

	if(color == 0)
		glColor3f(0.0,0.0,0.0);
	else
		glColor3f(1.0,1.0,1.0);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1,y1);

	for (angle=1.0f;angle<361.0f;angle+=0.2)
	{
	    x2 = x1+sin(angle)*radius;
	    y2 = y1+cos(angle)*radius;
	    glVertex2f(x2,y2);
	}

	glEnd();
}

void draw_text(char* str, double xt, double yt)
{
	char* bitmap_font_names[7] = {str};

   GLfloat x, y, ystep, yild, stroke_scale;

   /* Draw the strings, according to the current mode and font. */
   glTranslatef(xt,yt,0);
   glColor4f(1.0, 1.0, 224/255.0, 0.0);
   x = -225.0;
   y = 70.0;
   ystep  = 100.0;
   yild   = 20.0;
      glRasterPos2f(-150, y+1.25*yild);
     print_string(bitmap_font_names[0]);
}

/* The function called whenever a key is pressed. */
void keyPressedEnd(unsigned char key, int x, int y)
{
    if(key == (unsigned char)'b')
    	menuMain();
}

void end_display(void)
{

   glClearColor(112/255.0, 128/255.0, 144/255.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();                // Reset The View

   draw_text("Ramesh has now switched to Swag Tyres!", -20.0, 70.0);
   draw_text("You should too!", 90.0, -25.0);

      //if(glutGet(GLUT_ELAPSED_TIME) % 30 == 0) {
   	   swxe += 1;
   		if(swxe >= 300.0)
   			swxe = -450.0;
      //}

      circleE(swxe,-55,120,0);
      circleE(swxe,-55,65,1);

   draw_text("Swag Tyres!", 20.0, -300.0);
   draw_text("Bring a little swag to the road!", -60.0, -35.0);

   glutSwapBuffers();
}

void endMain()
{
	//glutInitWindowSize(500, 500);
	//glutCreateWindow("Swag Tyres");
	glutFullScreen();
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutDisplayFunc(end_display);
	glutIdleFunc(end_display);
	glutKeyboardFunc(keyPressedEnd);
	glutReshapeFunc(my_reshapeE);
	glutMainLoop();
}
