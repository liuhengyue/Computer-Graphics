/**
The program is based on OpenGL in windows7
The main task is to draw an  uang according to Lab 8 requirement
Author@ Liu Hengyue
BUPT Number 10212779
*/
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define radian 3.14159/180 
//The next part 'define' defines the datailed data of a uang
//Big horn(The horn has six parts)
#define UPPER_HORN1_RADIUS1 0.5//the big horn of the uang is modeled in the combination of cylinders,this is the parameters of upper part
#define UPPER_HORN1_RADIUS2 0.3
#define UPPER_HORN1_HEIGHT 2.5
#define LOWER_HORN1_RADIUS1 0.3//lower part of the horn
#define LOWER_HORN1_RADIUS2 0.2
#define LOWER_HORN1_HEIGHT 2.0
#define BRANCH_HORN1_RADIUS1 0.2//a horn has a branch to grow two sides of spines
#define BRANCH_HORN1_RADIUS2 0.15
#define BRANCH_HORN1_HEIGHT 1.5
#define ACE_HORN1_RADIUS 0.15//a horn has two spines with model cone
#define ACE_HORN1_HEIGHT 0.7

//Little horn
#define HORN2_RADIUS1 0.35//the main part of the little horn
#define HORN2_RADIUS2 0.2
#define HORN2_HEIGHT 1.0
#define ACE_HORN2_RADIUS 0.2//the spine of the horn
#define ACE_HORN2_HEIGHT 0.6
//Head
#define HEAD_RADIUS 1.8//the head is modeled as sphere
#define HEAD_X 1.2//x y z are to modify the shape of the sphere head
#define HEAD_Y 1.2
#define HEAD_Z 1.4
//eyes
#define EYE_RADIUS 0.1
//mouth
#define UPPER_MOUTH_RADIUS1 0.1
#define UPPER_MOUTH_RADIUS2 0.06
#define UPPER_MOUTH_HEIGHT 0.5
#define LOWER_MOUTH_RADIUS1 0.06
#define LOWER_MOUTH_RADIUS2 0.02
#define LOWER_MOUTH_HEIGHT 0.2
//flag(2 cylinders,beside the mouth)
#define UPPER_FLAG_RADIUS1 0.1
#define UPPER_FLAG_RADIUS2 0.05
#define UPPER_FLAG_HEIGHT 1.0
#define LOWER_FLAG_RADIUS1 0.05
#define LOWER_FLAG_RADIUS2 0.02
#define LOWER_FLAG_HEIGHT 0.7
//Torso
#define TORSO_RADIUS 1.0//the torso model is sphere
#define TORSO_X 2.8//x y z are to modify the shape of the sphere torso
#define TORSO_Y 2.2
#define TORSO_Z 4.0
//Propes
#define UPPER_PROPES_RADIUS1 0.25//the upper propes model is Cylinder
#define UPPER_PROPES_RADIUS2 0.15
#define UPPER_PROPES_HEIGHT 2.5
#define LOWER_PROPES_RADIUS1 0.15//the lower propes model is Cylinder
#define LOWER_PROPES_RADIUS2 0.1
#define LOWER_PROPES_HEIGHT 2.2
#define LOWESS_PROPES_RADIUS 0.1//the lowess propes model is Cone
#define LOWESS_PROPES_HEIGHT 1.5
#define TIP_PROPES_RADIUS 0.05//the little spine on lowess propes,with model Cone
#define TIP_PROPES_HEIGHT 0.5
//leg

#define UPPER_LEG_RADIUS1 0.32//the upper leg model is Cylinder
#define UPPER_LEG_RADIUS2 0.2
#define UPPER_LEG_HEIGHT 2.52
#define LOWER_LEG_RADIUS1 0.2//the lower leg model is Cylinder
#define LOWER_LEG_RADIUS2 0.12
#define LOWER_LEG_HEIGHT 2.5
#define LOWESS_LEG_RADIUS 0.12//the lowess leg model is Cone
#define LOWESS_LEG_HEIGHT 1.72
#define TIP_LEG_RADIUS 0.052//the little spine on lowess leg,with model Cone
#define TIP_LEG_HEIGHT 0.52
#define LEFT 1
#define RIGHT -1
#define UP 1
#define DOWN -1
#define FRONT 0//for determing the position of the lowess propes or legs
#define BACK 1
GLUquadricObj *p;   // poGLfloater to quadric object

