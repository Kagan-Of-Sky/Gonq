/* File Name:     buffer.c
 * Compiler:      MS Visual Studio 2013
 * Author:        Mark Kaganovsky, 040789903
 * Course:        CST 8152 - Compilers, Lab Section 012
 * Assignment:    1
 * Date:          March 8 2016
 * Professor:     Sv. Ranev
 * Purpose:       Implementation of buffer.h
 * 
 * Function List: b_create()
 *                b_addc()
 *                b_reset()
 *                b_free()
 *                b_isfull()
 *                b_size()
 *                b_capacity()
 *                b_setmark()
 *                b_mark()
 *                b_mode()
 *                b_incfactor()
 *                b_load()
 *                b_isempty()
 *                b_eob()
 *                b_getc()
 *                b_print()
 *                b_pack()
 *                b_rflag()
 *                b_retract()
 *                b_retract_to_mark()
 *                b_getcoffset()
 */




#include "buffer.h"




/* PURPOSE:          Create a new Buffer and return a handle to it.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.1
 * CALLED FUNCTIONS: calloc(), free(), malloc()
 *
 * PARAMETERS:       short init_capacity: Initial capacity of the buffer.
 *                                        Must be > 0 for a fixed buffer.
 *                                        Must be >= 0 for an additive or multiplicative buffer.
 *
 *                   char inc_factor:     Used to grow the buffer when it is full. Please see the o_mode parameter for more details.
 *                                        If set to 0 then the o_mode argument is overriden and set to 'f'ixed mode.
 *                                        This argument is interpreted by the function as an 'unsigned char', despite the parameter
 *                                        being a 'signed char'.
 *
 *                   char o_mode:         B_MODE_FIXED_SIZE_ARG     - Fixed size buffer, this buffer is not capable of growing.
 *                                                                    inc_factor is ignored.
 *
 *                                        B_MODE_ADDITIVE_ARG       - Additive buffer. The value of inc_factor (1 to 255 inclusive)
 *                                                                    will be added to the buffer size when it needs to grow. This
 *                                                                    This makes the buffer grow in a linear fashion.
 *
 *                                        B_MODE_MULTIPLICATIVE_ARG - Multiplicative buffer. The value of inc_factor (1 to 100 inclusive) is
 *                                                                    explained in the "ALGORITHM" section.
 *
 * RETURN VALUE:      A pointer to a Buffer structure. This pointer can then be passed to the functions b_XXXXXX().
 *                    NULL if the arguments are invalid or if memory can not be allocated for the Buffer.
 *
 * ALGORITHM:         In order to grow the buffer in multiplicative mode, the following algorithm is used:
 *                        available space = maximum buffer size – current capacity
 *                        new increment   = available space * inc_factor / 100
 *                        new capacity    = current capacity + new increment
 */
Buffer * b_create(short init_capacity, char inc_factor, char o_mode){
	Buffer *buf; /* Pointer to buffer being created */

	unsigned char unsigned_inc_factor; /* Unsigned version of inc_factor */
	
	unsigned_inc_factor = (unsigned char)inc_factor; /* Interpret the increment factor as unsigned. */

	/* Validate parameters. */ 
	if (init_capacity < 0){
		return NULL;
	}

	/* An increment factor of zero overrides the buffer mode to fixed mode. */
	if (!unsigned_inc_factor){
		o_mode = B_MODE_FIXED_SIZE_ARG;
	}

	/* Validate the arguments based on the buffer mode. */
	switch (o_mode){
		case B_MODE_FIXED_SIZE_ARG:{
			if (!init_capacity){
				return NULL;
			}
			break;
		}
		
		case B_MODE_ADDITIVE_ARG:{
			break;
		}
		
		case B_MODE_MULTIPLICATIVE_ARG:{
			if (unsigned_inc_factor > 100){
				return NULL;
			}
			break;
		}
		
		default:{ /* Invalid buffer mode. */
			return NULL;
		}
	}
	/* Arguments are all valid beyond this point. */
	
	/* Allocate memory for the Buffer struct. */
	buf = (Buffer *)calloc(1, sizeof(Buffer));
	if (buf == NULL){
		return NULL;
	}

	/* Initialize the Buffer struct based on the o_mode parameter. */
	switch (o_mode){
		case B_MODE_FIXED_SIZE_ARG:{
			buf->mode = B_MODE_FIXED_SIZE;
			break;
		}

		case B_MODE_ADDITIVE_ARG:{
			buf->mode = B_MODE_ADDITIVE;
			buf->inc_factor = inc_factor;
			break;
		}

		case B_MODE_MULTIPLICATIVE_ARG:{
			buf->mode = B_MODE_MULTIPLICATIVE;
			buf->inc_factor = inc_factor;
			break;
		}
	}

	/* Allocate memory for the buffer's storage.
	 * 
	 * If the initial capacity is 0 at this point, then the buffer is in either additive or multiplicative mode.
	 * To stay platform independant, the call to malloc() is prevented until the realloc() call in b_addc().
	 */
	if (init_capacity != 0){
		buf->cb_head = (char *)malloc(init_capacity);
		if (buf->cb_head == NULL){
			free(buf);
			return NULL;
		}
		buf->capacity = init_capacity;
	}

	return buf;
}




