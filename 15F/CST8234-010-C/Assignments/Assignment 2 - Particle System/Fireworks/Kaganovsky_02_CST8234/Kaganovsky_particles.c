/*****************************************************************************
 FILE       :  particles.c
 PROGRAM    :  Particle System
 AUTHOR     :  Carolina Ayala, Mark Kaganovsky
 DUE DATE   :  
 COURSE     :  CST8234, Carolina Ayala
 PURPOSE    :  
 CHALLENGES :  
 DIFFICULTY :  
 OBJECTIVES :  
*****************************************************************************/

/***********************************************
 Include linux library headers.
 ***********************************************/
#include <unistd.h> 
#include <time.h>

/***********************************************
 Include OpenGL library headers.
 ***********************************************/
#include <GL/glut.h>

/***********************************************
 Include C library headers.
 ***********************************************/
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>  

/***********************************************
 Include private library headers.
***********************************************/
#include "Kaganovsky_particles.h"
#include "Kaganovsky_particle.h"

/***********************************************
 * Global variables -- problem with glut
 ***********************************************/
int window;
struct particle* particles = NULL;



/*****************************************************************************
  FUNCTION :  main
  PURPOSE  :  create the window and particle list, start the glut main loop
  INPUT    :  command line arguments 
  OUTPUT   :  returns 0 (but not really since glutMainLoop doesn't return)
  NOTES    :  
 ******************************************************************************/
int main(int argc, char **argv){
	/* Print out the controls. */
	puts("Welcome to the fireworks particle system!");
	puts("Try resizing the window to get more fireworks on the screen at once! :)");
	puts("ps: if the controls dont work after resizing the screen, then make sure to move the mouse outside the window and then back inside, this seems to be a problem with openGL or Ubuntu.");
	putchar('\n');
	putchar('\n');
	puts("Controls:");
	putchar('\n');
	puts("  Mouse:");
	puts("    Left click:    Explode a SMALL cluster of particles.");
	puts("    Right click:   Explode a LARGE cluster of particles.");
	puts("    Middle click:  Quit application.");
	putchar('\n');
	puts("  Keyboard:");
	puts("    Spacebar:      Spawn a single firework.");
	puts("    q or Q:        Quit the application.");
	puts("    d:             Delete all particles (particles are deleted automatically when their lifespan runs out).");
	puts("    l:             Disable lighting.");
	puts("    L:             Enable lighting.");
	puts("    s:             Disable material coloring.");
	puts("    S:             Enable material coloring.");
	puts("    c:             Flat shader mode.");
	puts("    C:             Smooth shader mode.");
	
	/* Create the window & basic initialiation
	 * The window starts in position ( DFLT_INIT_POS, DFLT_INIT_POS ) 
	 * The screen starts in ( 0, 0 ) in the upper left corner
	 * The window size is DFLT_INIT_WINDOW_W x  DFLT_INIT_WINDOW_H in pixels
	 * The window title is WINDOW_TITLE 
	 */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize(DFLT_INIT_WINDOW_W, DFLT_INIT_WINDOW_H);
	glutInitWindowPosition(DFLT_INIT_POS, DFLT_INIT_POS);  
	window = glutCreateWindow(WINDOW_TITLE);
	
	/* Basic OpenGL functions 
	 * Register for the glutMainLoop
	 */
	glutDisplayFunc( RenderParticles );
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	
	/* Initialization of OpenGL + Particles */
	Init();
	
	/* Register function to be called when exit */
	atexit(exit_func);
	
	/* Timer function to redraw depending of your frames per seconds */
	glutTimerFunc(MS, animate, 0);
	
	/* Main loop for opengl, never returns. */
	glutMainLoop();
	
	/* MainLoop never returns to this main
	 * Here to be ansi
	 */
	return OK;
}




/*****************************************************************************
 FUNCTION :  init
 PURPOSE  :  Basic initialization of OpenGL - done once
             Create the particles at the beginning
 INPUT    :  void
 OUTPUT   :  void
 NOTES    :  Enable 3D, color blending
 *****************************************************************************/
void Init( void ) {
	int i;
	
	srand(time(NULL));
	
	glClearColor(DFLT_BKG, DFLT_BKG, DFLT_BKG, DFLT_BKG);
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	glClearDepth(1.0);
	glEnable( GL_DEPTH_TEST ); 
	glEnable( GL_CULL_FACE );
	
	InitLight();
	
	/* DFLT_INIT_NUM_PARTICLES defined in particles.h
	 * Create particles and add them into the particles list
	 * Here first call to one of your functions
	 */
	for (i=0; i<DFLT_INIT_NUM_PARTICLES; i++){
		particle_add(&particles);
	}
	
	return;
}




/*****************************************************************************
 FUNCTION :  InitLight
 PURPOSE  :  Initializes the lighting.
 INPUT    :  void
 OUTPUT   :  void
 NOTES    :  
 ******************************************************************************/
void InitLight( void ){
	GLfloat lightPos0[] = { 20.0, 20.0, 20.0, 1.0 };
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable( GL_COLOR_MATERIAL );
	glEnable( GL_NORMALIZE );
	glLightfv( GL_LIGHT0, GL_POSITION, lightPos0 );
}



/*****************************************************************************
 FUNCTION :  exit_func
 PURPOSE  :  calls particle_destroy to free the link list if it exists
 INPUT    :  void
 OUTPUT   :  void
 NOTES    :  
 ******************************************************************************/
void exit_func(void) {
	particle_destroy( &particles );
}




/*****************************************************************************
 FUNCTION :  animate 
 PURPOSE  :  update the particles, redraw the screen, restart the timer
 INPUT    :  not used
 OUTPUT   :  void
 NOTES    :  
 ******************************************************************************/