GLfloat value_sin;//to record the value y of location(x,y) of one certain body part
GLfloat value_cos;//to record the value x of location(x,y) of one certain body part
GLboolean move = GL_FALSE;
//theta[0] is for rotating all objects;theta[1] is for rotaing the head;theta[2] is for flag;theta[3] is for mouthparts;theta[4] is for upper propes;theta[5] is for lower and theta[6] is for lowess propes;theta[7],theta[8],theta[9] are for legs.
GLfloat theta[]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}; //theta[10] is for changing the position of a light source
int dir[]={1,1,1,1,1,1,1,1,1}; //for determing the direction of head moving(when i=1,the head move down or right; i=-1, move up or left)
//big horn1 and little horn2
   //define the material properties 
    float no_mat[] = {0.0, 0.0, 0.0, 1.0};
    float blue[] = {0.1, 0.5, 0.8, 1.0}; //dark blue
	float blue2[] = {0.1, 0.2, 1.0, 1.0}; //dark blue2
	float brown[] = {0.1, 0.05, 0.05, 1.0}; //dark brown
	float black[] = {0.05, 0.05, 0.05, 1.0};//dark black 
	float yellow[] = {1.0, 1.0, 0.1, 1.0};//yellow
	float red[] = {1.0, 0.1, 0.1, 1.0};//red
	float grey[] = {0.3, 0.3, 0.3, 1.0}; //dark grey
	float current1[] = {0.0, 0.0, 0.0, 1.0};//the current color of ace_horn1, branch_horn1,horn2 
	float current2[] = {0.0, 0.0, 0.0, 1.0};//the current color of head
	float current3[] = {0.0, 0.0, 0.0, 1.0};//the current color of torso
	float current4[] = {0.0, 0.0, 0.0, 1.0};//the current color of upper and lower propes/legs
	float current5[] = {0.0, 0.0, 0.0, 1.0};//the current color of feet
	float current6[] = {0.0, 0.0, 0.0, 1.0};//the current color of upper and lower horn1
    int mode=3;//determine the current model is goldbug/devil/normal(default is normal)

    float mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    float no_shininess = 0.0;
    float low_shininess = 10.0;
	float middle_shininess = 50.0;
    float high_shininess = 100.0;
    float mat_emission[] = {0.3, 0.2, 0.2, 0.0};
int menu,submenu1,submenu2,submenu3;//used for menu and submenu
/*used for change the light or its position*/
GLboolean changeposition =GL_FALSE; //change the light source position related to the uang or not
GLboolean white =GL_FALSE;//change the light color
GLboolean colored =GL_FALSE;
GLboolean light =GL_TRUE;//change the light source
GLfloat x=0.0; //the position of the moving light source
GLfloat z=15.0;
GLfloat rgb[]={1.0,1.0,1.0};//the color of the light source

void ace_horn1()//scaleR and scaleH define the radius and height parameters of a cone
{
  glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, brown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, current1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glRotatef (-75.0, 1.0, 0.0, 0.0);
  glutSolidCone(ACE_HORN1_RADIUS,ACE_HORN1_HEIGHT,50,50);
  glPopMatrix();
}

void branch_horn1(GLfloat side)
{ 
		glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, brown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, current1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glRotatef (side*15.0, 0.0, 0.0, 1.0);
  glRotatef (side*90.0, 0.0, 1.0, 0.0);
  gluCylinder (p, BRANCH_HORN1_RADIUS1, BRANCH_HORN1_RADIUS2,BRANCH_HORN1_HEIGHT, 15, 15);
  glPopMatrix();
}

void lower_horn1()
{
	glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, brown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, current1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  
  glRotatef(-30.0,1.0,0.0,0.0);
  gluCylinder (p, LOWER_HORN1_RADIUS1, LOWER_HORN1_RADIUS2,LOWER_HORN1_HEIGHT, 15, 15);
  glPopMatrix();
}
void upper_horn1()
{
	glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, brown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, current1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  
  glRotatef(-15.0,1.0,0.0,0.0);
  gluCylinder (p,UPPER_HORN1_RADIUS1,UPPER_HORN1_RADIUS2,UPPER_HORN1_HEIGHT, 15, 15);
  glPopMatrix();
}

