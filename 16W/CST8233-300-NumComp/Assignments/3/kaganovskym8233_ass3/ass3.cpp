/******************************************************************************
Filename:           ass3.cpp
Version:            1.0
Author:             Mark Kaganovsky
Student No:         040789903
Course Name/Number: Numerical Computing  CST8233
Lab Sect:           302
Assignment #:       3
Assignment name:    Population Dynamics with Harvesting.
Due Date:           17 Sunday April 2016
Submission Date:    15 Friday April 2016
Professor:          Andrew Tyler
Purpose:            Model population dynamics with harvesting.
******************************************************************************/
#include <Windows.h>

#include <iostream>
#include <limits>
#include <conio.h>


using namespace std;




/******************************************************************************
Function Name:  main

Purpose:        Recieve initial values for the equation:
                    dP/dt = rP(1-P/K) – hP
                
                Then loop forever calculating the new population using the
                following equation:
                    P = P + dP/dt * ^t
                Where ^t represents delta t, or the change in time.
                
                The user can, at any time, press some buttons on the keyboard
                to increase/reduce one of the constants in the first equation.
                
In parameters:  none
Out parameters: int - EXIT_SUCCESS
Version:        1.5
Author:         Mark Kaganovsky
******************************************************************************/
int main(void){
	char *clearScreenCommand = "cls"; /* The command to clear the terminal screen. "cls" for windows, "clear" for unix. */

	int choice;

	/* dP/dt = rP(1-P/K) – hP */
	double dPdt = 0.0; /* (dP/dt) - The instantaneous population growth rate (as an increase per year) */
	double P    = 0.0; /* The total current population */
	double r    = 0.0; /* The natural reproductive increase rate (as a fractional increase per year). */
	double K    = 0.0; /* The population carrying capacity (maximum population the environment can support). */
	double h    = 0.0; /* The harvesting rate – rate at which the population is culled (as a fractional loss per year). */

	/* Get the users choice of whether to run the simulation or quit. */
	while (1){
		puts("Population Simulation");
		puts("1. Run the Simulation");
		puts("2. Quit");
		cin >> choice;

		/* Skip remaining chars in buffer. */
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		if (!cin.good()) { continue; } /* User entered illegal input. */

		if (1 == choice) { break; } /* User wants to run the simulation. */
		
		if (2 == choice){ exit(EXIT_SUCCESS); } /* User chose to quit. */

		/* User entered out of range choice. */
		puts("Invalid choice.\n");
	}
	
	/* Get the simulation parameters. */
	puts("ENTER SIMULATION PARAMETERS");

	/* Get the initial population. */
	printf("Initial population (typically 900000)? ");
	cin >> P;

	/* Get the maximum population. */
	printf("Maximum population the environment can support (typically 1000000)? ");
	cin >> K;

	/* Get the initial harvesting rate. */
	printf("Initial harvesting rate (fraction per year - 0 for no harvesting)? ");
	cin >> h;

	/* Get the natural fractional growth. */
	printf("Natural fractional growth population rate (typically 0.2 per year)? ");
	cin >> r;

	system(clearScreenCommand);

	bool running = true; /* Set to false when 'q' is pressed. */

	char *statusString = "starting simulation"; /* Effect of the last pressed button on the keyboard (ex: 'w' = "w was pressed - increase harvesting"). */

	unsigned int startTime; /* Start time of the simulation. */
	unsigned int oldTime;
	unsigned int newTime;

	startTime = GetTickCount();
	oldTime   = GetTickCount() - startTime;
	while(running){
		newTime=GetTickCount()-startTime;

		/* Check if enough time has passed. */
		if (newTime == oldTime){ continue; }

		system(clearScreenCommand);

		/* Print out simulation run times. */
		puts(statusString);
		printf("Simulation run time minute = %u; second = %u; millisec = %u\n", newTime/(1000*60), newTime/1000, newTime%1000);
		puts("*****************************************************************");
		printf("Year of simulation = %u\n", newTime/1000);

		/* Calculate population growth rate. */
		if (0.0 == K) { K = DBL_MIN; } /* If K is 0.0, prevent division by 0. */
		dPdt = (r*P*(1 - P/K) - h*P);
		printf("Rate of population change = %.6f\n", dPdt);

		/* Add population growth rate to population. */
		P += dPdt * (double)(newTime-oldTime)/1000.0; /* dPdt * deltat */
		if (P < 0.0) { P = 0.0; }

		/* Print out the new population. */
		printf("Population = %.0f\n", P);
		puts("*****************************************************************");

		/* Print out harvesting rate, max population, and growth rate. */
		puts("Press w / e to increase / decrease harvesting rate.");
		printf("Current harvesting rate : %.6f\n", h);

		puts("Press p / o to increase / decrease Max population supported.");
		printf("Current Max population : %.0f\n", K);
		
		puts("Press k / l to increase / decrease growth rate.");
		printf("Current growth rate : %.6f\n",r);
		
		puts("Press q to quit.");
		
		/* Check if the keyboard was pressed. */
		if (_kbhit()){
			/* Check if one of the increase/decrease keys was pressed. */
			switch (_getch()){
				/* Increase / decrease harvesting rate. */
				case 'w':
					h += 0.01;
					statusString = "w was pressed - increase harvesting";
					break;
				case 'e':
					h -= 0.01;
					statusString = "e was pressed - reduce harvesting";
					break;
				
				/* Increase / decrease max population */
				case 'p':
					K += 1000.0;
					statusString = "p was pressed - increase Max population supported";
					break;
				case 'o':
					K -= 1000.0;
					statusString = "o was pressed - reduce Max population supported";
					break;
				
				/* Increase / decrease growth rate. */
				case 'k':
					if (r > 1.0){ r += 1.01; }
					else        { r += 0.01; }
					statusString = "k was pressed - increase growth rate";
					break;
				case 'l':
					r -= 0.01;
					statusString = "l was pressed - reduce growth rate";
					break;
				
				/* Quit */
				case 'q':
					running = false;
					break;
			}
			
			/* Make sure all constants are in valid ranges. */
			if (h <= 0.0)     { h = 0.0; }
			else if (h >= 1.0){ h = 1.0; }

			if (K <= 0.0) { K = 0.0; }

			if (r <= 0.0) { r = 0.0; }
		}
		oldTime=newTime;
	}

	return EXIT_SUCCESS;
}
