
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include "./terrain.h"
#include "./durability.h"
#include "./roadGrip.h"
#include "./end.h"

float upwx = -245.0;
float upwy = -85.0;
float swx = -50.0;
float rswx = 200.0;

int ac;
char** av;

void print_bitmap_string(/*void* font,*/ char* s)
{

      while (*s) {
         glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *s);
         s++;
      }

}

void my_reshape(int w, int h)
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

void square(double x1, double y1, double sidelength, int colorGray)
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

void circle(float x1, float y1, double radius, int color)
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

void draw_stuff(char* str, double xt, double yt, float r, float g, float b)
{
	char* bitmap_font_names[7] = {str};

   GLfloat x, y, ystep, yild, stroke_scale;

   /* Draw the strings, according to the current mode and font. */
   glTranslatef(xt,yt,0);
   glColor4f(r, g, b, 0.0);
   x = -225.0;
   y = 70.0;
   ystep  = 100.0;
   yild   = 20.0;
      glRasterPos2f(-150, y+1.25*yild);
     print_bitmap_string(bitmap_font_names[0]);
}

/* The function called whenever a key is pressed. */
void keyPressedMenu(unsigned char key, int x, int y)
{
    if(key == (unsigned char)'t')
    	terrainMain();
    else if(key == (unsigned char)'d')
        durabilityMain();
    else if(key == (unsigned char)'r')
        roadGripMain();
    else if(key == (unsigned char)'e')
        endMain();
}

void main_display(void)
{

   glClearColor(112/255.0, 128/255.0, 144/255.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();                // Reset The View

   draw_stuff("Ramesh uses X tires!", 35.0, 0.0, 255.0 / 255.0f, 127.0 / 255.0f, 80.0 / 255.0f);
   draw_stuff("Suresh uses Swag Tires!", -20.0, -25.0, 0.0f, 1.0f, 0.5);
   draw_stuff("Let us see how they lead their lives!", -35.0, -27.0, 1.0, 1.0, 224/255.0);

   square(-200.0, -80.0, 150.0, 0);

   //hill
   glBegin(GL_POLYGON);
   glColor3f(101.0/255.0, 67.0/255.0, 33.0/255.0);

       glVertex2d(-123, -155);
       glVertex2d(-275, -155);
       glVertex2d(-275, -130);
       glVertex2d(-123, -70);

   glEnd();

   //if(glutGet(GLUT_ELAPSED_TIME) % 5 == 0) {
	   upwx += 0.5f;
	   upwy += 0.2f;
		if(upwx >= -150.0) {
			upwx = -245.0;
			upwy = -85.0;
		}
   //}

   circle(upwx,upwy,30,0);
   circle(upwx,upwy,15,1);

   square(0.0, -80.0, 150.0, 0);

   //road
      glBegin(GL_POLYGON);
      glColor3f(0.2, 0.2, 0.2);

          glVertex2d(75, -155);
          glVertex2d(-75, -155);
          glVertex2d(-75, -110);
          glVertex2d(75, -110);

      glEnd();

      //if(glutGet(GLUT_ELAPSED_TIME) % 30 == 0) {
   	   swx += 0.5;
   		if(swx >= 50.0)
   			swx = -50.0;
      //}

      circle(swx,-85,30,0);
      circle(swx,-85,15,1);

   square(200.0, -80.0, 150.0, 1);

   //rain
   	   glBegin(GL_POLYGON);
        glColor3f(0.5, 0.5, 1.0);
             glVertex2d(275, -115);
             glVertex2d(125, -115);
             glVertex2d(125, -110);
             glVertex2d(275, -110);
         glEnd();

         glBegin(GL_POLYGON);
         glColor3f(0, 0, 0);

             glVertex2d(275, -155);
             glVertex2d(125, -155);
             glVertex2d(125, -115);
             glVertex2d(275, -115);

         glEnd();

         //if(glutGet(GLUT_ELAPSED_TIME) % 30 == 0) {
      	   rswx += 0.5;
      		if(rswx >= 250.0)
      			rswx = 155.0;
         //}

         circle(rswx,-85,30,0);
         circle(rswx,-85,15,1);

         glColor3f(0.5, 0.5, 1.0);
         glBegin(GL_LINES);
         if(glutGet(GLUT_ELAPSED_TIME) % 3 == 0) {
         	  for (int i=0; i<130; i=i+10) {
         		  int x = 130 + (rand() % 130);
         		  glVertex2d(x, -130+i);
         		  glVertex2d(x, -150+i);
         	  }
         }
         glEnd();

   draw_stuff("Press T", -80.0, -275.0, 1.0, 1.0, 224/255.0);
   draw_stuff("Press D", 200.0, 0.0, 1.0, 1.0, 224/255.0);
   draw_stuff("Press R", 200.0, 0.0, 1.0, 1.0, 224/255.0);

   draw_stuff("Terrain Adaption", -440.0, -23.0, 1.0, 1.0, 224/255.0);
   draw_stuff("Durability", 235.0, 0.0, 1.0, 1.0, 224/255.0);
   draw_stuff("Road Grip", 195.0, 0.0, 1.0, 1.0, 224/255.0);

   glutSwapBuffers();
}

void menuMain()
{
	glutInitWindowSize(500, 500);
	glutCreateWindow("Swag Tyres");
	glutFullScreen();
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutDisplayFunc(main_display);
	glutIdleFunc(main_display);
	glutKeyboardFunc(keyPressedMenu);
	glutReshapeFunc(my_reshape);
	glutMainLoop();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   menuMain();
   return 0;
}
