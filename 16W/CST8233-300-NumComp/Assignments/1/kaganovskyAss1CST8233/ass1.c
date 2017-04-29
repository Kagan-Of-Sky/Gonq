/******************************************************************************
Filename:           ass1.c
Version:            1.0
Author:             Mark Kaganovsky
Student No:         040789903
Course Name/Number: Numerical Computing  CST8233
Lab Sect:           302
Assignment #:       1
Assignment name:    Ring Tone
Due Date:           February 21 2016
Submission Date:    February 19 2016
Professor:          Andrew Tyler

Purpose:            To use the following maclauren series:
                        f(t) = 0  +  t  -  0.5(t^2)  -  1/3(t^3)  +  5/24(t^4)  -  1/30(t^5)
                    
                    To approxomate the following function:
                        f(t) = (1-e^(-t))cos(t)
                    
******************************************************************************/




/* To supress warnings for functions such as scanf() */
#define _CRT_SECURE_NO_WARNINGS




#include <stdio.h>
#include <stdlib.h>
#include <math.h>




/* Constans */
/* User choices. */
#define CHOICE_EVALUATE '1'
#define CHOICE_QUIT     '2'

/* Term coeficients for the maclaurin series: f(t) = t  -  0.5(t^2)  -  1/3(t^3)  +  5/24(t^4)  -  1/30(t^5) */
#define T1_COEFF (1.0)
#define T2_COEFF (-1.0 / 2.0)
#define T3_COEFF (-1.0 / 3.0)
#define T4_COEFF (5.0 / 24.0)
#define T5_COEFF (-1.0 / 30.0)


/* Function prototypes. */
void printMenu(void);

void evaluateSeries(void);

double evaluateSeries0(double t);
double evaluateSeries1(double t);
double evaluateSeries2(double t);
double evaluateSeries3(double t);
double evaluateSeries4(double t);
double evaluateSeries5(double t);




/******************************************************************************
Function Name:  main
Purpose:        Determine the users choice and call the appropriate function
                based on that choice.
In parameters:  none
Out parameters: SUCCESS: EXIT_SUCCESS
                FAILURE: EXIT_FAILURE
Version:        1.0
Author:         Mark Kaganovsky
******************************************************************************/
int main(void){
	int choice;
	
	choice = '\0';
	while (choice != CHOICE_QUIT){
		/* Print out the menu */
		printMenu();
		
		/* Get the users choice */
		choice = getchar();
		
		/* Skip the rest of the characters until the newline */
		while (getchar() != '\n'){}
		
		/* Determine the users choice */
		switch (choice){
			case CHOICE_EVALUATE: {
				evaluateSeries();
				break;
			}
			
			case CHOICE_QUIT: {
				puts("Quitting...");
				break;
			}
			
			default: {
				puts("Invalid choice.");
				break;
			}
		}
	}
	return EXIT_SUCCESS;
}




/******************************************************************************
Function Name:  printMenu
Purpose:        Simply print out the menu for the user.
In parameters:  none
Out parameters: none
Version:        1.0
Author:         Mark Kaganovsky
******************************************************************************/
void printMenu(void){
	puts("Evaluate the Taylor Series approximation to (1 - exp(-t))*cos(t)\n");
	puts("1: Evaluate the series");
	puts("2: quit\n");
}




