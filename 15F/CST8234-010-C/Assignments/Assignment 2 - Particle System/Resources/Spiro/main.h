/**************************************************************************/
/* Declare include files
 **************************************************************************/
#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "text.h"

/**************************************************************************/
/* Some defines to use in the program
 **************************************************************************/
#define NUM_RANDOM( min, max ) ( min + (int)( (double)max * rand() / ( RAND_MAX + 1.0 ) ) )
#define RADIUS		50
#define MAX_RADIUS      2.0 
#define MAX_POINTS      72 
#define ON              1
#define OFF             0
#define TITLE 		"SpiroGraph :: C. Ayala"

/**************************************************************************/
/* Global variables for my window
 **************************************************************************/
int winWidth;
int winHeight;
int SHOW        = ON;
int SPIRO       = ON;
int RANDOM      = OFF;
int MANY	= OFF;
float A 	= 0.25;
float B 	= 0.12;
float H 	= 0.25;
int   RES 	= 72;
int   ITER 	= 25;


/**************************************************************************/
/* Function Prototypes
 **************************************************************************/
void Circle( float, float, float);
void Controls( void );
void ControlView( void );
void CoordSystem( void );
void Draw( void );
void keyPressed(unsigned char , int , int );
void Reshape(int , int );
void SpiroView( void );
void Init( void );
void Spirograph( float, float, float, float );  /* Draws a spiro */

