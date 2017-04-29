#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

#include "hill.h"

int main(int argc, char **argv){
	char   *sourceFilePath;    
	FILE   *sourceFile;        
	char   *destFilePath;      
	FILE   *destFile;          
	
	int  c;                    
	int  i;                      
	int  j;
	char *optString = "hm:";     /* Command line options for getopt(). */
	
	long matrixSize;             /* Size of the matrix (matrixDimensions ^ 2) */
	long matrixDimensions;       
	long currentMatrixNum;       
	long largestMatrixNum;       /* Used to print out the matrix. */
	int  numLargestMatrixDigits; /* Used to print out the matrix. */
	char *errorCurrentMatrixStr; 
	char *matrixSizestr;         /* The matrix dimensions from the command line. */
	char *errorMatrixSizestr;    /* A pointer to the first invalid character in 'matrixSizestr' */
	long *matrix;                /* Pointer to the dynamically allocated matrix array. */
	
	/* Not enough arguments. */
	if(argc < 9){
		fprintf(stderr, "ERROR: Not enough arguments\n");
		printHelpScreen(argv[0]);
		exit(EXIT_SUCCESS);
	}
	
	/* Parse command line arguments. */
	while((c=getopt(argc, argv, optString)) != -1){
		switch(c){
			/* Print out the help screen. */
			case 'h': {
				printHelpScreen(argv[0]);
				exit(EXIT_SUCCESS);
			}
			
			/* Matrix size. */
			case 'm': {
				errno              = 0;
				matrixSizestr      = optarg;
				errorMatrixSizestr = NULL;
				matrixDimensions   = strtol(matrixSizestr, &errorMatrixSizestr, 10);
				if(errno != 0){
					perror("ERROR");
					exit(EXIT_FAILURE);
				}
				else if(*errorMatrixSizestr != '\0'){
					fprintf(stderr, "ERROR: Invalid digit starting at: %s\n", errorMatrixSizestr);
					exit(EXIT_FAILURE);
				}
				else if(matrixDimensions < 2){
					fprintf(stderr, "ERROR: matrix dimensions must be greater than 1.\n");
					exit(EXIT_FAILURE);
				}
				matrixSize = matrixDimensions * matrixDimensions;
				break;
			}
			
			/* Invalid command line argument. */
			default:{
				exit(EXIT_FAILURE);
			}
		}
	}
	
	/* Check if the user passed enough arguments for the size of the matrix. */
	if((argc - optind) != (matrixSize + 2)){
		fprintf(stderr, "ERROR: There is an error in the number of arguments you passed\n");
		fprintf(stderr, "	Possibility 1: For a matrix with dimensions: %ld,\n"
		                "	               you need to have %ld arguments\n"
		                "	Possibility 2: You did not specify either the source\n"
		                "	               or the destination file.\n", matrixDimensions, matrixSize);
		exit(EXIT_FAILURE);
	}
	
	/* Allocate memory for the matrix array. */
	matrix = malloc(matrixSize * sizeof(long));
	if(matrix == NULL){
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	
	/* Convert the matrix values specified at the command line to longs and store them in the matrix array. */
	largestMatrixNum = LONG_MIN;
	for(i=optind, j = 0; i<(optind+matrixSize); i++, j++){
		errno                 = 0;
		errorCurrentMatrixStr = NULL;
		currentMatrixNum      = strtol(argv[i], &errorCurrentMatrixStr, 10);
		if(errno != 0){
			perror("ERROR");
			fprintf(stderr, "%s is too large\n", argv[i]);
			free(matrix);
			exit(EXIT_FAILURE);
		}
		else if(*errorCurrentMatrixStr != '\0'){
			fprintf(stderr, "ERROR: Invalid matrix digit starting at: %s\n", errorCurrentMatrixStr);
			free(matrix);
			exit(EXIT_FAILURE);
		}
		matrix[j] = currentMatrixNum;
		if(currentMatrixNum > largestMatrixNum){
			largestMatrixNum = currentMatrixNum;
		}
	}
	
	/* Open the source file. */
	sourceFilePath = argv[argc - 2];
	sourceFile     = fopen(sourceFilePath, "r");
	if(sourceFile == NULL){
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	
	/* Open the destination file. */
	destFilePath = argv[argc - 1];
	destFile     = fopen(destFilePath, "w");
	if(destFile == NULL){
		perror("ERROR");
		fclose(sourceFile);
		exit(EXIT_FAILURE);
	}
	
	/* Calculate the maximum number of digits in the largest matrix (for alignment of the matrix when printed). */
	numLargestMatrixDigits = 0;
	if(largestMatrixNum < 0){
		numLargestMatrixDigits++;
		largestMatrixNum = -largestMatrixNum;
	}
	while(largestMatrixNum > 0){
		largestMatrixNum /= 10;
		numLargestMatrixDigits++;
	}
	numLargestMatrixDigits++;
	
	/* Print out the matrix. */
	printf("Encrypting/Decrypting file %s into file %s using matrix:\n", sourceFilePath, destFilePath);
	printf("  +-%*s-+\n", (int)(numLargestMatrixDigits*matrixDimensions + matrixDimensions-2), " ");
	for(i=0; i<matrixSize; i++){
		if((i % matrixDimensions) == 0){
			printf("  |");
		}
		printf("%*ld ", numLargestMatrixDigits, matrix[i]);
		if(((i+1) % matrixDimensions) == 0){
			puts("|");
		}
	}
	printf("  +-%*s-+\n", (int)(numLargestMatrixDigits*matrixDimensions + matrixDimensions-2), " ");
	
	/* encrypt or decrypt the file. */
	encryptDecryptFile(matrix, matrixSize, matrixDimensions, sourceFile, destFile);
	
	/* Clean up resources. */
	fclose(sourceFile);
	fclose(destFile);
	free(matrix);
	
	return EXIT_SUCCESS;
}

void printHelpScreen(char *executableName){
	puts   ("Help Screen:");
	printf ("  USAGE: %s -m MATRIXSIZE MATRIX SOURCE DESTINATION\n", executableName);
	puts   ("         Encrypt/decrypt a file using matrix encryption.");
	puts   ("         To decrypt a file you have to specify the inverse matrix.");
	putchar('\n');
	puts   ("  Required Arguments:\n"
	        "    -m MATRIXSIZE MATRIX    Encrypt/decrypt a file using the following matrix.\n"
	        "\n"
	        "  Optional Arguments:\n"
	        "    -h                      Print this help screen.\n"
	        "\n"
	        "  Examples:");
	printf ("    Running the command: %s -m 2 0 1 3 1 original original.encrypted\n", executableName);
	puts   ("      Would encrypt the original file into original.encrypted using the matrix:");
	puts   ("      +--  --+");
	puts   ("      | 0  1 |");
	puts   ("      | 3  1 |");
	puts   ("      +--  --+");
	printf ("    Running the command: %s -m 3 0 1 2 3 4 5 6 7 8 original original.encrypted\n", executableName);
	puts   ("      Would encrypt the original file into original.encrypted using the matrix:");
	puts   ("      +--     --+");
	puts   ("      | 0  1  2 |");
	puts   ("      | 3  4  5 |");
	puts   ("      | 6  7  8 |");
	puts   ("      +--     --+");
}

void encryptDecryptFile(long* matrix, long matrixLength, long matrixDimensions, FILE *sourceFile, FILE *destFile){
	char *buffer;            /* Buffer to hold 'matrixDimensions' number of chars. */
	int  ret;
	
	int  matrixRow;
	int  matrixIndex;
	int  bufferIndex;
	long currentSum;
	
	/* Allocate memory for the buffer. */
	buffer = malloc(matrixLength);
	if(buffer == NULL){
		perror("ERROR");
		return;
	}
	
	/* While we are still completely filling the buffer. */
	while((ret=fread(buffer, sizeof(char), matrixDimensions, sourceFile)) == matrixDimensions){
		for(matrixRow=0; matrixRow<matrixLength; matrixRow += matrixDimensions){
			currentSum = 0;
			for(matrixIndex=matrixRow, bufferIndex=0; matrixIndex<(matrixRow+matrixDimensions); matrixIndex++, bufferIndex++){
				currentSum += matrix[matrixIndex] * buffer[bufferIndex];
			}
			
			if(fputc((int)(currentSum % 256), destFile) == -1){
				perror("ERROR");
				return;
			}
		}
	}
	
	/* Handle the case where the buffer was not completely filled. */
	if(ret > 0){
		fwrite(buffer, 1, ret, destFile);
		/*
		putchar('1');
		printf("%.*s", ret, buffer);
		for(matrixRow=0; matrixRow<(matrixDimensions*ret); matrixRow += matrixDimensions){
			currentSum = 0;
			for(matrixIndex=matrixRow, bufferIndex=0; matrixIndex<(matrixRow+ret); matrixIndex++, bufferIndex++){
				currentSum += matrix[matrixIndex] * buffer[bufferIndex];
			}
			printf(" %d\n", ((int)(currentSum % 256)));
			if(fputc((int)(currentSum % 256), destFile) == -1){
				perror("ERROR");
				return;
			}
		}
		*/
	}
	
	/* Check if an error occured while reading. */
	if(ferror(sourceFile) != 0){
		perror("ERROR");
	}
}