#ifndef CIPHER_H
#define CIPHER_H

#include <stdio.h>
#include <sys/types.h>


/* PURPOSE:
 *     Simply prints out a help screen.
 * 
 * PARAMETERS:
 *     char *executableName    The name the user used to call this program (argv[0]) (ex "./cipher")
 */
void printHelpScreen(char *executableName);




/* PURPOSE:
 *     Encrypt or decrypt (the process is the same for a Hill Cipher Transpotion algorithm) the
 *     'sourceFile' into the 'destFile' using the 'matrix' as the key.
 *     
 * PARAMETERS:
 *     long *matrix             An array containing the matrix.
 *     long matrixLength        The number of elements in the matrix array.
 *     long matrixDimensions    The dimensions of the matrix (same as matrixLength / 2).
 *     FILE *sourceFile         The source file.
 *     FILE *destFile           The destination file.
 */
void encryptDecryptFile(long *matrix, long matrixLength, long matrixDimensions, FILE *sourceFile, FILE *destFile);


#endif