#ifndef KAGANOVSKY_PARTICLE_H
#define KAGANOVSKY_PARTICLE_H




#include <GL/glut.h>
#include "Kaganovsky_particles.h"




/* The initial number of particles. */
	#define DFLT_INIT_NUM_PARTICLES 10

/* Particle types */
	#define PARTICLE_TYPE_FIREWORK  0 /* A firework particle which starts at the bottom and shoots upwards. */
	#define PARTICLE_TYPE_EXPLOSION 1 /* When the firework explodes, it produces a cluster of particles, these particles do not explode later on. */

/* Debug macros. */
	#define UPDATE_PARTICLES        1 /* Set to 0 to disable the updating of particles. */


/********************************************************************* 
 * FUNCTION :  particle_init_xxx family of functions
 * 
 * PURPOSE  :  initialize a particle
 * 
 * INPUT    :  struct particle* p: A malloc()ed particle to fill in
 *             Other parameters are explained in the comment above
 *             each function.
 * 
 * OUTPUT   :  returns ­1 on error, 0 on success 
 * 
 * NOTES    :  This is a family of functions which perform similiar
 *             tasks, but different enough that seperate functions
 *             were necessary.
 ********************************************************************/
	
	/****************************************************************
	 * Initialize a firework particle
	 * 
	 * Particle has a long lifespan, starts at bottom middle of 
	 * the screen, moves upwards.
	 ***************************************************************/
	int particle_init_firework(struct particle* p);
	
	/****************************************************************
	 * Initialize a firework particle.
	 * 
	 * color and direction of 'p' get set to the same values as 
	 * 'struct particle* firework'.
	 * 
	 * Particle is small, fast, lifespan is short, and can move 
	 * in any direction.
	 ****************************************************************/
	int particle_init_explosion(struct particle* p, struct particle* firework);
	
	/****************************************************************
	 * Initialize a particle at (x,y) coordinates.
	 * This function is used when the user clicks somewhere in 
	 * the program window.
	 * 
	 * Particle is small, fast, lifespan is short, and can move in 
	 * any direction, and can have any color.
	 ***************************************************************/
	int particle_init_click(struct particle* p, float x, float y);




/********************************************************************* 
 * FUNCTION :  particle_add
 * 
 * PURPOSE  :  add a firework particle to the dynamic particle linked list
 * 
 * INPUT    :  struct particle *head. Head of the particle list
 * 
 * OUTPUT   :  returns ­1 on error, 0 on success
 * 
 * NOTES    :  Calls particle_init_firework()
 ********************************************************************/
int particle_add( struct particle **head);




/********************************************************************* 
 * FUNCTION :  particle_remove
 * 
 * PURPOSE :   remove a specific particle from the dynamic
 *             particle linked list
 *
 * INPUT    :  pointer to the particle to remove
 * 
 * OUTPUT   :  returns ­1 on error, 0 on success
 * 
 * NOTES    :  Particle can be situated in any place in the list.
 *             Usually deleted because the lifespan ran out.
 *             
 *             For efficiency reasons, this function only calls free().
 ********************************************************************/
int particle_remove(struct particle* p);




/********************************************************************* 
 * FUNCTION :  particle_destroy 
 * 
 * PURPOSE  :  free memory used by the dynamic particle linked list 
 * 
 * INPUT    :  struct particle **head. Head of the particle list 
 * 
 * OUTPUT   :  returns ­1 on error, 
               the number of particles destroyed on success 
 * 
 * NOTES    :  removes all particles from the list 
               Calls particle_remove()
 ********************************************************************/
int particle_destroy( struct particle **head );




/******************************************************************** 
 * FUNCTION :  particle_update
 * 
 * PURPOSE  :  update the particles properties to be rendered
 *             in the next frame
 * 
 * INPUT    :  struct particle **head. Head of the particle list
 * 
 * OUTPUT   :  returns ­1 on error, 0 on success
 * 
 * NOTES    :  This function also handles deleting of particles whos
 *             lifespan ran out, it maintains a previous and current
 *             pointer to do this.
 ********************************************************************/
int particle_update(struct particle **head);




/******************************************************************** 
 * FUNCTION :  particle_explode
 * 
 * PURPOSE  :  When a firework particle runs out of life, it will
 *             explode.
 * 
 * INPUT    :  struct particle **head:      Head of the particle list 
 *             struct particle* firework:   The firework particle
 *                                          which has just exploded.
 * 
 * OUTPUT   :  returns ­1 on error, 0 on success 
 ********************************************************************/
int particle_explode(struct particle **head, struct particle* firework);



/********************************************************************
 * FUNCTION :  particle_explode_click
 * 
 * PURPOSE  :  When the user left clicks or right clicks on the 
 *             window a cluster of particles will spawn.
 * 
 * INPUT    :  struct particle **head: Head of the particle list.
 *             int x: x coordinate of the mouse click.
 *             int y: y coordinate of the mouse click.
 *             int count: the number of particles to spawn.
 * 
 ********************************************************************/
int particle_explode_click(struct particle **head, int x, int y, int count);




#endif /* KAGANOVSKY_PARTICLE_H */