/**************************************************************************/
/* Init light in OpenGL 
/* If using 3D objeccts and lighting, add into Init( )
 **************************************************************************/
void InitLight( void )	        
{
  GLfloat lightPos0[] = { 20.0, 20.0, 20.0, 1.0 };

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glEnable( GL_COLOR_MATERIAL );
  glEnable( GL_NORMALIZE );
  glLightfv( GL_LIGHT0, GL_POSITION, lightPos0 );

}


/**************************************************************************/
/* Add to the keyboard function
/* to see some lighting features 
 **************************************************************************/
void keyboard(unsigned char key, int x, int y)
{
   
    if (key == 'L') {
      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);
    }
    if (key == 'l') {
      glDisable(GL_LIGHTING);
      glDisable(GL_LIGHT0);
    }
    if (key == 'C') glEnable( GL_COLOR_MATERIAL );
    if (key == 'c') glDisable( GL_COLOR_MATERIAL );

    if ( key == 'S' ) glShadeModel( GL_SMOOTH );
    if ( key == 's' ) glShadeModel( GL_FLAT );
   

    glutPostRedisplay();   
}