void ace_horn2(GLfloat scaleR,GLfloat scaleH)//scaleR and scaleH define the radius and height parameters of a cone
{
  glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, brown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, current1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glRotatef (-12.0, 1.0, 0.0, 0.0);
  glutSolidCone(scaleR,scaleH,50,50);
  glPopMatrix();
}
void horn2()
{
  glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, brown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, current1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glRotatef(-30.0,1.0,0.0,0.0);
  gluCylinder (p, HORN2_RADIUS1, HORN2_RADIUS2,HORN2_HEIGHT, 15, 15);
  glPopMatrix();
}
//Head part
void head()
{
    glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, grey);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, current2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glTranslatef(0.0,0.0,HEAD_RADIUS/2);
    glRotatef (-1.5, 1.0, 0.0, 0.0);
    glRotatef (180.0, 0.0, 0.0, 1.0);
    glRotatef (90.0, 0.0, 1.0, 0.0);
    glScalef(HEAD_X,HEAD_Y,HEAD_Z);
    glutSolidSphere(HEAD_RADIUS,5,100);
    glPopMatrix();

}
//Eye part(SolidSphere)
void eye()
{
  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, black);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glTranslatef(0.0,0.0,EYE_RADIUS/2);
  glutSolidSphere(EYE_RADIUS,5,100);
  glPopMatrix();
}
//Mouthpart
void upper_mouth(GLfloat side)
{
  glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,brown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, current6);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glRotatef (-side*30.0, 0.0, 1.0, 0.0);
  gluCylinder (p,UPPER_MOUTH_RADIUS1,UPPER_MOUTH_RADIUS2,UPPER_MOUTH_HEIGHT,15,15);
  glPopMatrix();
}
void lower_mouth(GLfloat side)
{
  glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,brown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, current6);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glRotatef (side*10.0, 0.0, 1.0, 0.0);
  gluCylinder (p,LOWER_MOUTH_RADIUS1,LOWER_MOUTH_RADIUS2,LOWER_MOUTH_HEIGHT,15,15);
  glPopMatrix();
}
//flags
void upper_flag(GLfloat side)
{
  glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,brown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, current6);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glRotatef (-side*30.0, 0.0, 1.0, 0.0);
  gluCylinder (p,UPPER_FLAG_RADIUS1,UPPER_FLAG_RADIUS2,UPPER_FLAG_HEIGHT,15,15);
  glPopMatrix();
}
void lower_flag(GLfloat side)
{
  glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, brown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, current6);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  glRotatef (side*10.0, 0.0, 1.0, 0.0);
  gluCylinder (p,LOWER_FLAG_RADIUS1,LOWER_FLAG_RADIUS2,LOWER_FLAG_HEIGHT,15,15);
  glPopMatrix();
}
//Torso part
void torso()
{   
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, current3);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glTranslatef(TORSO_RADIUS,0.0,0.0);
    glScalef(TORSO_X,TORSO_Y,TORSO_Z);
    glutSolidSphere(TORSO_RADIUS,6,250);
    glPopMatrix();

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, black);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, current3);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glTranslatef(-TORSO_RADIUS,0.0,0.0);
    glScalef(TORSO_X,TORSO_Y,TORSO_Z);
    glutSolidSphere(TORSO_RADIUS,6,250);
    glPopMatrix();

}
//LEG part
//scaleR1,2 and scaleH define the radius and height parameters of a cylinder;lo and la define the subdivisions;dir determines the direction of a leg part;a determines the angle of a leg part
void leg(GLfloat dir,GLfloat a,GLfloat side,GLfloat scaleR1,GLfloat scaleR2,GLfloat scaleH,GLfloat lo,GLfloat la)
                                                                                                  
{ glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT, black);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, current4);
  glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
  glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  
  glRotatef (side*dir*a, 0.0, 0.0, 1.0);
  glRotatef (side*90.0, 0.0, 1.0, 0.0);
  gluCylinder (p,scaleR1,scaleR2,scaleH,lo,la);
  glPopMatrix();
  value_cos=cos(a*radian);//for calculating the coordinates of ce
  value_sin=sin(a*radian);
}
//scaleR1,2 and scaleH1,2 define the radiuses and heights parameters of cones(feet and tips);side determines the side of the cones;lo and la define the subdivisions
void leg_foot(GLfloat dir,GLfloat side,GLfloat scaleR1,GLfloat scaleH1,GLfloat scaleR2,GLfloat scaleH2,GLfloat lo,GLfloat la)
{ 
	glPushMatrix();      
    glMaterialfv(GL_FRONT, GL_AMBIENT,brown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, current5);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
  
  glRotatef(dir*180.0, 0.0, 1.0, 0.0);
  glutSolidCone(scaleR1,scaleH1,lo,la);
  glTranslatef(0.0,0.0,scaleH1/2);
  glPushMatrix();
  glRotatef(side*90,0.0,1.0,0.0);
  glutSolidCone(scaleR2,scaleH2,lo,la);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0.0,0.0,scaleH1/3);
  glRotatef(side*90,0.0,1.0,0.0);
  glutSolidCone(scaleR2,scaleH2,lo,la);
  glPopMatrix();
  glPopMatrix();
}

