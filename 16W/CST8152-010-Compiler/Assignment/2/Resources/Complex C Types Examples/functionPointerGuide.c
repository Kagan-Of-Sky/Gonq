#include <stdio.h>

/* Simple arithmetic functions. */
int add     (int left, int right){ return left+right; }
int subtract(int left, int right){ return left-right; }
int multiply(int left, int right){ return left*right; }

/* Function which takes a pointer to a function as an argument. */
int doOperation(int left, int right, int(*pointerToOperationFunction)(int, int)){
	return (*pointerToOperationFunction)(left, right);
}

/* Sorting function which takes a function pointer to do comparisons. */
void bubbleSort(int *a, int size, int (*compare)(int, int)){
	int outer;
	int inner;
	int temp;
	
	for(outer=size-1; outer>1; --outer){
		for(inner=0; inner<outer; ++inner){
			if((*compare)(a[inner], a[inner+1]) > 0){
				temp       = a[inner];
				a[inner]   = a[inner+1];
				a[inner+1] = temp;
			}
		}
	}
}

/* Compare 2 ints. */
int compareInts(int n1, int n2){
	return n1 - n2;
}

/* Compare the absolute value of 2 ints. */
int compareIntsAbsolute(int n1, int n2){
	/* Make both of the arguments positive. */
	if(n1 < 0){ n1 = -n1; }
	if(n2 < 0){ n2 = -n2; }
	
	return n1 - n2;
}

int main(){
	/* Format of function pointer:
	 *     RETURN_TYPE    (*NAME_OF_FUNCTION_POINTER)    (ARGUMENTS_TYPES)
	 */
	int (*pointerToAddFunction)     (int, int) = &add;
	int (*pointerToSubtractFunction)(int, int) = &subtract;
	int (*pointerToMultiplyFunction)(int, int) = &multiply;
	
	
	
	
	/* Format of array of function pointers:
	 *     RETURN_TYPE    (*ARRAY_NAME[SIZE])    (ARGUMENT_TYPES)
	 */
	int (*pointerToAddSubMulFunctions[3])(int, int) = {&add,
	                                                   &subtract,
	                                                   &multiply};
	int functionPointerArraySize = sizeof(pointerToAddSubMulFunctions) / sizeof(pointerToAddSubMulFunctions[0]);
	
	
	
	
	/* Format of dereferencing function pointer:
	 *     (*NAME_OF_FUNCTION_POINTER)    (ARGUMENTS_VALUES)
	 */
	puts("-------------------------------------------------------------------------------");
	printf("(*pointerToAddFunction)(1,2);      = %d\n", (*pointerToAddFunction)(1,2));
	printf("(*pointerToSubtractFunction)(1,2); = %d\n", (*pointerToSubtractFunction)(1,2));
	printf("(*pointerToMultiplyFunction)(1,2); = %d\n", (*pointerToMultiplyFunction)(1,2));
	puts("-------------------------------------------------------------------------------");
	
	
	
	
	/* Format of dereferencing array of function pointers:
	 *     (*NAME_OF_FUNCTION_POINTER[INDEX])    (ARGUMENTS_VALUES)
	 */
	int i;
	for(i=0; i<functionPointerArraySize; ++i){
		printf("Result: %d\n", (*pointerToAddSubMulFunctions[i])(1,2));
	}
	puts("-------------------------------------------------------------------------------");
	
	
	
	/* Call doOperation() */
	printf("doOperation(1, 2, pointerToAddFunction)      = %d\n", doOperation(1, 2, pointerToAddFunction));
	printf("doOperation(1, 2, pointerToSubtractFunction) = %d\n", doOperation(1, 2, pointerToSubtractFunction));
	printf("doOperation(1, 2, pointerToSubtractFunction) = %d\n", doOperation(1, 2, pointerToSubtractFunction));
	puts("-------------------------------------------------------------------------------");
	
	
	
	
	/* Sort array of ints using a generic bubble sort function which has a callback function to do comparisons. */
	int intArray[]   = {-3, 65, 2, 45, -23, 321, 5, 16, 45};
	int intArraySize = sizeof(intArray)/sizeof(intArray[0]);
	
	/* Print out the array before sorting. */
	puts("Array before sorting:");
	for(i=0; i<intArraySize; ++i){
		printf("%5d\n", intArray[i]);
	}
	
	/* Sort array by value. */
	bubbleSort(intArray, intArraySize, &compareInts);
	puts("Array after sorting by value:");
	for(i=0; i<intArraySize; ++i){
		printf("%5d\n", intArray[i]);
	}
	
	/* Sort array by absolute value. */
	bubbleSort(intArray, intArraySize, &compareIntsAbsolute);
	puts("Array after sorting by absolute value:");
	for(i=0; i<intArraySize; ++i){
		printf("%5d\n", intArray[i]);
	}
	
	puts("-------------------------------------------------------------------------------");
	
	
	
	
	return 0;
}








/* The function signal() takes an integer and a pointer to a
 * function (a function which returns nothing and takes an int as a parameter)
 * 
 * The function returns a pointer to a function which takes an int as a parameter
 * and returns nothing.
 */
extern void (*   signal(int,    void(*)(int)   )   )(int);