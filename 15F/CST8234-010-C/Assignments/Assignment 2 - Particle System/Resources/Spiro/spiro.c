/**************************************************************************/
/* Declare include files
 **************************************************************************/
#include "spiro.h"

/**************************************************************************/
/* A function which draws a circle
 **************************************************************************/
void Spirograph( float inr, float outr, float offset, float res ) {

   	float angle,
         	radius = inr + outr,
         	inc = (2* M_PI)/res;
	float red, green, blue;

	
	glColor3f( SPIRO_COLOR);

   	glBegin( GL_LINE_STRIP );
   		for ( angle = 0.0; angle <= ITER* (2*M_PI); angle += inc ) {
			if ( RANDOM ) {
				red   = NUM_RANDOM( 1, 100 );
                		green = NUM_RANDOM( 1, 100 );
                		blue  = NUM_RANDOM( 1, 100 );
                		glColor3f( red/100, green/100, blue/100 );
			}
        		glVertex3f( (radius)*cos( angle ) - offset*cos( ( radius * angle ) / outr ),
                                  (radius)*sin( angle ) - offset*sin( ( radius * angle ) / outr ),
                                   0.0 );

   		}

   	glEnd( );

   return;
}

/**************************************************************************/
/* A function which draws a circle
 * with radius r centre in ( a, b )
 * with MAX_POINTS points
 **************************************************************************/
void Circle( float r, float a, float b) {
	float angle;
	float inc = ( 2 * M_PI ) / MAX_POINTS;
	
	glBegin( GL_LINE_LOOP );
		for (angle = 0.0; angle <= 2*M_PI ; angle +=inc) {
			glVertex3f( r*cos(angle) + a, r*sin(angle) + b, 0.0 );
		}
	glEnd( ); 
}
/**************************************************************************/
/* Controls
 * Draw the control panel
 * with the information for the user
 **************************************************************************/
void Controls( void ) {
        static char aRadius[55];
        static char bRadius[55];
        static char hOffset[55];
        static char iTerati[55];
        static char rEsolut[55];

        sprintf( aRadius, "A Radius   [Aa] = %3f", A);
        sprintf( bRadius, "B Radius   [Bb] = %3f", B);
        sprintf( hOffset, "H Offset   [Hh] = %3f", H);
        sprintf( iTerati, "I Iter     [Ii] = %3d", ITER);
        sprintf( rEsolut, "R Res      [Rr] = %3d", RES);

        ControlView();

        glColor4f( 0.2, 0.2, 0.2, 0.5 );
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE );

        glBegin( GL_QUADS );
                glVertex3f( 0.0, 0.0, 0.0 );
                glVertex3f( 40.0, 0.0, 0.0 );
                glVertex3f( 40.0, 60.0, 0.0 );
                glVertex3f( 0.0, 60.0, 0.0 );
        glEnd();
        glDisable( GL_BLEND);

        glColor3f( 0.0, 1.0, 0.0 );
        Legend( 5, 58, " SpiroGraph");
        glBegin( GL_LINES);
                glColor3f( 0.0, 0.0, 1.0 );
                glVertex3f( 2, 57, 0 );
                glColor3f( 1.0, 0.0, 0.0 );
                glVertex3f( 38, 57, 0 );
        glEnd();

        glColor3f( ON_COLOR );
	Legend( 3, 55, aRadius);
        Legend( 3, 53, bRadius );
        Legend( 3, 51, hOffset );
        Legend( 3, 49, iTerati );
        Legend( 3, 47, rEsolut );

        if ( SPIRO )  
		glColor3f( ON_COLOR );
	else 
		glColor3f( OFF_COLOR );
	Legend( 3, 40, SPIRO_TEXT );
        if ( SHOW )  
		glColor3f( ON_COLOR );
	else 
		glColor3f( OFF_COLOR );
	Legend( 3, 38, DISPLAY_TEXT );
        if ( RANDOM )  
		glColor3f( ON_COLOR );
	else 
		glColor3f( OFF_COLOR );
        Legend( 3, 36, RANDOM_TEXT );
        if ( MANY )  
		glColor3f( ON_COLOR );
	else 
		glColor3f( OFF_COLOR );
        Legend( 3, 34, MANY_TEXT );
}

/**************************************************************************/
/* 2D Coordinate System
 **************************************************************************/
void CoordSystem( void ) {
        glColor3f( 0.35, 0.35, 0.35);
        glBegin( GL_LINES );
                glVertex3f( -100.0,   0.0, 0.0 );
                glVertex3f(  100.0,   0.0, 0.0 );
                glVertex3f(    0.0, 100.0, 0.0 );
                glVertex3f(    0.0,-100.0, 0.0 );
        glEnd();
}