void initlight()
{

  
  //light properties
    float ambient[] = {0.8f, 0.8f, 0.8f, 1.0f};
    float diffuse[] = {rgb[0], rgb[1],rgb[2], 1.0f};
    float specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float position[] = {x, 0, z, 1.0f};//light0 positon
    float model_ambient[] = {0.2, 0.2, 0.2, 1.0};//global ambient light
    int model_two_side = 1; //0=2sided, 1=1sided
    int viewpoint = 0;      //0=infiniteViewpoint, 1=localViewpoint

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    

    //light model properties
    
    
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, viewpoint);
    //Only outside face because we don't see the inside of the spheres
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
   glLightfv(GL_LIGHT0, GL_POSITION, position);
   glEnable(GL_LIGHTING);
   if(light) {
	   glEnable(GL_LIGHT0); } 
   else
	   glDisable(GL_LIGHT0); 
}
	void init()
{
p = gluNewQuadric();

}
void reshape(int w, int h)
{
  glViewport (0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-15.0, 15.0, -10.0, 10.0, -15.0, 15.0);
}
void display()//the selection of states translating/bending/rotating
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.8, 0.3, 0.8, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0);
  model(mode);//defaut mode=3,normal uang color model
  initlight();
  
  glRotatef(theta[0], 0.0, 1.0, 0.0);
  
  
  //Torso is divided into two parts
  glPushMatrix();//make sure the coordinate not be influenced by other parts of the uang
  torso();
  glPopMatrix();
  
  glPushMatrix();
  glRotatef (theta[1], 1.0, 0.0, 0.0);
  //draw the head
  glPushMatrix();
  glTranslatef(0.0,0.0, TORSO_RADIUS*TORSO_Z);//Locate the head
  head();
  glPopMatrix();
  //draw the big horn
  glPushMatrix();
  glTranslatef(0.0,-HEAD_RADIUS/6, HEAD_RADIUS*HEAD_Z+TORSO_RADIUS*TORSO_Z);
  upper_horn1();
  glTranslatef(0.0,UPPER_HORN1_HEIGHT*sin(15*radian) ,UPPER_HORN1_HEIGHT*cos(15*radian));
  lower_horn1();
  glTranslatef(0.0,LOWER_HORN1_HEIGHT*sin(30*radian) ,LOWER_HORN1_HEIGHT*cos(30*radian));
  branch_horn1(LEFT);
  branch_horn1(RIGHT);
  glPushMatrix();
  glTranslatef(BRANCH_HORN1_HEIGHT*cos(15*radian),BRANCH_HORN1_HEIGHT*sin(15*radian) ,0.0);
  ace_horn1();
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-BRANCH_HORN1_HEIGHT*cos(15*radian),BRANCH_HORN1_HEIGHT*sin(15*radian) ,0.0);
  ace_horn1();
  glPopMatrix();
  glPopMatrix();

  //draw the little horn
  glPushMatrix();
  glTranslatef(0.0,sqrt(5*HEAD_RADIUS*HEAD_RADIUS*HEAD_Y*HEAD_Y/9) , HEAD_RADIUS+TORSO_RADIUS*TORSO_Z);
  horn2();
  glTranslatef(0.0,HORN2_HEIGHT/2 , HORN2_HEIGHT*sqrt(3)/2);
  ace_horn2(ACE_HORN2_RADIUS,ACE_HORN2_HEIGHT);
  glPopMatrix();



  //draw the eyes
  glPushMatrix();
  glTranslatef(HEAD_RADIUS/3,-HEAD_RADIUS/1.5, TORSO_RADIUS*TORSO_Z+HEAD_RADIUS*1.1);
  eye();
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-HEAD_RADIUS/3,-HEAD_RADIUS/1.5, TORSO_RADIUS*TORSO_Z+HEAD_RADIUS*1.1);
  eye();
  glPopMatrix();
  
  //draw the  mouthparts
  glPushMatrix();
  glRotatef(theta[2],0.0,1.0,0.0);
  glPushMatrix();
  glTranslatef(HEAD_RADIUS/4,-HEAD_RADIUS, TORSO_RADIUS*TORSO_Z+HEAD_RADIUS*0.8);//Locate the upper mouth flag
  upper_mouth(RIGHT);
  glTranslatef(UPPER_MOUTH_HEIGHT*sin(30*radian),0.0, UPPER_MOUTH_HEIGHT*cos(30*radian));//Locate the lower mouth flag
  lower_mouth(RIGHT);
  glPopMatrix();
  glPopMatrix();

  glPushMatrix();
  glRotatef(-theta[2],0.0,1.0,0.0);
  glPushMatrix();
  glTranslatef(-HEAD_RADIUS/4,-HEAD_RADIUS, TORSO_RADIUS*TORSO_Z+HEAD_RADIUS*0.8);
  upper_mouth(LEFT);
  glTranslatef(-UPPER_MOUTH_HEIGHT*sin(30*radian),0.0, UPPER_MOUTH_HEIGHT*cos(30*radian));
  lower_mouth(LEFT);
  glPopMatrix();
  glPopMatrix();
  
  //draw the two flags
  glPushMatrix();
  glRotatef(theta[3],0.0,1.0,1.0);
  glPushMatrix();
  glTranslatef(HEAD_RADIUS*sin(30*radian),-HEAD_RADIUS/1.5, TORSO_RADIUS*TORSO_Z+HEAD_RADIUS);//Locate the upper mouth flag
  upper_flag(RIGHT);
  glTranslatef(UPPER_FLAG_HEIGHT*sin(30*radian),0.0, UPPER_FLAG_HEIGHT*cos(30*radian));//Locate the lower mouth flag
  lower_flag(RIGHT);
  glPopMatrix();
  glPopMatrix();

  glPushMatrix();
  glRotatef(-theta[3],0.0,1.0,1.0);
  glPushMatrix();
  glTranslatef(-HEAD_RADIUS*sin(30*radian),-HEAD_RADIUS/1.5, TORSO_RADIUS*TORSO_Z+HEAD_RADIUS);
  upper_flag(LEFT);
  glTranslatef(-UPPER_FLAG_HEIGHT*sin(30*radian),0.0, UPPER_FLAG_HEIGHT*cos(30*radian));
  lower_flag(LEFT);
  glPopMatrix();
  glPopMatrix();

  glPopMatrix();//head motion including the parts on it
  
  //right side propes and legs
  glPushMatrix();

  glTranslatef(-(HEAD_RADIUS*HEAD_X-HEAD_RADIUS*HEAD_X/6),-HEAD_RADIUS*HEAD_Y/2,
                TORSO_RADIUS*TORSO_Z+HEAD_RADIUS/2);//Locate the first right propes
  
  glRotatef(theta[4],1.0,0.0,1.0);
  leg(UP,45,RIGHT,UPPER_PROPES_RADIUS1,UPPER_PROPES_RADIUS2,UPPER_PROPES_HEIGHT,15,15);//upper part

  glTranslatef(-UPPER_PROPES_HEIGHT*value_cos,UPPER_PROPES_HEIGHT*value_sin,0.0);
  
  glRotatef(theta[5],0.0,1.0,1.0);
  leg(DOWN,30,RIGHT,LOWER_PROPES_RADIUS1,LOWER_PROPES_RADIUS2,LOWER_PROPES_HEIGHT,15,15);//lower part

  glTranslatef(-LOWER_PROPES_HEIGHT*value_cos,-LOWER_PROPES_HEIGHT*value_sin,0.0);
  glRotatef(theta[6],0.0,1.0,0.0);
  leg_foot(FRONT,RIGHT,LOWESS_PROPES_RADIUS,LOWESS_PROPES_HEIGHT,TIP_PROPES_RADIUS,TIP_PROPES_HEIGHT,25,25);//lowess part(foot)

  glPopMatrix();

  glPushMatrix();
  glTranslatef(-sqrt(TORSO_RADIUS*(TORSO_X+1)*TORSO_RADIUS*(TORSO_X+1)-(TORSO_RADIUS*TORSO_Z/2)*(TORSO_RADIUS*TORSO_Z/2))+TORSO_RADIUS*TORSO_Y/3,-TORSO_RADIUS*TORSO_Y/2,-TORSO_RADIUS*TORSO_Z/2);//Locate the second right propes
  glRotatef(-theta[7]/2,1.0,0.0,1.0);
  leg(UP,45,RIGHT,UPPER_LEG_RADIUS1,UPPER_LEG_RADIUS2,UPPER_LEG_HEIGHT,15,15);
  glTranslatef(-UPPER_LEG_HEIGHT*value_cos,UPPER_LEG_HEIGHT*value_sin,0.0);
  glRotatef(-theta[8],0.0,1.0,1.0);
  leg(DOWN,30,RIGHT,LOWER_LEG_RADIUS1,LOWER_LEG_RADIUS2,LOWER_LEG_HEIGHT,15,15);
  glTranslatef(-LOWER_LEG_HEIGHT*value_cos,-LOWER_LEG_HEIGHT*value_sin,0.0);
  glRotatef(-theta[6],0.0,1.0,0.0);
  leg_foot(BACK,LEFT,LOWESS_LEG_RADIUS,LOWESS_LEG_HEIGHT,TIP_LEG_RADIUS,TIP_LEG_HEIGHT,25,25);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-sqrt(TORSO_RADIUS*(TORSO_X+1)*TORSO_RADIUS*(TORSO_X+1)-(TORSO_RADIUS*TORSO_Z/2)*(TORSO_RADIUS*TORSO_Z/2))+TORSO_RADIUS*TORSO_Y/3,-TORSO_RADIUS*TORSO_Y/2,TORSO_RADIUS*TORSO_Z/2);//Locate the third right propes
  glRotatef(-theta[7]*2,1.0,0.0,1.0);
  leg(UP,45,RIGHT,UPPER_LEG_RADIUS1,UPPER_LEG_RADIUS2,UPPER_LEG_HEIGHT,15,15);
  glTranslatef(-UPPER_LEG_HEIGHT*value_cos,UPPER_LEG_HEIGHT*value_sin,0.0);
  glRotatef(-theta[8],0.0,1.0,1.0);
  leg(DOWN,30,RIGHT,LOWER_LEG_RADIUS1,LOWER_LEG_RADIUS2,LOWER_LEG_HEIGHT,15,15);
  glTranslatef(-LOWER_LEG_HEIGHT*value_cos,-LOWER_LEG_HEIGHT*value_sin,0.0);
  glRotatef(-theta[9],0.0,1.0,0.0);
  leg_foot(BACK,LEFT,LOWESS_LEG_RADIUS,LOWESS_LEG_HEIGHT,TIP_LEG_RADIUS,TIP_LEG_HEIGHT,25,25);
  glPopMatrix();

  //left side propes and legs
  glPushMatrix();
  glTranslatef(sqrt(HEAD_RADIUS*HEAD_X*HEAD_RADIUS*HEAD_X-
                     (TORSO_RADIUS*TORSO_Z+HEAD_RADIUS-TORSO_RADIUS*TORSO_Z-HEAD_RADIUS)*(TORSO_RADIUS*TORSO_Z+HEAD_RADIUS-TORSO_RADIUS*TORSO_Z-HEAD_RADIUS))-HEAD_RADIUS*HEAD_X/6,-HEAD_RADIUS*HEAD_Y/2,
                TORSO_RADIUS*TORSO_Z+HEAD_RADIUS/2);//Locate the first right propes
  glRotatef(-theta[4],1.0,0.0,1.0);
  leg(UP,45,LEFT,UPPER_PROPES_RADIUS1,UPPER_PROPES_RADIUS2,UPPER_PROPES_HEIGHT,15,15);
  glTranslatef(UPPER_PROPES_HEIGHT*value_cos,UPPER_PROPES_HEIGHT*value_sin,0.0);
  glRotatef(-theta[5],0.0,1.0,0.5);
  leg(DOWN,30,LEFT,LOWER_PROPES_RADIUS1,LOWER_PROPES_RADIUS2,LOWER_PROPES_HEIGHT,15,15);
  glTranslatef(LOWER_PROPES_HEIGHT*value_cos,-LOWER_PROPES_HEIGHT*value_sin,0.0);
  glRotatef(-theta[6],0.0,1.0,0.0);
  leg_foot(FRONT,LEFT,LOWESS_PROPES_RADIUS,LOWESS_PROPES_HEIGHT,TIP_PROPES_RADIUS,TIP_PROPES_HEIGHT,25,25);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(sqrt(TORSO_RADIUS*(TORSO_X+1)*TORSO_RADIUS*(TORSO_X+1)-(TORSO_RADIUS*TORSO_Z/2)*(TORSO_RADIUS*TORSO_Z/2))-TORSO_RADIUS*TORSO_Y/3,-TORSO_RADIUS*TORSO_Y/2,-TORSO_RADIUS*TORSO_Z/2);//Locate the second right propes
  glRotatef(theta[7]/2,1.0,0.0,1.0);
  leg(UP,45,LEFT,UPPER_LEG_RADIUS1,UPPER_LEG_RADIUS2,UPPER_LEG_HEIGHT,15,15);
  glTranslatef(UPPER_LEG_HEIGHT*value_cos,UPPER_LEG_HEIGHT*value_sin,0.0);
  glRotatef(theta[8],0.0,1.0,1.0);
  leg(DOWN,30,LEFT,LOWER_LEG_RADIUS1,LOWER_LEG_RADIUS2,LOWER_LEG_HEIGHT,15,15);
  glTranslatef(LOWER_LEG_HEIGHT*value_cos,-LOWER_LEG_HEIGHT*value_sin,0.0);
  glRotatef(theta[9],0.0,1.0,0.0);
  leg_foot(BACK,RIGHT,LOWESS_LEG_RADIUS,LOWESS_LEG_HEIGHT,TIP_LEG_RADIUS,TIP_LEG_HEIGHT,25,25);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(sqrt(TORSO_RADIUS*(TORSO_X+1)*TORSO_RADIUS*(TORSO_X+1)-(TORSO_RADIUS*TORSO_Z/2)*(TORSO_RADIUS*TORSO_Z/2))-TORSO_RADIUS*TORSO_Y/3,-TORSO_RADIUS*TORSO_Y/2,TORSO_RADIUS*TORSO_Z/2);//Locate the third right propes
  glRotatef(theta[7]*2,1.0,0.0,1.0);
  leg(UP,45,LEFT,UPPER_LEG_RADIUS1,UPPER_LEG_RADIUS2,UPPER_LEG_HEIGHT,15,15);
  glTranslatef(UPPER_LEG_HEIGHT*value_cos,UPPER_LEG_HEIGHT*value_sin,0.0);
  glRotatef(theta[8]*0.4,0.0,1.0,1.0);
  leg(DOWN,30,LEFT,LOWER_LEG_RADIUS1,LOWER_LEG_RADIUS2,LOWER_LEG_HEIGHT,15,15);
  glTranslatef(LOWER_LEG_HEIGHT*value_cos,-LOWER_LEG_HEIGHT*value_sin,0.0);
  glRotatef(theta[9]*0.4,0.0,1.0,0.0);
  leg_foot(BACK,RIGHT,LOWESS_LEG_RADIUS,LOWESS_LEG_HEIGHT,TIP_LEG_RADIUS,TIP_LEG_HEIGHT,25,25);
  glPopMatrix();
  glutSwapBuffers();
}
void goldbug(){
	int i;
	for(i=0;i<4;i++){
 current1[i] = yellow[i];//the current color of ace_horn1, branch_horn1,horn2 
 current2[i] = yellow[i];//the current color of head
 current3[i] = yellow[i];//the current color of torso
 current4[i] = yellow[i];//the current color of upper and lower propes/legs
 current5[i] = yellow[i];//the current color of feet
 current6[i] = yellow[i];//upper and lower horn1
	}
}
void normal(){
	int i;
	for(i=0;i<4;i++){
 current1[i] = brown[i];//the current color of ace_horn1, branch_horn1,horn2 
 current2[i] = blue2[i];//the current color of head
 current3[i] = blue[i];//the current color of torso
 current4[i] = black[i];//the current color of upper and lower propes/legs
 current5[i] = brown[i];//the current color of feet
 current6[i] = brown[i];
	}
}
void devil(){
	int i;
	for(i=0;i<4;i++){
 current1[i] = red[i];//the current color of ace_horn1, branch_horn1,horn2 
 current2[i] = black[i];//the current color of head
 current3[i] = red[i];//the current color of torso
 current4[i] = black[i];//the current color of upper and lower propes/legs
 current5[i] = red[i];//the current color of feet
 current6[i] = black[i];
	}
}
model(int m){
	if(m==1) goldbug();
	if(m==2) devil();
	if(m==3) normal();
}
void idle()
{	

	
	if(move){
	theta[0]+=0.05;
    if (theta[0] > 360) {theta[0]-= 360;}
    if(changeposition){
		theta[10]+=0.05;
		if (theta[10] > 360) {theta[10]-= 360;}
	x=15*sin(3.14*theta[10]/180); 
	z=15*cos(3.14*theta[10]/180);
	
  }
	theta[1]+=dir[0]*0.005;
	if(theta[1]>=1.5||theta[1]<=-1.5) {dir[0]=-dir[0];}
    theta[2]+=dir[1]*0.006;
	if(theta[2]>=1.5||theta[2]<=-0.5) {dir[1]=-dir[1];}
	theta[3]+=dir[2]*0.006;
	if(theta[3]>=2||theta[3]<=-1) {dir[2]=-dir[2];}
	theta[4]+=dir[3]*0.1;
	if(theta[4]>=45||theta[4]<=-5) {dir[3]=-dir[3];}
	theta[5]-=dir[4]*0.2;
	if(theta[5]>=45||theta[5]<=-20) {dir[4]=-dir[4];}
	theta[6]+=dir[5]*0.15;
	if(theta[6]>=60||theta[6]<=20) {dir[5]=-dir[5];}
	theta[7]+=dir[6]*0.05;
	if(theta[7]>=5||theta[7]<=-20) {dir[6]=-dir[6];}
	theta[8]-=dir[7]*0.1;
	if(theta[8]>=45||theta[8]<=-20) {dir[7]=-dir[7];}
	theta[9]+=dir[8]*0.2;
	if(theta[9]>=20||theta[9]<=-90) {dir[8]=-dir[8];}
	}

  if(white){
	  rgb[0]=rgb[1]=rgb[2]=1.0;
     
  }
  if(colored){
         rgb[0]=1.0;
		 rgb[1]=1.0;
		 rgb[2]=0.0;//yellow
  }
    
    glutPostRedisplay();
}
void mymouse(int btn,int state,int x,int y)
{

    if(btn==GLUT_LEFT_BUTTON&&state==GLUT_DOWN) move=! move;

}


