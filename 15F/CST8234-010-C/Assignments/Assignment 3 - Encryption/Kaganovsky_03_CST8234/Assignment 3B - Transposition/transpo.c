#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

#include "transpo.h"

int main(int argc, char **argv){
	char *sourceFilePath;        
	FILE *sourceFile;            
	char *destFilePath;          
	FILE *destFile;              
	struct stat fileStats;
	
	int  c;                      
	char *optString = "he:d:";   /* Command line options for getopt(). */
	char *keystr;                /* The key from the command line. */
	char *errorKeystr;           /* A pointer to the first invalid character in 'keystr' */
	long key;                    /* 'keystr' converted into a long. */
	char flagEncryptFile;        /* 0 to encrypt, 1 to decrypt. */
	
	if(argc == 1){
		printHelpScreen(argv[0]);
		exit(EXIT_SUCCESS);
	}
	
	/* Parse command line arguments. */
	flagEncryptFile = -1;
	while((c=getopt(argc, argv, optString)) != -1){
		switch(c){
			/* Print out the help screen. */
			case 'h': {
				printHelpScreen(argv[0]);
				exit(EXIT_SUCCESS);
			}
			
			/* Encrypt the file. */
			case 'e': {
				if(flagEncryptFile != -1){
					puts("ERROR: [-d KEY] already specified.\n");
					exit(EXIT_FAILURE);
				}
				flagEncryptFile = 1;
				keystr = optarg;
				break;
			}
			
			/* Decrypt the file. */
			case 'd': {
				if(flagEncryptFile != -1){
					puts("ERROR: [-e KEY] already specified.\n");
					exit(EXIT_FAILURE);
				}
				flagEncryptFile = 0;
				keystr = optarg;
				break;
			}
			
			/* Invalid command line argument. */
			default:{
				exit(EXIT_FAILURE);
			}
		}
	}
	
	/* Neither encription or decryption were specified. */
	if(flagEncryptFile == -1){
		puts("ERROR: one of the arguments [-e KEY] or [-d KEY] have to be specified.");
		exit(EXIT_FAILURE);
	}
	
	/* The source and destination files were not specified properly. */
	if(optind != argc - 2){
		fprintf(stderr, "ERROR: source and destination files not specified properly.");
		fprintf(stderr, "USAGE: %s [OPTIONS] SOURCE DESTINATION\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	/* Get the source and destination files. */
	sourceFilePath = argv[optind];
	destFilePath   = argv[optind+1];
	
	/* Convert the key to a long. */
	errno       = 0;
	errorKeystr = NULL;
	key         = strtol(keystr, &errorKeystr, 10);
	if(errno != 0){
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	else if(*errorKeystr != '\0'){
		fprintf(stderr, "ERROR: Invalid digit starting at: %s\n", errorKeystr);
		exit(EXIT_FAILURE);
	}
	else if(key < 2){
		fprintf(stderr, "ERROR: key must be greater than 1.\n");
		exit(EXIT_FAILURE);
	}
	key--;
	
	/* Open the files. */
	sourceFile = fopen(sourceFilePath, "r");
	if(sourceFile == NULL){
		fprintf(stderr, "ERROR: %s, ", sourceFilePath);
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	
	destFile = fopen(destFilePath, "w");
	if(destFile == NULL){
		fprintf(stderr, "ERROR: %s, ", destFilePath);
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	
	/* Get the file size. */
	if(stat(sourceFilePath, &fileStats) == -1){
		perror("ERROR");
		fclose(sourceFile);
		fclose(destFile);
		exit(EXIT_FAILURE);
	}
	
	/* Encrypt the file. */
	if(flagEncryptFile){
		printf("Encrypting file %s using key %ld into file %s\n", sourceFilePath, key+1, destFilePath);
		encryptFile(key, fileStats.st_size, sourceFile, destFile);
		puts("Done!");
	}
	/* Decrypt the file. */
	else{
		printf("Decrypting file %s using key %ld into file %s\n", sourceFilePath, key+1, destFilePath);
		decryptFile(key, fileStats.st_size, sourceFile, destFile);
		puts("Done!");
	}
	
	/* Clean up resources. */
	fclose(sourceFile);
	fclose(destFile);
	
	return EXIT_SUCCESS;
}

void printHelpScreen(char *executableName){
	puts("Help Screen:");
	printf("	USAGE: %s [OPTIONS] SOURCE DESTINATION\n", executableName);
	putchar('\n');
	puts("	Required Arguments:\n"
	     "		-e KEY     Encrypt a file using the KEY.\n"
	     "		-d KEY     Decrypt a file using the KEY.\n"
	     "		          *Only one of the above can be specified.\n"
	     "	Optional Arguments:\n"
	     "		-h         Print this help screen.");
}

void encryptFile(long key, off_t sourceFileSize, FILE *sourceFile, FILE *destFile){
	off_t numCharsProcessed;
	int   startingPoint;     /* Goes up by one after every pass through the source file. */
	int   c;
	
	startingPoint     = 0;
	numCharsProcessed = 0;
	
	while(numCharsProcessed < sourceFileSize){
		while((c=fgetc(sourceFile)) != EOF){
			fputc(c, destFile);
			numCharsProcessed++;
			fseek(sourceFile, key, SEEK_CUR);
		}
		startingPoint++;
		fseek(sourceFile, startingPoint, SEEK_SET);
	}
}

void decryptFile(long key, off_t sourceFileSize, FILE *sourceFile, FILE *destFile){
	off_t numCharsProcessed;
	int   startingPoint;     /* Goes up by one after every pass through the destination file. */
	int   c;
	
	startingPoint     = 0;
	numCharsProcessed = 0;
	
	while(numCharsProcessed < sourceFileSize){
		while(ftell(destFile) < sourceFileSize && (c=fgetc(sourceFile)) != EOF){
			fputc(c, destFile);
			numCharsProcessed++;
			fseek(destFile, key, SEEK_CUR);
		}
		startingPoint++;
		fseek(destFile, startingPoint, SEEK_SET);
	}
}