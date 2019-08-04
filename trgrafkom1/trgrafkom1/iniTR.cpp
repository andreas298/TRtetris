#include <Windows.h>
#include <iostream>
#include <GL\glew.h>
#include <GL\glut.h>
#include <math.h>
#include <Box2D\Box2D.h>

int x=0,y=0,z=0;
int w=640, h=480;
const int ESCKEY = 27;

void drawQuad() {
	glLineWidth(4.0);
	glBegin(GL_LINE_LOOP);
      glColor3f(0,0,1);
            glVertex2f(-10.,-10.);
            glVertex2f(10.,-10.);
            glVertex2f(10.,10.);  
            glVertex2f(-10.,10.);
      glEnd();
}



void mouse(int button, int state, int xmouse, int ymouse){
      if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
          
            x = xmouse-(w/2);
            y = (h/2)-ymouse;
            printf("   x = %d    y = %d",x,y);
      }
}

void mykeyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
   case ESCKEY:  // ESC: Quit
      exit(0);
      break;
   }
}

void renderScene(void){
      glClear(GL_COLOR_BUFFER_BIT);
      glClearColor(1,1,1,1);
      glPushMatrix();
      glTranslatef(x,y,z);
      drawQuad();
      glPopMatrix();
      glFlush();
}

void timer(int value){
      glutPostRedisplay();
      glutTimerFunc(50,timer,0);
}

void main (int argc, char **argv){
      glutInit(&argc, argv);
      glutInitWindowPosition(100,100);
      glutInitWindowSize(w,h);
      glutCreateWindow("TR");
      gluOrtho2D(-w/2,w/2,-h/2,h/2);
      glutDisplayFunc(renderScene);
      glutKeyboardFunc(mykeyboard);
      glutMouseFunc(mouse);
      glutTimerFunc(1,timer,0);
      glutMainLoop();
}