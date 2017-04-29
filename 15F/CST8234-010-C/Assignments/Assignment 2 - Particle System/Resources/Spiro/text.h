/* PROGRAM:  Text.h 
   AUTHOR:   Carolina Ayala
   DATE:     29/Jan/03
   PURPOSE:  A simple library to display text 
				 using glutBitmapCharater
*/

/**************************************************************************/
/* Include necessary header files
 **************************************************************************/
#include <GL/glut.h>     
#include <GL/gl.h>
#include <GL/glu.h>	
#include <string.h>

/**************************************************************************/
/* Declare needed defines
 **************************************************************************/
#define  FONT  GLUT_BITMAP_8_BY_13
#define NUMCHARACTERS 256

/**************************************************************************/
/* Declare function prototypes
 **************************************************************************/
void CreateCharacters( void *font );
void Legend( int, int, char * );

