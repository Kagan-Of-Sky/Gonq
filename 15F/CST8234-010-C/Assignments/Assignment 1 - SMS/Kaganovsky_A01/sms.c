/* Assignment:        Assignemnt 1
 * Author:            Mark Kaganovsky
 * Student Number:    040-789-903
 */

#include <stdio.h>
#include <stdlib.h>

/*****************************************************
 * DEFINES                                           *
 *****************************************************/

/* Information printing. */
#define PRINT_INFORMATION 0 /* For debugging, set this to a value other than 0 to print the values of the various registers. */

/* Booleans */
    #define TRUE  1
    #define FALSE 0

/* Operation codes */
    /* Input output operations */
        #define OPERATION_READ       10 /* Read a word from the file. */
        #define OPERATION_WRITE      11 /* Print the contents of a specific memory location to the terminal. */
    /* Load and store operations */
        #define OPERATION_LOAD       20 /* Load the accumulator with a value from memory. */
        #define OPERATION_STORE      21 /* Store the value in the accumulator to a specific location. */
    /* Arithmetic operations */
        #define OPERATION_ADD        30 /* Add a word in memory to whatever is in the accumulator. Store the result in the accumulator. */
        #define OPERATION_SUBTRACT   31 /* Subtract a word in memory from whatever is in the accumulator. Store the result in the accumulator. */
        #define OPERATION_DIVIDE     32 /* Divide the accumulator by a word from a specific location in memory. Store the result in the accumulator. */
        #define OPERATION_MULTIPLY   33 /* Multiply a word in memory to whatever is in the accumulator. Store the result in the accumulator. */
    /* Transfer of control operations */
        #define OPERATION_BRANCH     40 /* Branch to a specific word of code in memory. */
        #define OPERATION_BRANCHNEG  41 /* Branch to a specific word of code in memory if the value in the accumulator is negative. */
        #define OPERATION_BRANCHPOS  44 /* Branch to a specific word of code in memory if the value in the accumulator is positive. */
        #define OPERATION_BRANCHZERO 42 /* Branch to a specific word of code in memory if the value in the accumulator is zero. */
        #define OPERATION_HALT       43 /* Stop execution. */

/* Memory related */
    #define SIZE       1000          /* The size of the memory array. */
    #define INIT_MEMO  50505         /* The default values for the memory. */
    #define END       -999999        /* End of instruction. */
    #define MIN_WORD  -99999         /* Minimum value of a word. */
    #define MAX_WORD   99999         /* Maximum value of a word. */

/* Error codes. */
    /* Program load errors. */
        #define TOO_BIG        -10      /* Too many instructions to fit in memory. */
        #define INVALID_WORD   -20      /* Invalid word read. */
    /* Runtime errors. */
        #define INVALID_CODE   -30      /* Invalid operation code. */
        #define ADDRESSABILITY -40      /* Fetch instruction from an invalid memory location. */
        #define DIVIDE_BY_ZERO -50      /* Attempt to divide by zero. */
        #define UNDERFLOW      -60      /* The result of an arithmatic operation is less than -99999. */
        #define OVERFLOW       -70      /* The result of an arithmatic operation is more than 99999. */
        #define ILLEGAL_INPUT  -80      /* During a READ instruction, an attempt was made to read a value that was either less than -999 or more than 999. */







/*****************************************************
 * FUNCTION PROTOTYPES BELOW                         *
 *****************************************************/

/* Initialize every memory location to the macro 'INIT_MEMO' */
void init_memo( int a[ ] );

/* Dumps the memory, and all other variables. */
void dump(int a[ ], int accumulator, int instcounter, int validInstructions, int instregister, int operationcode, int operand , int maximum);

/* Helper function for dump(), simply dumps the memory array. */
void dump_memo( int a[ ], int max );

/* Reads the instructions from standard input and stores them in mem[]. */
int load( int mem[ ] );

/* Prints out an error message based on 'errorcode'. */
void error_message(int errorcode);

/* Returns 0 if num is between -999 and 999, or returns UNDERFLOW or OVERFLOW depending on the value of num. */
int checkArithmeticRange(int num);





