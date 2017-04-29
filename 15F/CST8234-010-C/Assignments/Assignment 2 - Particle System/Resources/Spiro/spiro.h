/**************************************************************************/
/* Declare include files
 **************************************************************************/
#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "text.h"

/**************************************************************************/
/* Some defines to use in the program
 **************************************************************************/
#define NUM_RANDOM( min, max ) ( min + (int)( (double)max * rand() / ( RAND_MAX + 1.0 ) ) )
#define MAX_POINTS      72 
#define DISPLAY_TEXT    "Display       [D]"
#define SPIRO_TEXT	"Spiro         [S]"
#define RANDOM_TEXT     "Random Color  [C]"
#define MANY_TEXT	"Many Spiros   [M]"
#define ON              1
#define OFF             0
#define ON_COLOR	0.0, 1.0, 0.0
#define OFF_COLOR	0.0, 0.3, 0.0
#define SPIRO_COLOR     0.0, 0.0, 1.0

/**************************************************************************/
/* Global variables for my window
 **************************************************************************/
extern int SHOW;
extern int SPIRO;
extern int RANDOM;
extern int MANY;
extern float A;
extern float B;
extern float H;
extern int   RES;
extern int   ITER;

/**************************************************************************/
/* Function Prototypes
 **************************************************************************/
void Spirograph( float, float, float, float );  /* Draws a spiro */
void Circle( float, float, float);
void Controls( void );
void CoordSystem( void );
void ControlView( void );


