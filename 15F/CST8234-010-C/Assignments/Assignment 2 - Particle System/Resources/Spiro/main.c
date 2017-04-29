/* PROGRAM:  spirograph.c 
   AUTHOR:   Carolina Ayala 
   DATE:     20/08/07 
   PURPOSE:  F07_Lab01 Solution 
   NOTES:   
             
*/

#include "main.h"

/**************************************************************************/
/* main
 ***************************************************************************/
int main( int argc, char *argv[] ) {
  	glutInit( &argc, argv );
  	glutInitDisplayMode( GLUT_DOUBLE );
	glutInitWindowSize( 800, 600 );
  	glutCreateWindow( TITLE );
  	glutDisplayFunc( Draw );
  	glutReshapeFunc( Reshape );
  	glutKeyboardFunc(keyPressed);
	Init();
   	glutMainLoop();
   	return( 0 );  		/* NOTE: this is here only for ANSI requirements */
}

/**************************************************************************/
/* Init( )
 * Plants the seed for number generation
 * Love big resolutions, but I want smooth lines
 **************************************************************************/
void Init( ) {
        srand( time (NULL ) );
        CreateCharacters( GLUT_BITMAP_8_BY_13);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glPointSize( 4 );
	//glClearColor( 1.0, 1.0, 1.0, 1.0 );
}

/**************************************************************************/
/* Reshape Function
 * Call in case that the window gets resize
 * I want to keep the size of my new window, so I can set my viewport later on
 * Keep my world from -10 to 10 all the time  -- always square
 ***************************************************************************/
void Reshape(int w, int h) {
        winWidth = w;
        winHeight = h;
        glViewport( 0, 0, winWidth, winHeight );
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho( -100.0, 100.0,  -100.0, 100.0,  -100.0, 100.0 );
        glMatrixMode(GL_MODELVIEW);
}


/**************************************************************************/
/* SpiroView
 * Settings to display my ellipse in the left side of the window
 * Use from the bottom left corner of the window
 *     to 75% of the width and 100% lenght
 ***************************************************************************/
void SpiroView( ) {
        glViewport( 0, 0, 0.75*winWidth, winHeight );
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho( -1.0, 1.0,  -1.0, 1.0,  -1.0, 1.0 );
        glMatrixMode(GL_MODELVIEW);
}

/**************************************************************************/
/* ControlView
 * Settings to display the control panel in the right side of the window
 * Use from the (80%, 0) of the widht of the window
 *     to 25% of the width and 100% lenght
 ***************************************************************************/
void ControlView( void ) {
        glViewport( 0.75*winWidth, 0, 0.25*winWidth, winHeight );
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho( 0.0, 40.0, 0.0, 60, 0.0, 40.0  );
        glMatrixMode(GL_MODELVIEW);
}

/**************************************************************************/
/* Draw( )
 * The OpenGL function that know how to draw
 * When OpenGL recieves an event to draw, it calls this function to do the
 * work.
 **************************************************************************/
void Draw( void ) {

	float j;

   	glClear( GL_COLOR_BUFFER_BIT );

	SpiroView();

	 /*
          * Show circle and points
          */
        if ( SHOW ) {
                CoordSystem();
 		Circle( A, 0.0, 0.0 );
        	Circle( B, A+B, 0.0 );
		glBegin( GL_LINE_STRIP );
			glVertex3f( 0.0, 0.0, 0.0 );
                	glVertex3f( A+B+H, 0.0, 0.0 );
		glEnd();
		glPointSize( 5.0 );
        	glBegin( GL_POINTS );
                	glVertex3f( A+B+H, 0.0, 0.0 );
        	glEnd();


        }

	if ( SPIRO )
		Spirograph( A, B, H, RES );
	

	if ( MANY ) {
        	for (j = 0; j < 1.0; j += 1.0 / 10) 
			Spirograph( A , B, H + j/10, RES );
	}	
	
	/*
	 * Draws the control panel 
	 */
	Controls();
   	glutSwapBuffers();

   	return;
}

/**************************************************************************/
/* A function that handles the keyboard callback
 *  **************************************************************************/
void keyPressed(unsigned char key, int x, int y) {
        switch ( key ) {
                case 'A':
			A += 0.01;
                        break;
                case 'a':
			A -= 0.01;
                        break;
                case 'B':
                        B = ( abs(A + B) > 0.6 ? B : B + 0.01 );
                        break;
                case 'b':
                        B -= 0.01 ;
                        break;
		case 'H':
			H += 0.01;
			break;
		case 'h':
			H -= 0.01;
			break;
                case 'I':
                        ITER++;
                        break;
                case 'i':
                        ITER = ( ITER <= 1? 1: ITER-1 );
                        break;
		case 'R':
			RES++;
			break;
		case 'r':
                        RES = ( RES <= 1? 1: RES-1 );
			break;
                case 'D':
                        SHOW = ( SHOW ? OFF : ON );
                        break;
		case 'S':
                        SPIRO = ( SPIRO ? OFF : ON );
			if ( ! SPIRO ) MANY = OFF; 
			break;
		case 'C':
                        RANDOM = ( RANDOM  ? OFF : ON );
			break;
		case 'M':
                        MANY = ( MANY ? OFF : ON );
			if ( MANY && ! SPIRO ) MANY = OFF;
			break;
                case 'q':
                case 'Q':
                        exit( 0 );
                        break;
                default:
                        return;
        }
        glutPostRedisplay();
}
