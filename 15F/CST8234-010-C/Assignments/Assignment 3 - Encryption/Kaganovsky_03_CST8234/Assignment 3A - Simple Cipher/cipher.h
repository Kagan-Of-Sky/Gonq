#ifndef CIPHER_H
#define CIPHER_H

#include <stdio.h>



/* PURPOSE:
 *     Simply prints out a help screen.
 * 
 * PARAMETERS:
 *     char *executableName: The name the user used to call this program (argv[0]) (ex "./cipher")
 */
void printHelpScreen(char *executableName);




/* PURPOSE:
 *     Encrypt the 'sourceFile' using the 'key' into the 'destFile'.
 *     
 * PARAMETERS:
 *     long key            The key to encrypt the file with.
 *     FILE *sourceFile    The source file.
 *     FILE *destFile      The destination file.
 */
void encryptFile(long key, FILE *sourceFile, FILE *destFile);




/* PURPOSE:
 *     Decrypt the 'sourceFile' using the 'key' into the 'destFile'.
 *     
 * PARAMETERS:
 *     long key            The key to decrypt the file with.
 *     FILE *sourceFile    The source file.
 *     FILE *destFile      The destination file.
 */
void decryptFile(long key, FILE *sourceFile, FILE *destFile);

#endif