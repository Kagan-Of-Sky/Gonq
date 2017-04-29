/* PROGRAM:  Text.c 
   AUTHOR:   Carolina Ayala
   DATE:     29/Jan/03
   PURPOSE:  A simple library to display text 
				 using glutBitmapCharater
*/

/**************************************************************************/
/* Include necessary header files
 **************************************************************************/
#include "text.h"	

/**************************************************************************/
/* Include necessary header files
 **************************************************************************/
GLint base = 0;


/**************************************************************************/
/* Function to create NUMCHARACTERS list, each of them with a character 
 **************************************************************************/
void CreateCharacters( void *font ) {
int i;
base = glGenLists( NUMCHARACTERS );

for ( i = 0; i < NUMCHARACTERS; i++ ) {
	glNewList( base + i, GL_COMPILE );
		glutBitmapCharacter( font, i );
	glEndList( );
}

}
/**************************************************************************/
/* Function to draw the text text
 **************************************************************************/
void Legend( int x, int y, char *text ) {

	glRasterPos2f( x, y );
        glListBase( base );
        glCallLists( (GLint) strlen( text ), GL_BYTE, text );

}