void animate(int step) {
	#if PRINT_PARTICLE_UPDATE_RENDER_TIME
		clock_t start;
		clock_t end;
		
		/* time particle_update() */
		start = clock();
		particle_update( &particles );
		end = clock();
		printf("Update Particles: %f ms\n", (((double)(end - start))/CLOCKS_PER_SEC));
	#else
		/* Update the particles */
		particle_update( &particles );
	#endif
	
	/* Render the particles again */
	glutPostRedisplay();
	
	/* Restart the timer */
	glutTimerFunc(MS, animate, 0);
}




/*****************************************************************************
  FUNCTION :  RenderParticles
  PURPOSE  :  clear the screen, render the particles, swap the buffers
  INPUT    :  void
  OUTPUT   :  void
  NOTES    :  
 ******************************************************************************/
void RenderParticles(void) {
	struct particle* tmp = particles;
	
	#if PRINT_PARTICLE_UPDATE_RENDER_TIME
		clock_t start;
		clock_t end;
	#endif
	
	/* get the start time. */
	#if PRINT_PARTICLE_UPDATE_RENDER_TIME
		start = clock();
	#endif
	
	/* clear the buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/* Draw the particles. */
	 while(tmp != NULL){
		glColor4f(tmp->col.r,
		          tmp->col.g,
		          tmp->col.b,
		          tmp->col.a);
		
		glPushMatrix();
		
		glTranslatef(tmp->pos.x,
		             tmp->pos.y,
		             tmp->pos.z);
		
		glutSolidSphere(tmp->size/2, 10, 2);
		
		glPopMatrix();
		
		tmp = tmp->next;
	}
	
	/* Swap the buffers */
	glutSwapBuffers();
	
	/* Print out the time taken. */
	#if PRINT_PARTICLE_UPDATE_RENDER_TIME
		end = clock();
		printf("Render Particles: %f ms\n", (((double)(end - start))/CLOCKS_PER_SEC));
	#endif
}




/*****************************************************************************
  FUNCTION :  keyboard
  PURPOSE  :  callback
  INPUT    :  the key pressed
  OUTPUT   :  void
  NOTES    :  exits on 'q' or 'Q'
 ******************************************************************************/
void keyboard(unsigned char key, int x, int y) {
	switch(key) {
		/* Press the space bar to add a particle */
		case ' ': {
			particle_add(&particles);
			break;
		}
		
		/* Enable/Disable lighting. */
		case 'l': {
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
			break;
		}
		case 'L': {
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			break;
		}
		
		/* Enable/Disable material coloring. */
		case 'c': {
			glDisable( GL_COLOR_MATERIAL );
			break;
		}
		case 'C': {
			glEnable( GL_COLOR_MATERIAL );
		}
		
		/* Change shader mode. */
		case 's': {
			glShadeModel( GL_FLAT );
			break;
		}
		case 'S': {
			glShadeModel( GL_SMOOTH );
			break;
		}
		
		/* Delete all the particles. */
		case 'd':
		case 'D': {
			particle_destroy(&particles);
			particles = NULL;
			break;
		}
		
		/* Quit program. */
		case 'q':
		case 'Q': {
			glutDestroyWindow(window);
			exit(0);
			break;
		}
	}
	glutPostRedisplay();
}




/*****************************************************************************
 FUNCTION :  mouse
 PURPOSE  :  callback
 INPUT    :  the button and its state
 OUTPUT   :  void
 NOTES    :  exits on middle mouse click
 *****************************************************************************/
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {    /* Quit the application. */
			glutDestroyWindow(window);
			exit(0);
	}
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {  /* Spawn a small cluster. */
		particle_explode_click(&particles, x, y, LEFT_CLICK_PARTICLE_COUNT);
	}
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) { /* Spawn a large cluster. */
		particle_explode_click(&particles, x, y, RIGHT_CLICK_PARTICLE_COUNT);
	}


	glutPostRedisplay();
}




/*****************************************************************************
  FUNCTION :  reshape
  PURPOSE  :  handle window resizing by updating the viewport and ortho
  INPUT    :  new window width and height
  OUTPUT   :  void
  NOTES    :  The ortho function defines the viewable world in which you
              render your particles.
              Ortho creates a 3D cube, anything you draw inside the cube
              gets render in your window.
              The world is centered in ( 0, 0, 0 ) in the middle of the screen
 ******************************************************************************/
void reshape(int w, int h) {
	int windowWidthHalf;
	int windowHeightHalf;
	
	windowWidthHalf = (w/2);
	windowHeightHalf = (h/2);
	
	if (h == 0){
		h = 1;
	}
	
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	#if PRINT_DEBUG_INFO
		printf("reshape()\n");
		printf("	windowWidthHalf: %d\n", windowWidthHalf);
		printf("	windowHeightHalf: %d\n", windowHeightHalf);
		
		printf("	width:  %d\n", w);
		printf("	height:  %d\n", w);
	#endif
	
	glOrtho(-windowWidthHalf,
		     windowWidthHalf,
		    -windowHeightHalf,
		     windowHeightHalf,
		    -ORTHO,
		     ORTHO);
	
	/* Original code.
	if (w <= h){
		glOrtho(-ortho,
		        ortho,
		        -windowHeightHalf,
		        windowHeightHalf,
		        -ORTHO,
		        ORTHO);
	}
	else{
		glOrtho(-ortho * w / h,
		        ortho * w / h,
		        -ortho,
		        ortho,
		        -ORTHO,
		        ORTHO);
	}
	*/
	glMatrixMode(GL_MODELVIEW);
}