/******************************************************************************
Function Name:  evaluateSeries
Purpose:        Get the highest term to evaluate to from the user (1 to 4).

                Get the range (0.0 to 1.0).

                Use the array of function pointers to call the correct function
                which will efficiently evaluate the maclaurin series for that
                term count.

In parameters:  none
Out parameters: none
Version:        1.2
Author:         Mark Kaganovsky
******************************************************************************/
void evaluateSeries(void){
	/* Array of pointers to the evaluateSeriesXXXX() functions. */
	static double(*evaluteSeriesXptr[6])(double t) = { &evaluateSeries0,
	                                                   &evaluateSeries1,
	                                                   &evaluateSeries2,
	                                                   &evaluateSeries3,
	                                                   &evaluateSeries4,
	                                                   &evaluateSeries5};

	/* Calculate the number of cofficients in the 'cofficients' array so that it is
	* very simple to add extra terms and make the Maclaurin series more accurate.
	*/
	static int numTerms = sizeof(evaluteSeriesXptr) / sizeof(evaluteSeriesXptr[0]) - 2;

	int    highestPower;        /* The highest power to compute the maclaurin series to, specified by the user. */
	double range;               /* The range to compute the maclaurin series in. Broken into 10 equal increments. */
	double increment;           /* The increment to go up in when computing the series (range / 10). */
	double t;                   /* The current value of t. */
	double ftseries;            /* F(t) computed using the Maclaurin series. */
	double ftexact;             /* F(t) Exact, computed using c's math library. */
	double relativeExactError;  /* Relative exact error.  100 * (exact_value - series_value) / exact_value */
	double relativeSeriesError; /* Relative series error. 100 * first_truncated_term / series_value */
	double firstTruncatedTerm;  /* The value of the first truncated term. */

	puts("\nEvaluating the series");

	/* Get the highest power. */
	printf("Please enter the highest power of t in the series (1, 2, 3 or 4): ");
	scanf("%d", &highestPower);
	while (getchar() != '\n'){} /* Skip trailing characters. */

	/* Make sure the value for highest power is valid. */
	if (highestPower < 1 || highestPower > numTerms){
		puts("Out of range value for highest power!");
		return;
	}


	/* Get the range of t. */
	printf("\nPlease enter the range of t to evaluate in 10 increments( 0.0 < t < +1.0): ");
	scanf("%lf", &range);
	while (getchar() != '\n'){} /* Skip trailing characters. */

	/* Make sure the value for range is valid. */
	if (range < 0.0 || range > 1.0){
		puts("Out of range value for range!");
		return;
	}
	
	/* Evalute and print out the maclaurin series. */
	puts("\nMACLAURIN SERIES");
	puts("  t          F(t) Series     F(t) Exact        %RExactE          %RSerE");

	increment = range / 10.0;
	for (t = 0.0; t < range; t += increment){
		/* Compute F(t) using the maclaurin series. */
		ftseries = (*evaluteSeriesXptr[highestPower])(t);

		/* Compute the exact value (or at least a much more accurate value) of F(t) using c's math library. */
		ftexact = (1 - exp(-t)) * cos(t);

		/* Calculate the relative exact error. */
		relativeExactError = (ftexact == 0.0) ? 0.0 : 100.0 * (ftexact - ftseries) / ftexact;

		/* Calculate the relative series error. */
		if (ftseries == 0){
			relativeSeriesError = 0.0;
		}
		else{
			firstTruncatedTerm = (*evaluteSeriesXptr[highestPower+1])(t) - ftseries;
			relativeSeriesError = 100.0 * firstTruncatedTerm / ftseries;
		}

		/* Print out the results. */
		printf("%.3e   %.5e   %.5e     %.5e   %.5e\n", t, ftseries, ftexact, relativeExactError, relativeSeriesError);
	}
	putchar('\n');
}




/******************************************************************************
Function Name:  evaluateSeries0
Purpose:        To evaluate the maclaurin series using 0 term precision.
In parameters:  double t - The x-axis value to evaluate the series for.
Out parameters: The value of the series at 't' (always 0).
Version:        1.0
Author:         Mark Kaganovsky
******************************************************************************/
double evaluateSeries0(double t){
	return 0;
}




/******************************************************************************
Function Name:  evaluateSeries1
Purpose:        To evaluate the maclaurin series using 1 term precision.
In parameters:  double t - The x-axis value to evaluate the series for.
Out parameters: The value of the series at 't' (same value as t).
Version:        1.0
Author:         Mark Kaganovsky
******************************************************************************/
double evaluateSeries1(double t){
	return t;
}




/******************************************************************************
Function Name:  evaluateSeries2
Purpose:        To evaluate the maclaurin series using 2 term precision.
In parameters:  double t - The x-axis value to evaluate the series for.
Out parameters: The value of the series at 't'.
Version:        1.0
Author:         Mark Kaganovsky
******************************************************************************/
double evaluateSeries2(double t){
	return t*(T1_COEFF    +    t * T2_COEFF);
}




/******************************************************************************
Function Name:  evaluateSeries3
Purpose:        To evaluate the maclaurin series using 3 term precision.
In parameters:  double t - The x-axis value to evaluate the series for.
Out parameters: The value of the series at 't'.
Version:        1.0
Author:         Mark Kaganovsky
******************************************************************************/
double evaluateSeries3(double t){
	return t*(T1_COEFF + t*(T2_COEFF + t * T3_COEFF));
}




/******************************************************************************
Function Name:  evaluateSeries4
Purpose:        To evaluate the maclaurin series using 4 term precision.
In parameters:  double t - The x-axis value to evaluate the series for.
Out parameters: The value of the series at 't'.
Version:        1.0
Author:         Mark Kaganovsky
******************************************************************************/
double evaluateSeries4(double t){
	return t*(T1_COEFF    +    t*(T2_COEFF    +    t*(T3_COEFF    +    t * T4_COEFF)));
}




/******************************************************************************
Function Name:  evaluateSeries5
Purpose:        To evaluate the maclaurin series using 5 term precision.
In parameters:  double t - The x-axis value to evaluate the series for.
Out parameters: The value of the series at 't'.
Version:        1.0
Author:         Mark Kaganovsky
******************************************************************************/
double evaluateSeries5(double t){
	return t*(T1_COEFF    +    t*(T2_COEFF    +    t*(T3_COEFF    +    t*(T4_COEFF    +    t*T5_COEFF))));
}
