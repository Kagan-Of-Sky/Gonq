/* C library headers. */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

/* OpenGL headers. */
#include <GL/glut.h>

/* My headers. */
#include "Kaganovsky_particle.h"
#include "Kaganovsky_particles.h"




int particle_init_firework(struct particle* p){
	float viewport[4];
	
	if(p == NULL){
		return 1;
	}
	
	/* Color */
	p->col.r = ((float)(rand() % 100)) / 100;
	p->col.g = ((float)(rand() % 100)) / 100;
	p->col.b = ((float)(rand() % 100)) / 100;
	p->col.a = 1;
	
	/* Position. */
	glGetFloatv(GL_VIEWPORT, viewport);
	p->pos.x = (((rand() & 0x1) == 0) ? -1 : 1) * (rand() % ((int)viewport[2]/3));
	p->pos.y = -viewport[3]/2;
	p->pos.z = 0;
	
	/* Direction */
	p->dir.x = (((rand() & 0x1) == 0) ? -1 : 1) * ((float)(rand() & 0x1f)) / 100;
	p->dir.y = 1.0f;
	p->dir.z = 0;
	
	/* Speed */
	p->spd.x = (float)((rand() & 0x3) + 4);
	p->spd.y = (float)((rand() & 0x3) + 6);
	p->spd.z = 0;
	
	/* Other */
	p->lifespan = (rand() % (int)viewport[3]/20) + viewport[3]/12;
	p->size     = (rand() & 0x1f) + 5;
	
	p->type = PARTICLE_TYPE_FIREWORK;
	p->next = NULL;
	return 0;
}




int particle_init_explosion(struct particle* p, struct particle* firework){
	if(p == NULL || firework == NULL){
		return 1;
	}
	
	/* Color */
	p->col.r = firework->col.r;
	p->col.g = firework->col.g;
	p->col.b = firework->col.b;
	p->col.a = firework->col.a;
	
	/* Position. */
	p->pos.x = firework->pos.x;
	p->pos.y = firework->pos.y;
	p->pos.z = firework->pos.z;
	
	/* Direction */
	p->dir.x = ((float)(rand() % 201 - 100)) / 100;
	p->dir.y = ((float)(rand() % 201 - 100)) / 100;
	p->dir.z = 0;
	
	/* Speed */
	p->spd.x = (float)((rand() & 0x7) + 4);
	p->spd.y = (float)((rand() & 0x7) + 4);
	p->spd.z = 0;
	
	/* Other */
	p->lifespan = (rand() & 0x1f) + 20;
	p->size     = (rand() & 0x7) + 1;
	p->type     = PARTICLE_TYPE_EXPLOSION;
	p->next     = NULL;
	
	return 0;
}




int particle_init_click(struct particle* p, float x, float y){
	if(p == NULL){
		return 1;
	}
	
	/* Color */
	p->col.r = ((float)(rand() % 100)) / 100;
	p->col.g = ((float)(rand() % 100)) / 100;
	p->col.b = ((float)(rand() % 100)) / 100;
	p->col.a = 1;
	
	/* Position. */
	p->pos.x = x;
	p->pos.y = y;
	p->pos.z = 0;
	
	/* Direction */
	p->dir.x = ((float)(rand() % 201 - 100)) / 100;
	p->dir.y = ((float)(rand() % 201 - 100)) / 100;
	p->dir.z = 0;
	
	/* Speed */
	p->spd.x = (float)((rand() & 0x7) + 10);
	p->spd.y = (float)((rand() & 0x7) + 10);
	p->spd.z = 0;
	
	/* Other */
	p->lifespan = (rand() & 0x1f) + 25;
	p->size     = (rand() & 0x7) + 1;
	p->type     = PARTICLE_TYPE_EXPLOSION;
	p->next     = NULL;
	
	return 0;
}




int particle_add(struct particle **head){
	struct particle *newParticle;
	
	if(head == NULL){
		return -1;
	}
	
	newParticle = malloc(sizeof(struct particle));
	if(newParticle == NULL){
		return -1;
	}
	
	particle_init_firework(newParticle);
	newParticle->next = *head;
	
	*head = newParticle;
	
	return 0;
	
}




int particle_explode(struct particle **head, struct particle* firework){
	int i;
	struct particle *newParticle;
	
	if(head == NULL || firework == NULL){
		return 1;
	}
	
	/* The number of particles in the explosion depends on the size of the particle. */
	for(i=0; i<firework->size*5; i++){
		newParticle = malloc(sizeof(struct particle));
		if(newParticle == NULL){
			return 1;
		}
		
		/* Create the particle. */
		particle_init_explosion(newParticle, firework);
		
		/* Add the particle to the list. */
		newParticle->next = *head;
		*head = newParticle;
	}
	
	return 0;
}




int particle_explode_click(struct particle **head, int x, int y, int count){
	int i;
	struct particle *newParticle;
	
	float viewport[4];
	float xPos;
	float yPos;
	
	if(head == NULL){
		return 1;
	}
	
	glGetFloatv(GL_VIEWPORT, viewport);
	
	/* x coordinate. */
	if(x > viewport[2]/2){
		xPos = x - viewport[2]/2;
	}
	else{
		xPos = -(float)(viewport[2]/2 - x);
	}
	
	/* y coordinate. */
	if(y < viewport[3]/2){
		yPos = viewport[3]/2 - y;
	}
	else{
		yPos = -(y - viewport[3]/2);
	}
	
	for(i=0; i<count; i++){
		newParticle = malloc(sizeof(struct particle));
		if(newParticle == NULL){
			return 1;
		}
		
		/* Create the particle. */
		particle_init_click(newParticle, xPos, yPos);
		
		/* Add the particle to the list. */
		newParticle->next = *head;
		*head = newParticle;
	}
	
	return 0;
}




