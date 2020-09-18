/*-------------------------------
ALEXIS MCBEAIN
ASSIGNMENT 3 - LORENZ ATTRACTOR
CSCI 4229



Lorenz Information given by: https://www.prinmath.com/csci5229/misc/lorenz.c
I also used the examples given from class as guides.

--------------------------------*/






#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif



double s = 10;
double b = 2.6666;
double r = 28;

//lorenz points 
double points[50000][3];

//view angles x & y
double th = 0;
double ph = 0;

double dt = 0.001;


#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}


void draw(void){
	double x = 1;
	double y = 1;
	double z = 1; 
	
	for(int i=0; i<50000; i++){
		
		double dx = s*(y-x);
		double dy = x*(r-z)-y;
		double dz = x*y - b*z;
		
		x += dt*dx;
		y += dt*dy;
		z += dt*dz;
		
		points[i][0] = x*0.02;
		points[i][1] = y*0.02;
		points[i][2] = z*0.02;
		
	} 
}

void key(unsigned char c, int x, int y){
	//esc = exit
	if (c == 27){
	exit(0);
	}
	
	//modifications of some lorenz points
	
	else if (c == 's'){
		s -= 1;
	}
	else if (c == 'w'){
		s += 1;
	}
	else if (c == 'a'){
		b -= 1;
	}
	else if(c == 'd'){
		b+= 1;
	}
	else if (c == 'q'){
		r-=1;
	}
	else if(c == 'e'){
		r+=1;
	}
	 //reset 
	else if(c == 32){
		s = 10;
		b = 2.666;
		r = 28;
		th = 0;
		ph = 0;
	}
	
	glutPostRedisplay();
}

 

//ARROW KEYS 
void movement(int key, int x, int y){
	if (key == GLUT_KEY_RIGHT){
		ph +=5.0;
	}
	else if (key == GLUT_KEY_LEFT){
		ph -=5.0;
	}
	else if (key == GLUT_KEY_UP){
		th += 5.0;
	}
	else if(key == GLUT_KEY_DOWN){
		th -=5.0;
	}
	
	glutPostRedisplay();
}
 
 
 void reshape(int width,int height)
{
   const double dim=2.5;
   
   //  Ratio of the width to the height of the window
   double w2h = (height>0) ? (double)width/height : 1;
   glViewport(0,0, width,height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-w2h*dim,+w2h*dim, -dim,+dim, -dim,+dim);
   glMatrixMode(GL_MODELVIEW);
   
   //  Undo previous transformations
   glLoadIdentity();
}
 
 
void display(){
	draw();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	//rotations (angle, x, y, z)
	glRotated(th,1,0,0);
	glRotated(ph,0,1,0);
	
	glBegin(GL_LINE_STRIP); //LINE_STRIP is more connected to vertices's vs LINES
		for(int i=0; i<50000; i++){
			glColor3f(0.5f, 0.5f, 1.5f);  //purple lines
			glVertex3dv(points[i]);		//getting points to plot from array
			
		}
	glEnd();
	
	//axis 
	glColor3f(1,1,1);
	glBegin(GL_LINES);
		glVertex3d(0,0,0);
		glVertex3d(1,0,0);
		glVertex3d(0,0,0);
		glVertex3d(0,1,0);
		glVertex3d(0,0,0);
		glVertex3d(0,0,1);
	glEnd();
	
	//axis label
	 glRasterPos3d(1 ,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,1,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,1);
      Print("Z");
	
	//angle text
	glWindowPos2i(5,5);
	Print("View Angle=%d,%d",th,ph);
	
	
	glFlush();
	glutSwapBuffers();
	
	
}




int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE |GLUT_DEPTH);
	
	glutInitWindowSize(800,800);
	glutCreateWindow("Alexis McBeain - Lorenz Attractor");
	glutDisplayFunc(display);
	glutSpecialFunc(movement);
	glutKeyboardFunc(key);
	glutReshapeFunc(reshape);
	glClearColor(0,0,0,1);
	glViewport(0,0,1000,1000);
	

	
	glutMainLoop();
	
	return 0;
	
	
	
	
}
