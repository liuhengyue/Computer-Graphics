#include <windows.h>
#include <gl/gl.h>
#include <stdlib.h>


#define BASE_RADIUS 1.0
#define BASE_HEIGHT 1.5
#define LOWER_ARM_WIDTH  0.5
#define LOWER_ARM_HEIGHT 3.5
#define UPPER_ARM_WIDTH  0.3
#define UPPER_ARM_HEIGHT 2.0

GLfloat theta[3] = {0.0, 0.0, 0.0};
GLboolean bas = GL_FALSE;
GLboolean low = GL_FALSE;
GLboolean up = GL_FALSE;
GLint u_direction = 1;
GLint l_direction = 1;

GLUquadricObj *p;   // pointer to quadric object

void base()
{
   glPushMatrix();

   glScalef(2.5,1.0,2.5);
   glutWireSphere(BASE_RADIUS,7,15);
   glPopMatrix();
}

void lower_arm()
{
  glPushMatrix();
  glTranslatef(-0.5*LOWER_ARM_HEIGHT, 0.0, 0.0);
  glRotatef (-90.0, 0.0, 0.0, 1.0);
  glScalef(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, LOWER_ARM_WIDTH);
  glutWireCube(1.0);
  glPopMatrix();
}

void upper_arm()
{
  glPushMatrix();
  glTranslatef(-0.5*UPPER_ARM_HEIGHT,0.0 , 0.0);
  glRotatef (-90.0, 0.0, 0.0, 1.0);
  glScalef(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_WIDTH*4);
  glutWireCube(1.0);
  glPopMatrix();
}

void display()
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  glRotatef(theta[0], 0.0, 1.0, 0.0);
  glColor3f (0.0, 0.0, 1.0);
  base();

  glTranslatef(0.0, BASE_HEIGHT, 0.0);
  glRotatef(theta[1], 0.0, 0.0, 1.0);
  glColor3f (0.0, 1.0, 0.0);
  lower_arm();

  glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);
  glRotatef(theta[2], 0.0, 0.0, 1.0);
  glColor3f (1.0, 0.0, 0.0);
  upper_arm();

  glutSwapBuffers();
}


void init()
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  p = gluNewQuadric();
}

void reshape(int w, int h)
{
  glViewport (0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-7.0, 7.0, -7.0, 7.0, -10.0, 10.0);
}

void mykey(unsigned char key, int x, int y)
{
	if(key == 'b' | key == 'B')
		bas = !bas;
	if(key == 'u' | key == 'U')
		up = !up;
	if(key == 'l' | key == 'L')
		low = !low;
}


void idle()
{
  if (bas) {
    theta[0] += 0.02;
    if (theta[0] > 360) theta[0] -= 360;
  }
  if (low) {
    if (l_direction > 0) {
       theta[1] += 0.02;
       if (theta[1] > 70) {
          l_direction = -1;
          theta[1] -= 0.02;
       }
    }
    else {
       theta[1] -= 0.02;
       if (theta[1] < -70) {
          l_direction = 1;
          theta[1] += 0.02;
       }
    }
  }
  if (up) {
    if (u_direction > 0) {
       theta[2] += 0.02;
       if (theta[2] > 70) {
          u_direction = -1;
          theta[2] -= 0.02;
       }
    }
    else {
       theta[2] -= 0.02;
       if (theta[2] < -70) {
          u_direction = 1;
          theta[2] += 0.02;
       }
    }
  }
  glutPostRedisplay();
}


int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutCreateWindow("robot animated");
  glutKeyboardFunc(mykey);
  glutIdleFunc(idle);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glEnable(GL_DEPTH_TEST); /* Enable hidden-surface removal */
  init();
  glutMainLoop();
}
