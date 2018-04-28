#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<GL/glut.h>
#include<time.h>
#include<math.h>

static GLfloat up=-0.2;
static GLfloat pos=-0.2;
int shoot=0,bang=0;
int counter1=0,counter2=0,count=0;
int game,instruct;
char tmp_str[40];
void displost();

void init(void)
{
	glClearColor (1.0,1.0,1.0,0.0);
	glMatrixMode (GL_PROJECTION);
}

void drawhit(const char * message, int x, int y)
{
	glPushMatrix();
	glScalef(0.3,0.2,0.15);
	glTranslatef(x,y,0);
	while (*message)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*message++);
	}
	glPopMatrix();
}	

void myHit()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,300,0,300);
	glClearColor(1.0,0.0,0.0,1.0);
	glColor3f(0.0,0.0,0.0);
	glLineWidth(8.0);
	
	drawhit("You Won!!",120,800);
}

void draw_instruct(const char *message, int x, int y)
{
	int j;
	
	glPushMatrix();
	glScalef(0.1,0.1,0.0);
	glTranslatef(x,y,0);
	while (*message)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*message++);
	}
	glPopMatrix();
}

void instructions()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,200,0,200);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(0.2,0.2,0.2);
	glLineWidth(8.0);
	draw_instruct("How To Play",500,1800); 
	glLineWidth(4.0);
	draw_instruct("_________",450,1780); 
	draw_instruct("Hit 3 Balls in 10 Shoots",200,1500);
	draw_instruct("Press Spacebar to shoot",200,1200);
	draw_instruct("Press Q to quit",750,100);
	glFlush();
}

void Write(char *string)
{
	glScalef(0.02,0.02,0.0);
	while(*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
}

void display()
{
	int i;
	if(counter1==3)
	{
		myHit();
		glFlush();
	}
	else
	{
		int j;
		for(j=0;j<100000000;j++);
		
		glClearColor(0.2,1.0,0.4,1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glColor3f(0, 0, 1);
		glRasterPos2f(-0.9, 0.9);
		sprintf(tmp_str, "Arrow count: %d", count);
		Write(tmp_str);
		glPopMatrix();

		if(count>10)
			glutDisplayFunc(displost);
		glPushMatrix();
		glColor3f(0, 0, 1);
		glRasterPos2f(-0.2, 0.9);
		sprintf(tmp_str, "Score: %d", counter1);
		
		Write(tmp_str);
		
		glPopMatrix();
		glPushMatrix();
		glColor3f(1.0,0.2,0.0);
		glLoadIdentity();
		glTranslatef(0.8,-0.869+up,0.0);
		glutSolidSphere(0.10,20,16);

		if(shoot==1)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(-0.8+pos,0.0,0.0);
			glColor3f(0.0,0.0,0.0);
			glLineWidth(5.0);
			glBegin(GL_LINES);
			glVertex3f(-0.2,0.0,0.0);
			glVertex3f(0.1,0.0,0.0);
			glVertex3f(0.1,0.0,0.0);
			glVertex3f(0.03,0.05,0.0);
			glVertex3f(0.1,0.0,0.0);
			glVertex3f(0.03,-0.05,0.0);	
			glVertex3f(-0.2,0.0,0.0);
			glVertex3f(0.03-0.3,0.05,0.0);
			glVertex3f(-0.2,0.0,0.0);
			glVertex3f(0.03-0.3,-0.05,0.0);
			glVertex3f(-0.16,0.0,0.0);
			glVertex3f(0.03-0.26,0.05,0.0);
			glVertex3f(-0.16,0.0,0.0);
			glVertex3f(0.03-0.26,-0.05,0.0);
			glEnd();
			glPopMatrix();
		}
		if(bang==1)
		{
			bang=0;pos=-0.2;
			glPushMatrix();
			glLoadIdentity();
			up=0;
			glColor3f(1.0,0.2,0.0);
			glutSolidSphere(1,20,16);
			glPopMatrix();
		}
		glPopMatrix();
		for( i=0;i<200;i+=20)
		{
			if(pos>=1.90 && up>0.920 && up<1.080)
			//collision detection
			{
				counter1++;
				shoot=0;
				pos=-0.2;
				bang=1;
			}
			if(counter1==3)
				count=0;
			int value=rand()*rand()%20;
			up=(up+value/1500.0+0.005);

			if(up>2)
				up=0;
			
			if(shoot==1)
			{
				pos=pos+0.015;
				if(pos>2)
				{
					pos=-0.2;
					shoot=0;
				}
			}
			glutPostRedisplay();
		}
	glFlush();
	}	
}

void displost()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,300,0,300);
	glClearColor(1.0,1.0,0.0,1.0);
	glColor3f(1.0,0.0,0.80);
	glLineWidth (8.0);
	drawhit("Sorry,",90,850);
	drawhit("Try Again!!",90,650);
	glFlush();
}

void indisplay()
{
	glClearColor(0.8,0.8,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	instructions();
	glFlush();
}

void keyboard(unsigned char key,int x,int y)
{
	if (key==' ')
	{
		shoot=1;
		count++;
	}
	if (key=='q' || key=='Q')
	{
		exit(0);
	}
}


int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1500,1500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Instructions");
	init();
	glutDisplayFunc(indisplay);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Game");
	init();
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