/* PURPOSE:          Try to add 'symbol' to the buffer pointed to by 'pBD'.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.1
 * CALLED FUNCTIONS: b_isfull(), realloc()
 *
 * PARAMETERS:       pBuffer const pBD: A pointer to a Buffer structure.
 *                   char symbol:       The character to add to the buffer pointed to by pBD.
 *
 * RETURN VALUE:     A pointer to pBD if everything goes OK.
 *                   NULL if pBD is NULL, or the buffer can not be expanded. In this case, all fields in pBD are left unchanged.
 *
 * ALGORITHM:        If the buffer is full, this function attempts to expand it.
 *                   If the buffer is succesfully expanded then 'symbol' is added at index 'pBD->addc_offset', and addc_offset is
 *                   incremented.
 */
pBuffer b_addc(pBuffer const pBD, char symbol){
	char *newBufferStorage; /* Pointer to the new buffer location if the buffer needs to be expanded. */
	short newBufferSize;    /* The size of the new buffer if it is expanded. */

	short availableSpace;   /* Used when expanding a multiplicative mode buffer. */
	float newIncrement;     /* Used when expanding a multiplicative mode buffer. It is a float so that checking for overflow can be done. */

	if (pBD == NULL){
		return NULL;
	}

	pBD->r_flag = 0;

	/* Check if the buffer needs to be expanded. */
	if (b_isfull(pBD)){
		if (pBD->capacity == SHRT_MAX){ /* Buffer is already at max capacity, can not expand anymore. */
			return NULL;
		}

		/* Expand the buffer based on the mode it is in. */
		switch (pBD->mode){
			case B_MODE_FIXED_SIZE: {
				return NULL;
			}
			
			case B_MODE_ADDITIVE: {
				newBufferSize = pBD->capacity + ((unsigned char)(pBD->inc_factor));
				if (newBufferSize < 0){
					return NULL;
				}
				break;
			}
			
			case B_MODE_MULTIPLICATIVE: {
				availableSpace = SHRT_MAX - pBD->capacity;                      /* available space = maximum buffer size – current capacity */
				newIncrement   = (float)availableSpace * pBD->inc_factor / 100; /* new increment = available space * inc_factor / 100 */
				
				if ((newIncrement + pBD->capacity) > SHRT_MAX){
					newBufferSize = SHRT_MAX;
				}
				else{
					newBufferSize = pBD->capacity + (short)newIncrement;          /* new capacity = current capacity + new increment */
					if (newBufferSize == pBD->capacity){ /* New capcity is the same as the current capacity, just max out the buffer size. */
						newBufferSize = SHRT_MAX;
					}
				}
				break;
			}
			
			default: { /* Should never execute. Left here because we might as well keep it. */
				return NULL;
			}
		}
		
		/* Expand the storage buffer. */
		newBufferStorage = (char *)realloc(pBD->cb_head, newBufferSize);
		if (newBufferStorage == NULL){
			return NULL;
		}

		if (newBufferStorage != pBD->cb_head){ /* realloc() changed the memory location of the buffer. */
			pBD->r_flag  = SET_R_FLAG;
			pBD->cb_head = newBufferStorage;
		}

		pBD->capacity = newBufferSize;
	}
	
	/* Add the new character to the buffer. */
	pBD->cb_head[pBD->addc_offset] = symbol;
	++(pBD->addc_offset);
	
	return pBD;
}




/* PURPOSE:          Reset some of the buffer fields to make it look like a new Buffer.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: none
 *
 * PARAMETERS:       Buffer * const pBD: A pointer to a Buffer struct.
 * 
 * RETURN VALUE:     SUCCESS: 0 is returned.
 *                   FAILURE: R_FAIL1 if pBD is NULL.
 *
 * ALGORITHM:        Resets the following fields in pBD to 0:
 *                   addc_offset
 *                   getc_offset
 *                   mark_offset
 *                   r_flag
 *                   eob
 *                   Everything else remains unchanged.
 */
