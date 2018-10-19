#include <GL/glut.h>
#include <iostream>
#include <omp.h>
#include "Nbody.h"
#include "keyhandler.h"
#include <math.h>


using namespace std;

const float dt = 0.001;
NBody galaxy(dt,N);
//NBody galaxy(dt); //Testeo
size_t start;
const int MAX = 1/dt;
int timeStep = 0;

const float axisIntensity = 0.8;
const float axisSize = 3.0;
		
void myInit( void )  {
	int nthreads = 2;
//	omp_set_num_threads(nthreads);
//	start = omp_get_wtime();
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f( 0.0, 0.0, 0.0 );
	gluOrtho2D( 0.0, 640.0, 0.0, 480.0 );
}

void plotBodies(NBody galaxy){
	glPointSize(5.0);
    
	glPushMatrix();
		glColor3f(0.8, 0.8, 0.6);
		glBegin(GL_POINTS);
			//#pragma omp parallel for
			for(int i=0; i < galaxy.bodyNum; ++i){
				float *pos = galaxy.bodies[i].pos;
				float posZ = 0;
				if(axis == 3) posZ = pos[2];
				glVertex3f( pos[0], pos[1], posZ);
			}
		glEnd();
	glPopMatrix();
}

void plotAxis(){
	glLineWidth(3.0);
	glPushMatrix();
		glBegin(GL_LINES);
			glColor3f(axisIntensity, 0.0, 0.0);
			glVertex3f(0.0,0.0,0.0);
			glVertex3f(axisSize,0.0,0.0);
			
			glColor3f(0.0, axisIntensity, 0.0);
			glVertex3f(0.0,0.0,0.0);
			glVertex3f(0.0, axisSize, 0.0);
			
			glColor3f(0.0, 0.0, axisIntensity);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, axisSize);	
		glEnd();
	glPopMatrix();
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//This function gets called everytime the window needs to
void myDisplay( void)  {

	glClear(GL_COLOR_BUFFER_BIT);
	
	glPushMatrix();
		
	    glTranslatef(xx,yy,-80.0f);//-20.0f);
		glRotatef(view_rotx, 1.0, 0.0, 0.0);
		glRotatef(view_roty, 0.0, 1.0, 0.0);
		glRotatef(view_rotz, 0.0, 0.0, 1.0);

		plotAxis();
		plotBodies(galaxy);

	glPopMatrix();
	glutSwapBuffers();
}

void update(int value) {
	
	//#pragma omp parallel firstprivate(dt) shared(galaxy)
	//cout<<timeStep++<<endl;
	galaxy.force();
	//cout<<omp_get_wtime()-start<<endl;
	glutPostRedisplay();
	glutTimerFunc(20, update, 0);
}