void mymenu(int id)
{
if(id==1)
	changeposition=GL_FALSE; //fixed
if(id==2)
	changeposition=GL_TRUE;//relative
if(id==3)
	light=GL_FALSE;  //ambient
if(id==4)
	light=GL_TRUE; //distant
if(id==5){
	white =!white;
    colored=GL_FALSE;
}
if(id==6){
	colored =!colored;
    white=GL_FALSE;
}
if(id==7) mode=1;
if(id==8) mode=2;
if(id==9) mode=3;
} 


void createmenu(){
  menu=glutCreateMenu(mymenu);
  submenu1=glutCreateMenu(mymenu);
  glutAddMenuEntry("fixed", 1);
  glutAddMenuEntry("relative", 2);
  submenu2=glutCreateMenu(mymenu);
  glutAddMenuEntry("ambient", 3);
  glutAddMenuEntry("distant", 4);
  submenu3=glutCreateMenu(mymenu);
  glutAddMenuEntry("white", 5);
  glutAddMenuEntry("coloured", 6);
  menu=glutCreateMenu(mymenu);
  glutAddSubMenu("light position", submenu1);
  glutAddSubMenu("light type", submenu2);
  glutAddSubMenu("light properties", submenu3);
  glutAddMenuEntry("goldbug", 7);
  glutAddMenuEntry("devil", 8);
  glutAddMenuEntry("normal", 9);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutCreateWindow("lab8");
  glutMouseFunc(mymouse);
  glutIdleFunc(idle);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  createmenu();
  glEnable(GL_DEPTH_TEST); /* Enable hidden-surface removal */
  init();
  
  glutMainLoop();
}