int b_reset(Buffer * const pBD){
	if (pBD == NULL){
		return R_FAIL1;
	}
	
	pBD->addc_offset = 0;
	pBD->getc_offset = 0;
	pBD->mark_offset = 0;
	pBD->r_flag      = 0;
	pBD->eob         = 0;

	return 0;
}




/* PURPOSE:          To free all memory allocated to a Buffer.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: free()
 *
 * PARAMETERS:       Buffer * const pBD: The Buffer to free.
 *
 * RETURN VALUE:     none
 *
 * ALGORITHM:        none
 */
void b_free(Buffer * const pBD){
	if (pBD == NULL){
		return;
	}

	free(pBD->cb_head);
	free(pBD);
}




/* PURPOSE:          Determine whether the buffer passed to it is full.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.1
 * CALLED FUNCTIONS: none
 *
 * PARAMETERS:       Buffer * const pBD: A pointer to a Buffer struct.
 *
 * RETURN VALUE:     R_FAIL1: pBD is NULL.
 *                   0:       Buffer is not full.
 *                   1:       Buffer is full.
 *
 * ALGORITHM:        none
 */
int b_isfull (Buffer * const pBD){
	return (pBD == NULL) ? R_FAIL1 : pBD->addc_offset == pBD->capacity;
}



/* PURPOSE:          Get the number of characters currently stored in the buffer.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: none
 *
 * PARAMETERS:       Buffer * const pBD: A pointer to a Buffer struct.
 *
 * RETURN VALUE:     SUCCESS: The number of characters currently stored in the buffer.
 *                   FAILURE: R_FAIL1, pBD is NULL.
 *
 * ALGORITHM:        none
 */
short b_size(Buffer * const pBD){
	if (pBD == NULL){
		return R_FAIL1;
	}

	return pBD->addc_offset;
}




/* PURPOSE:          Get the capacity of a Buffer.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: none
 *
 * PARAMETERS:       Buffer * const pBD: A pointer to a Buffer struct.
 *
 * RETURN VALUE:     SUCCESS: The total capacity of the buffer.
 *                   FAILURE: R_FAIL1, pBD is NULL.
 *
 * ALGORITHM:        none
 */
short b_capacity(Buffer * const pBD){
	if (pBD == NULL){
		return R_FAIL1;
	}

	return pBD->capacity;
}




/* PURPOSE:          Set the mark_offset of a Buffer.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: none
 *
 * PARAMETERS:       Buffer * const pBD: A pointer to a Buffer struct.
 *                   short mark:         The value to set mark_offset to.
 *
 * RETURN VALUE:     SUCCESS: A pointer to: (start of the buffer data) + (the offset).
 *                   FAILURE: NULL, pBD is NULL, or mark is an out of range value (mark < 0 or mark > addc_offset)
 *
 * ALGORITHM:        none
 */
char * b_setmark(Buffer * const pBD, short mark){
	if (pBD == NULL){
		return NULL;
	}

	/* Make sure that the mark is within range. */
	if (mark < 0 || mark > pBD->addc_offset){
		return NULL;
	}

	/* Set the mark and return a pointer to that offet in the buffer. */
	pBD->mark_offset = mark;

	return (pBD->cb_head + mark);
}




/* PURPOSE:          Get the current mark of a Buffer.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: none
 *
 * PARAMETERS:       Buffer * const pBD: A pointer to a Buffer struct.
 *
 * RETURN VALUE:     SUCCESS: the current mark_offset of the Buffer pointed to by pBD (a value >= 0).
 *                   FAILURE: R_FAIL1, pBD is NULL.
 *
 * ALGORITHM:        none
 */
short b_mark(Buffer * const pBD){
	if (pBD == NULL){
		return R_FAIL1;
	}

	return pBD->mark_offset;
}




/* PURPOSE:          Get the mode that the buffer is currently operating in.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: none
 *
 * PARAMETERS:       Buffer * const pBD: A pointer to a Buffer struct.
 *
 * RETURN VALUE:     R_FAIL2: pBD is NULL.
 *                   SUCCESS: 1: Buffer is in additive mode.
 *                            0: Buffer is in fixed size mode.
 *                           -1: Buffer is in multiplicative mode.
 *
 * ALGORITHM:        none
 */
int b_mode(Buffer * const pBD){
	if (pBD == NULL){
		return R_FAIL2;
	}

	return pBD->mode;
}