/*****************************************************
 * MAIN                                              *
 *****************************************************/

int main(void){
    int  memory[SIZE];        /* The 1000 word memory of this cpu. */
    int  word;                /* Used as a temporary storage location. */
    int  errorno;             /* Used to store any errors that arise. */
    int  operationCode;       /* The operation code. First 2 digits of the instruction. */
    int  operand;             /* The operand for the opcode. Last 3 digits of the instruction. */
    int  instructionRegister; /* Holds the instruction that is currently being executed. */
    int  instructionCounter;  /* Holds the memory location of the next instruction to be executed. */
    int  accumulator;         /* Holds a single word in order to do arithmetic and branching. */
    int  validInstructions;   /* Counts the number of instructions that have been executed. */
    int  maxMemory;           /* The address to store the next piece of data, also the upper bound for any operation which reads data. */
    int  maxCodeMemory;       /* The last index for program code (everything greater than this value is data). */
    int  done;                /* boolean value for main loop. */
    char c;                   /* Temporary variable to consume newline for OPERATION_READ. */
    
    printf("********************************START EXECUTION********************************\n");
    
    /* Zero out registers. */
    operationCode       = 0;
    operand             = 0;
    instructionRegister = 0;
    instructionCounter  = 0;
    accumulator         = 0;
    validInstructions   = 0;
    maxMemory           = 0;
    maxCodeMemory       = 0;
    errorno             = 0;
    
    /* Initialize the memory */
    init_memo(memory);
    
    /* Fill the memory from standard input. */
    maxMemory = load(memory);
    if(maxMemory < 0){            /* An error occured. */
        error_message(maxMemory);
        putchar('\n');
        return EXIT_FAILURE;
    }
    
    maxCodeMemory = maxMemory - 1;
    
    #if PRINT_INFORMATION
        printf("codeMemory = %d\n", maxCodeMemory);
        printf("maxMemory  = %d\n", maxMemory);
    #endif
    
    /* Begin executing instructions. */
    done = FALSE;
    while(done == FALSE && instructionCounter < maxCodeMemory){
        /* Fetch the instruction. */
        instructionRegister = memory[instructionCounter];
		
		/* Decode the instruction. */
        operationCode = instructionRegister / 1000;
        operand = instructionRegister % 1000;
        
        /* Make the operand positive. */
        if(operand < 0){
           operand = -operand; 
        }
        
        #if PRINT_INFORMATION
            printf("operationCode = %d\n", operationCode);
            printf("operand       = %d\n", operand);
        #endif
        
        /* Execute the instruction. */
        switch (operationCode) {
        /* Input output operations */
            case OPERATION_READ:
			    /* Read the number and the newline. */
                if(fscanf(stdin, "%d%c", &word, &c) <= 0){   /* A number was not successfully matched. */
                    errorno = INVALID_WORD;
                }
                else if(word < MIN_WORD || word > MAX_WORD){ /* The number read is out of range. */
                    errorno = ILLEGAL_INPUT;
                }
                else if(maxMemory >= SIZE){                  /* Max memory has been reached. */
                    errorno = TOO_BIG;
                }
                else if(operand <= maxCodeMemory || operand > maxMemory){  /* Trying to read into out of range data. */
                    errorno = ADDRESSABILITY;
                }
                else{
                    printf("READ:      %0+6d\n", word);
                    memory[operand] = word;
                    maxMemory++;
                }
                break;
            case OPERATION_WRITE:
                if(operand <= maxCodeMemory || operand >= maxMemory){  /* Trying to read out of range data. */
                    errorno = ADDRESSABILITY;
                }
                else{
                    printf("WRITE:     %0+6d\n", memory[operand]);
                }
                break;
            
        /* Load and store operations */
            case OPERATION_LOAD:
                if(operand <= maxCodeMemory || operand >= maxMemory){  /* Trying to read out of range data. */
                    errorno = ADDRESSABILITY;
                }
                else{
                    accumulator = memory[operand];
                    printf("LOAD:      %0+6d\n", accumulator);
                }
                break;
            case OPERATION_STORE:
                if(maxMemory == SIZE){                                  /* Memory is full. */
                    errorno = TOO_BIG;
                }
                else if(operand <= maxCodeMemory || operand > maxMemory){  /* Trying to write over the code area in memory, or out of bounds memory.*/
                    errorno = ADDRESSABILITY;
                }
                else{
                    printf("STORE:     %0+6d -> %0+6d\n", accumulator, operand);
                    memory[operand] = accumulator;
                    if(operand == maxMemory){                           /* Program wants one more word in memory. */
                        maxMemory++;
                    }
                }
                break;
            
        /* Arithmetic operations */
            case OPERATION_ADD:
                if(operand <= maxCodeMemory || operand >= maxMemory){  /* Trying to write over the code area in memory, or out of bounds memory.*/
                    errorno = ADDRESSABILITY;
                }
                else{
                    printf("ADD:       %0+6d\n", memory[operand]);
                    accumulator += memory[operand];
                    errorno = checkArithmeticRange(accumulator);
                }
                break;
            case OPERATION_SUBTRACT:
                if(operand <= maxCodeMemory || operand >= maxMemory){  /* Trying to write over the code area in memory, or out of bounds memory.*/
                    errorno = ADDRESSABILITY;
                }
                else{
                    word = memory[operand];
                    printf("SUBTRACT:  %0+6d\n", word);
                    accumulator -= word;
                    errorno = checkArithmeticRange(accumulator);
                }
                break;
            case OPERATION_DIVIDE:
                if(operand <= maxCodeMemory || operand >= maxMemory){  /* Trying to write over the code area in memory, or out of bounds memory.*/
                    errorno = ADDRESSABILITY;
                }
                else{
                    word = memory[operand];
                    if(word == 0){                                  /* Trying to divide by zero. */
                        errorno = DIVIDE_BY_ZERO;
                    }
                    else{
                        printf("DIVIDE:    %0+6d\n", word);
                        accumulator /= word;
                    }
                }
                break;
            case OPERATION_MULTIPLY:
                if(operand <= maxCodeMemory || operand >= maxMemory){  /* Trying to write over the code area in memory, or out of bounds memory.*/
                    errorno = ADDRESSABILITY;
                }
                else{
                    word = memory[operand];
                    printf("MULTIPLY:  %0+6d\n", word);
                    accumulator *= word;
                    errorno = checkArithmeticRange(accumulator);
                }
                break;
            
        /* Transfer of control operations */
            case OPERATION_BRANCH:
                if(operand > maxCodeMemory){ /* Attempt to branch to out of range memory. */
                    errorno = ADDRESSABILITY;
                }
                else{
                    instructionCounter = operand;
                    printf("BRANCH:    %0+6d\n", instructionCounter);
                }
                break;
            case OPERATION_BRANCHNEG:
                if(accumulator < 0){
                    if(operand > maxCodeMemory){ /* Attempt to branch to out of range memory. */
                        errorno = ADDRESSABILITY;
                    }
                    else{
                        instructionCounter = operand;
                        printf("BRANCHN:   %0+6d\n", instructionCounter);
                    }
                }
                else{
                    instructionCounter++;
                }
                break;
            case OPERATION_BRANCHZERO:
                if(accumulator == 0){
                    if(operand > maxCodeMemory){ /* Attempt to branch to out of range memory. */
                        errorno = ADDRESSABILITY;
                    }
                    else{
                        instructionCounter = operand;
                        printf("BRANCHZ:   %0+6d\n", instructionCounter);
                    }
                }
                else{
                    instructionCounter++;
                }
                break;
            case OPERATION_BRANCHPOS:
                if(accumulator > 0){
                    if(operand > maxCodeMemory){ /* Attempt to branch to out of range memory. */
                        errorno = ADDRESSABILITY;
                    }
                    else{
                        instructionCounter = operand;
                        printf("BRANCHP:   %0+6d\n", instructionCounter);
                    }
                }
                else{
                    instructionCounter++;
                }
                break;
            case OPERATION_HALT:
                printf("HALT\n");
                done = TRUE;
                break;
                
            default:
                printf("UNKNOWN INSTRUCTION\n");
                done = TRUE;
                break;
        }
        /* Check if any errors occured. */
        if(errorno != 0){
            error_message(errorno);
            done = TRUE;
        }
        else{
            validInstructions++;
        }
        /* Increment instructionCounter if not branching. */
        if((done == FALSE)                         &&
           (operationCode != OPERATION_BRANCH)     &&
           (operationCode != OPERATION_BRANCHNEG)  &&
           (operationCode != OPERATION_BRANCHZERO) &&
           (operationCode != OPERATION_BRANCHPOS))
        {
            instructionCounter++;
        }
    }
    
    printf("*********************************END EXECUTION*********************************\n");
    
    /* End of program, dump the registors and memory. */
    dump(memory, accumulator, instructionCounter, validInstructions, instructionRegister, operationCode, operand, maxMemory);
    
    putchar('\n');
    
    return (errorno == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}








/*****************************************************
 * FUNCTION DEFINITIONS BELOW                        *
 *****************************************************/

void init_memo( int a[ ] ){
    int i;
    for(i=0; i<SIZE; i++){
        a[i] = INIT_MEMO;
    }
}

void dump(int a[ ], int accumulator, int instcounter, int validInstructions, int instregister, int operationcode, int operand, int maximum){
    printf("REGISTERS:\n");
    
    printf("accumulator            %0+6d\n", accumulator);
    printf("instructioncounter        %03d\n", instcounter);
    printf("instructionregister    %0+6d\n", instregister);
    printf("operationcode              %02d\n", operationcode);
    printf("operand                   %03d\n", operand);
    printf("ValidInstructions      %6d\n\n", validInstructions);
    
    dump_memo(a, maximum);
}

void dump_memo( int a[ ], int max ){
    int i;
    printf("MEMORY: \n\n");
    
    for(i=0; i<max; i++){       /* For every element in a[] up to 'max' */
        if((i%10) == 0){        /* Print out the tens column if needed. */
            printf("%4d ", i);
        }
        
        printf("%0+6d ", a[i]); /* Print out the data in the entry. */
        
        if(((i+1) % 10) == 0){  /* Print out a newline after every 10th element. */
            putchar('\n');
        }
    }
}

int load( int mem[ ] ){
    int  instruction; /* The instruction read from the file. */
    int  i;           /* Index into mem[]. */
    int  ret;         /* Return value of scanf. */
    
    /* Read the instructions. */
    i = 0;
    while((i < SIZE) &&
          ((ret = fscanf(stdin, "%d", &instruction)) == 1) && 
          (instruction != -999999) && 
          (instruction >= MIN_WORD && instruction <= MAX_WORD))
    {
        mem[i] = instruction;
        i++;
    }
    if(i >= SIZE){
        return TOO_BIG;
    }
    else if(ret == 0){
        return INVALID_WORD;
    }
    else if(instruction != -999999){
        return INVALID_WORD;
    }
    else{
        return i;
    }
}

void error_message(int errorcode){
    switch (errorcode) {
        case TOO_BIG:
            printf("*** ABEND: prg load: prg too big ***\n");
            break;
        case INVALID_WORD:
            printf("*** ABEND: prg load: invalid word ***");
            break;
        case INVALID_CODE:
            printf("*** INVALID OPCODE ***\n");
            break;
        case ADDRESSABILITY:
            printf("*** ABEND: Addressability error ***\n");
            break;
        case DIVIDE_BY_ZERO:
            printf("*** ABEND: attempted division by 0 ***\n");
            break;
        case UNDERFLOW:
            printf("*** ABEND: underflow ***\n");
            break;
        case OVERFLOW:
            printf("*** ABEND: overflow ***\n");
            break;
        case ILLEGAL_INPUT:
            printf("*** ABEND: illegal input ***\n");
            break;
        default:
            printf("*** ABEND: invalid opcode ***\n");
            break;
    }
}

int checkArithmeticRange(int num){
    if(num < -999){
        return UNDERFLOW;
    }
    else if(num > 999){
        return OVERFLOW;
    }
    else{
        return 0;
    }
}