#include <GL/glut.h>
#include "Nbody.h"
#include "keyhandler.h"
#include "Draw.h"
#include<iostream>

int main( int argc, char *argv[] )  {
	// Inicializar GLUT.
	glutInit( &argc, argv );
	// Definir Color RGB y Single Buffer.
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	// Definir la ventana en pixeles de la pantalla .
	glutInitWindowSize( 1280, 720 );
	// Definir la posicion de la ventana en pixeles de la pantalla.
	glutInitWindowPosition( 100, 150 );
	// Crear la ventana.
	glutCreateWindow( "N-Bodies" );
	// Definir la funcion de callback que usaremos para dibujar algo.
	glutDisplayFunc( myDisplay );
	// Inicializar algunas cosas.
	myInit( );
	//glutReshapeFunc(reshape);
	glutReshapeFunc(handleResize);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	//glutKeyboardFunc(Key_Released);
	glutTimerFunc(25, update, 0); //Add a timer
	// Ahora que tenemos todo definido, el loop  que responde  a eventos.
	glutMainLoop( );
}

/* ----------------------------------------------------------------------- */