int particle_remove( struct particle* p ){
	free(p);
	return 0;
}




int particle_update( struct particle **head ){
	#if UPDATE_PARTICLES
		float viewport[4];
		float windowWidthHalf;
		float windowHeightHalf;
		float xmin;
		float xmax;
		float ymin;
		float ymax;
		
		struct particle * previous;
		struct particle * current;
		int currentHalfSize;
		bool exploded;
		
		#if PRINT_DEBUG_INFO
			int numParticles;
		#endif
		
		if(head == NULL || *head == NULL){
			return 1;
		}
		
		glGetFloatv(GL_VIEWPORT, viewport);
		
		#if PRINT_DEBUG_INFO
			printf(" Viewport:-------------------------------------------------------------------------------------------------------------------------------\n");
			printf(" 	x: %f\n", viewport[0]);
			printf(" 	y: %f\n", viewport[1]);
			printf("	w: %f\n", viewport[2]);
			printf("	h: %f\n", viewport[3]);
		#endif
		
		windowWidthHalf  = viewport[2] / 2;
		windowHeightHalf = viewport[3] / 2;
		
		xmin = -windowWidthHalf;
		xmax =  windowWidthHalf;
		
		ymin = -windowHeightHalf;
		ymax =  windowHeightHalf;
		
		previous = *head;
		current  = *head;
		#if PRINT_DEBUG_INFO
			numParticles = 0;
		#endif
		
		while(current != NULL){
			/* Print out the coordinates. */
			#if PRINT_DEBUG_INFO
				printf("	--------------------------------------------------------------------------\n");
				printf("		Position:\n");
				printf("			x = %f\n", current->pos.x);
				printf("			y = %f\n", current->pos.y);
				printf("			z = %f\n", current->pos.z);
				printf("		Dimensions:\n");
				printf("			s = %d\n", current->size);
			#endif
			
			currentHalfSize = current->size/2;
			
			exploded = false;
			
			/* Update the coordinates. */
			current->pos.x += (current->spd.x * current->dir.x);
			current->pos.y += (current->spd.y * current->dir.y);
			
			/* Update the speed. */
			current->spd.y -= 0.02;
			/* current->spd.x -= 0.01; Looks better without this. */
			
			/* Update the direction. */
			current->dir.y -= 0.003;
			
			/* Explosion particles are more common */
			if(current->type == PARTICLE_TYPE_EXPLOSION){
				current->dir.x += (current->dir.x > 0) ? -0.01 : 0.01;
				current->dir.y -= (current->dir.y >= 0) ? 0.03 : 0.02;
				
				/* Bounce the particle off the ground. */
				if(current->pos.y - currentHalfSize <= ymin){
					current->dir.y = -current->dir.y / 2;
					current->pos.y += (current->spd.y * current->dir.y);
				}
				/* Bounce the particle off the sides. */
				else if((current->pos.x - currentHalfSize <= xmin) || (current->pos.x + currentHalfSize >= xmax)){
					current->dir.x = -current->dir.x / 2;
					current->pos.x += (current->spd.x * current->dir.x);
				}
				
				if(current->size != 0 && (rand() & 0x7) == 0){
					current->size--;
				}
			}
			/* firework particle. */
			else{
				/* The particle has exploded.
				 * The following check: current->lifespan == 2 
				 * is done because:     current->lifespan == 1
				 * causes a crash on the next iteration of the loop
				 * because the 'previous' pointer is not updated
				 * properly.
				 */
				if(current->lifespan == 2){
					particle_explode(&particles, current);
					exploded = true;
				}
			}
			
			(current->lifespan)--;
			
			/* Check if this element has run out of life,
			 * or has gone out of bounds and needs to be 
			 * deleted. */
			
			/* TODO: when the particle is on the border and has exploded,
			 * this will cause a segmentation fault, the boolean value
			 * exploded is there to protect against this.
			 */
			if(exploded == false &&
				(
					(current->lifespan <= 0)                     ||
					((current->pos.y - currentHalfSize) >= ymax) ||
					((current->pos.x - currentHalfSize) >= xmax) ||
					((current->pos.x + currentHalfSize) <= xmin)
				)
			){
				/* Check if this element is the head. */
				if(current == *head){
					*head = current->next;
					particle_remove(current);
					current = *head;
				}
				else{
					previous->next = current->next;
					particle_remove(current);
					current = previous->next;
				}
			}
			else{
				previous = current;
				current = current->next;
				#if PRINT_DEBUG_INFO
					numParticles++;
				#endif
			}
		}
		#if PRINT_DEBUG_INFO
			printf("numParticles = %d\n", numParticles);
		#endif
	#endif
	return 0;
}




int particle_destroy( struct particle ** head ){
	struct particle * previous;
	struct particle * current;
	int numFreed;
	
	/* Check if head points to a valid linked list of particles. */
	if(head == NULL){
		return -1;
	}
	else if(*head == NULL){
		return -1;
	}
	
	current = *head;
	
	/* Check if the list is only 1 element long. */
	if(current->next == NULL){
		free(current);
		return 1;
	}
	
	previous = current;
	current  = current->next;
	numFreed = 0;
	while(current != NULL){
		free(previous);
		numFreed++;
		previous = current;
		current  = current->next;
	}
	
	free(previous);
	numFreed++;
	
	return 0;
}