/* PURPOSE:          Get the increment factor of the buffer.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: none
 *
 * PARAMETERS:       Buffer * const pBD: A pointer to a Buffer struct.
 *
 * RETURN VALUE:     SUCCESS: The positive value of pBD->inc_factor (inc_factor casted to size_t).
 *                            The following is the ranges of value which can be returned.
 *                                                 0:    If the buffer is in fixed mode.
 *                                1 to 255 inclusive:    If the buffer is in additive mode.
 *                                1 to 100 inclusive:    If the buffer is in multipicative mode.
 *
 *                   FAILURE: 256, pBD is NULL.
 *
 * ALGORITHM:        none
 */
size_t b_incfactor(Buffer * const pBD){
	if (pBD == NULL){
		return 256;
	}

	return (size_t)((unsigned char)pBD->inc_factor);
}




/* PURPOSE:          Fill up a Buffer with characters from an open stream.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: feof(), fgetc(), ungetc(), b_addc()
 *
 * PARAMETERS:       FILE * const fi:    The stream to read characters from.
 *                   Buffer * const pBD: A pointer to a buffer to store the characters read from the stream.
 *
 * RETURN VALUE:     R_FAIL1:   fi or pBD is NULL, or an error occurs while reading from the stream.
 *                   LOAD_FAIL: A character read from the stream can not be added to the buffer (most likely buffer is full).
 *                              In this case the character which could not be added is pushed back into the stream.
 *                   0:         Everything went ok, pBD now contains every character from the stream 'fi'.
 *
 * ALGORITHM:        none
 */
int b_load(FILE * const fi, Buffer * const pBD){
	int c; /* For fgetc(). */

	if (fi == NULL || pBD == NULL){
		return R_FAIL1;
	}
	
	c = getc(fi);
	if (ferror(fi)){ /* An error has occured on the stream. */
		return R_FAIL1;
	}

	while (!feof(fi)){
		if (b_addc(pBD, (char)c) == NULL){
			ungetc(c, fi); /* Push the character back into the stream so we dont lose it. */
			return LOAD_FAIL;
		}

		c = getc(fi);
		if (ferror(fi)){ /* An error has occured on the stream. */
			return R_FAIL1;
		}
	}

	return 0;
}




/* PURPOSE:          Check if the Buffer is empty.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: none
 *
 * PARAMETERS:       Buffer * const pBD: A pointer to a Buffer struct.
 *
 * RETURN VALUE:     R_FAIL1: pBD is NULL.
 *                   0:       The buffer is not empty.
 *                   1:       The buffer is empty.
 *
 * ALGORITHM:        none
 */
int b_isempty(Buffer * const pBD){
	if (pBD == NULL){
		return R_FAIL1;
	}

	return (pBD->addc_offset == 0);
}




/* PURPOSE:          To check if a Buffer has reached the end.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: none
 *
 * PARAMETERS:       Buffer * const pBD: A pointer to a Buffer struct.
 *
 * RETURN VALUE:     R_FAIL1: pBD is NULL.
 *                   0:       End of buffer has not been reached.
 *                   1:       End of buffer has been reached.
 *
 * ALGORITHM:        
 */
int b_eob(Buffer * const pBD){
	if (pBD == NULL){
		return R_FAIL1;
	}

	return pBD->eob;
}




/* PURPOSE:          Fetch the next character from a buffer and move the buffer up one character.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: none
 *
 * PARAMETERS:       Buffer * const pBD: A pointer to Buffer.
 *
 * RETURN VALUE:     SUCCESS: The next character in the buffer.
 *                   FAILURE: R_FAIL2, pBD is NULL
 *                            R_FAIL1, end of buffer has been reached.
 *
 * ALGORITHM:        none
 */
char b_getc(Buffer * const pBD){
	char c; /* The character to return. */

	if (pBD == NULL){
		return R_FAIL2;
	}

	/* Check if eob has been reached. */
	if (pBD->getc_offset == pBD->addc_offset){
		pBD->eob = 1;
		return R_FAIL1;
	}
	
	/* Not at end of buffer. */
	pBD->eob = 0;
	
	/* Fetch character */
	c = pBD->cb_head[pBD->getc_offset];

	/* Move buffer up by 1 char. */
	++(pBD->getc_offset);

	return c;
}




/* PURPOSE:          Print out the contents of the buffer from beginning to end.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: b_eob(), b_getc(), putchar()
 *
 * PARAMETERS:       Buffer * const pBD: A pointer to a Buffer.
 *
 * RETURN VALUE:     SUCCESS: 0, Everything went OK.
 *                   FAILURE: R_FAIL1, pBD is NULL.
 *                   
 *
 * ALGORITHM:        none
 */
