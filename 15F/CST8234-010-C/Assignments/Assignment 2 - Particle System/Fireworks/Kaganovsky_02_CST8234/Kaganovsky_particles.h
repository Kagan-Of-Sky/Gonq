#ifndef KAGANOVSKY_PARTICLES_H
#define KAGANOVSKY_PARTICLES_H

/***********************************************
 Constant definitions.
 ***********************************************/
#define ON      1
#define OFF     0
#define OK      0
#define FAIL   -1
#define POINTS  0

/* My constants. */
#define LEFT_CLICK_PARTICLE_COUNT  100 /* The number of particles to spawn on a left click. */
#define RIGHT_CLICK_PARTICLE_COUNT 400 /* The number of particles to spawn on a right click. */

/***********************************************
 Default Window properties.
 ***********************************************/
#define WINDOW_TITLE       "CST8234 - Simple Particle Systems - Mark Kaganovsky"
#define DFLT_INIT_POS      0   /* Not used. */
#define DFLT_INIT_WINDOW_W 400 /* Window width. */
#define DFLT_INIT_WINDOW_H 400 /* Window height. */
#define ORTHO              100 /* Z axis. */
#define DFLT_BKG           0.0 /* Not used. */

/* animation frames per second */
#define DFLT_FPS 60
#define MS       (unsigned int)(1000.0 / DFLT_FPS)

#define PRINT_DEBUG_INFO                  0 /* Set to 0 to disable printing of debug info. */
#define PRINT_PARTICLE_UPDATE_RENDER_TIME 0 /* Set to 0 to disable the printing of the time taken to update and render the particles. */


/* Structs and typedefs */
	/* color and Color4 structs. */
	struct color {
		float r; /* Between 0.0 and 1.0 */
		float g; /* Between 0.0 and 1.0 */
		float b; /* Between 0.0 and 1.0 */
		float a; /* Between 0.0 and 1.0 */
	};
	typedef struct color Color4;




	/* Vector, Point3D and Vector3D structs. */
	struct vector { 
		float x;
		float y;
		float z;
	};
	typedef struct vector Point3D;
	typedef struct vector Vector3D;




	/* particle struct. */
	struct particle {
		Color4             col;        /* RGBA color of the particle. */
		Point3D            pos;        /* XYZ position of the particle. */
		Vector3D           dir;        /* XYZ direction of the particle (values between 0.0 and 1.0). */
		Vector3D           spd;        /* XYZ speed of the particle. */
		int                lifespan;   /* Lifespan of the particle. */
		int                size;       /* Radius of the particle. */
		int                type;       /* The type of particle (firework or explosion particle, PARTICLE_TYPE_XXXXX). */
		struct particle*   next;       /* This particle system uses a linked list as the data structure. */
	};




/* particle list head. */
extern struct particle* particles;




/***********************************************
 * Function prototypes.
 ***********************************************/
void exit_func(void);
void Init( void );
void InitLight( void );
void RenderParticles(void);
void reshape(int, int);
void animate(int);
void keyboard(unsigned char, int, int);
void mouse(int, int, int, int);




#endif /* KAGANOVSKY_PARTICLES_H */
