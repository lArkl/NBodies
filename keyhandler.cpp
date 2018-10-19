#include<GL/glut.h>
#include<iostream>
#include "keyhandler.h"
float xx=0,yy=0;
float view_rotx=20.0, view_roty=30.0, view_rotz=0.0;

const float stepT = 2.0;
const float stepR = 2.0;

void keyboard(unsigned char key, int x, int y){
	//std::cout<<key<<std::endl;
	switch (key){
    case 'h':
		std::cout<<"help\nc - switch culling\nq/escape - Salir\n1/2 - rotar"<<std::endl;
        break;
	case 'c':
		if (glIsEnabled(GL_CULL_FACE))
			glDisable(GL_CULL_FACE);
		else glEnable(GL_CULL_FACE);
        break;
	case 'a':
		xx-= stepT;
        break;
	case 'd':
		xx += stepT;
		break;
	case 'w':
		yy += stepT;
		break;
	case 's':
		yy -= stepT;
		break;
    case 'q':
	    exit(0);
        break;
    case 27:
		exit(0);
        break;
    default: std::cout<<key;
    }
   	glutPostRedisplay();
}


void special(int key, int x, int y){
	switch(key){
	case GLUT_KEY_UP: view_rotx += stepR; break;
	case GLUT_KEY_DOWN: view_rotx -= stepR; break;
	case GLUT_KEY_LEFT: view_roty += stepR; break;
	case GLUT_KEY_RIGHT: view_roty -= stepR;break;
    }
	glutPostRedisplay();
}