int b_print(Buffer * const pBD){
	char c; /* For return value of b_getc() */
	
	if (pBD == NULL){
		return R_FAIL1;
	}
	
	/* Check if the buffer is empty. */
	if (!pBD->addc_offset){
		printf("The buffer is empty.\n");
		return 0;
	}
	
	pBD->getc_offset = 0;

	c = b_getc(pBD);
	while (!b_eob(pBD)){
		putchar(c);
		c = b_getc(pBD);
	}
	
	pBD->getc_offset = 0;
	
	putchar('\n');
	
	return 0;
}




/* PURPOSE:          Packs the buffer so that there is room for only one more character.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.1
 * CALLED FUNCTIONS: none
 *
 * PARAMETERS:       Buffer * const pBD: A pointer to a buffer struct.
 *
 * RETURN VALUE:     SUCCESS: A pointer to pBD.
 *                   FAILURE: NULL, the buffer is already at max capacity, 
 *                                  realloc failed,
 *                                  pBD is NULL.
 *
 * ALGORITHM:        none
 */
Buffer *b_pack(Buffer * const pBD){
	char *newStorageBuffer; /* Pointer to the new location if realloc changes the location of the buffer. */

	if (pBD == NULL){
		return NULL;
	}
	else if (pBD->addc_offset == SHRT_MAX){
		return NULL;
	}

	/* Reallocate the storage buffer. */
	newStorageBuffer = (char *)realloc(pBD->cb_head, pBD->addc_offset + (short)1);
	if (newStorageBuffer == NULL){
		return NULL;
	}

	/* Set the fields in pBD if the location of cb_head changed. */
	if (newStorageBuffer != pBD->cb_head){
		pBD->r_flag = 1;
		pBD->cb_head = newStorageBuffer;
	}

	/* Update the capacity of the buffer. */
	pBD->capacity = pBD->addc_offset + (short)1;

	return pBD;
}




/* PURPOSE:          Get the r_flag for a buffer.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: none
 *
 * PARAMETERS:       Buffer * const pBD: A pointer to a buffer struct.
 *
 * RETURN VALUE:     SUCCESS: The r_flag for pBD.
 *                   FAILURE: R_FAIL1, 'pBD' is NULL.
 *
 * ALGORITHM:        none
 */
char b_rflag(Buffer * const pBD){
	if (pBD == NULL){
		return R_FAIL1;
	}

	return pBD->r_flag;
}




/* PURPOSE:          Retract the buffer by one character.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: none
 *                   
 * PARAMETERS:       Buffer * const pBD: A pointer to a buffer struct.
 *                   
 * RETURN VALUE:     SUCCESS: The new position in the buffer (pBD->getc_offset - 1).
 *                   FAILURE: R_FAIL1, 'pBD' is NULL, or the buffer is already at the beginning.
 *                            0 if the offset is already at 0.
 *                   
 * ALGORITHM:        none
 */
short b_retract(Buffer * const pBD){
	if (pBD == NULL){
		return R_FAIL1;
	}
	else if (!pBD->getc_offset){
		return 0;
	}

	--(pBD->getc_offset);

	return pBD->getc_offset;
}




/* PURPOSE:          Retract the buffer to the mark (sets pBD->getc_offset to pBD->mark_offset).
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: none
 *                   
 * PARAMETERS:       Buffer * const pBD: A pointer to a buffer struct.
 *                   
 * RETURN VALUE:     SUCCESS: The new value of pBD->getc_offset.
 *                   FAILURE: R_FAIL1, 'pBD' is NULL.
 *                   
 * ALGORITHM:        none
 */
short b_retract_to_mark(Buffer * const pBD){
	if (pBD == NULL){
		return R_FAIL1;
	}

	pBD->getc_offset = pBD->mark_offset;

	return pBD->getc_offset;
}




/* PURPOSE:          Get the current position of the buffer.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: none
 *                   
 * PARAMETERS:       Buffer * const pBD: A pointer to a buffer struct.
 *                   
 * RETURN VALUE:     SUCCESS: The current position of the buffer (a value >= 0).
 *                   FAILURE: R_FAIL1, pBD is NULL.
 *                   
 * ALGORITHM:        none
 */
short b_getcoffset(Buffer * const pBD){
	if (pBD == NULL){
		return R_FAIL1;
	}

	return pBD->getc_offset;
}

