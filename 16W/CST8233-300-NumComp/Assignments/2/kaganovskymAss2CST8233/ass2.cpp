/******************************************************************************
Filename:           ass2.cpp
Version:            1.0
Author:             Mark Kaganovsky
Student No:         040789903
Course Name/Number: Numerical Computing  CST8233
Lab Sect:           302
Assignment #:       2
Assignment name:    Moore's Law
Due Date:           March 20 2016
Submission Date:    March 17 2016
Professor:          Andrew Tyler
Purpose:            To interpolate and extrapolate transistor counts and the
                    rate of change of transistor counts in CPUs.
******************************************************************************/




#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>




#include <string>
#include <fstream>
#include <iostream>




using namespace std;




/* Functions. */
void doLinearRegression(void);




/******************************************************************************
Function Name:  main
Purpose:        Get the users choice, either quit or call the function to
                perform the linear regression.
In parameters:  none
Out parameters: EXIT_SUCCESS
Version:        1.0
Author:         Mark Kaganovsky
******************************************************************************/
int main(void){
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	const int CHOICE_OPEN_FILE = 1;
	const int CHOICE_QUIT      = 2;

	int choice;

	for (choice=-1; choice != CHOICE_QUIT;){
		/* Print menu. */
		cout << "*******************************************************" << endl;
		cout << " Exponential fit by Linear Regression" << endl;
		cout << "1. Read Data from File" << endl;
		cout << "2. Quit" << endl;
		cout << "*******************************************************" << endl;
		cout << "Select an option: ";

		/* Get users choice. */
		choice = -1;
		cin >> choice;

		/* Skip the rest of the data in the stream. */
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		/* Do what the user asks. */
		switch (choice){
			case CHOICE_OPEN_FILE:
				doLinearRegression();
				break;

			case CHOICE_QUIT:
				break;

			default:
				cout << "Invalid choice." << endl;
		}
	}
	
	system("pause");

	return EXIT_SUCCESS;
}




/******************************************************************************
Function Name:  doLinearRegression
Purpose:        Prompt the user for the file name, read that file and calulate
                the values a and c in the function y = a*exp(c*x), then asks
                the user what kind of interpolation/extrapolation they want to
                do.
In parameters:  none
Out parameters: none
Version:        1.3
Author:         Mark Kaganovsky
******************************************************************************/
void doLinearRegression(void){
	/* Get file path. */
	string filePath;
	cout << "please enter the name of the file to open: ";
	getline(cin, filePath);
	
	/* Attempt to open file. */
	ifstream fileReader(filePath);
	if (!fileReader.is_open()){
		cout << "ERROR: Could not open file '" << filePath << "' for reading." << endl;
		return;
	}

	/* File opened. */
	cout << endl << endl << "FILE OPENED FOR READING" << endl;

	/* Find out how many records there are. */
	int numRecords = 0;
	{
		char temp;
		for (fileReader.get(temp); !fileReader.eof(); fileReader.get(temp)){
			if ('\n' == temp){
				++numRecords;
			}
		}
	}

	cout << "There are " << numRecords << " records." << endl << endl;
	printf("%-32s%-16s%s\n", "NAME", "YEAR", "COUNT");

	/* Rewind stream to the start. */
	fileReader.clear();
	fileReader.seekg(0);

	double a;
	double c;
	double year;
	{
		double sumx  = 0; /* E(x) */
		double sumy  = 0; /* E(y) */
		double sumxy = 0; /* E(xy) */
		double sumx2 = 0; /* E(x^2) */
		double sumy2 = 0; /* E(y^2) */

		string name;
		double transistorCount;

		while (fileReader >> name >> year >> transistorCount){
			printf("%-32s%-16.0f%g\n",name.c_str(),year + 1970,transistorCount);

			transistorCount = log(transistorCount);

			sumx += year;
			sumy += transistorCount;
			sumxy += year*transistorCount;
			sumx2 += year*year;
			sumy2 += transistorCount*transistorCount;
		}

		/* Calculate a and c. */
		a = exp((sumy*sumx2 - sumx*sumxy) / (numRecords*sumx2 - sumx*sumx));
		c = (numRecords*sumxy - sumx*sumy) / (numRecords*sumx2 - sumx*sumx);
	}

	cout << endl << "File read into memory" << endl << endl;
	cout << "EXPONENTIAL FUNCTION" << endl;
	cout << "Fit data to exponential:   y = a*exp(c*x)" << endl << endl;
	cout << "EXPONENTIAL:  y = " << a << "*exp(" << c << "*x)" << endl;

	const int CHOICE_TRANS_COUNT     = 1; /* User wants to Interpolation/Extrapolation transistor count. */
	const int CHOICE_ROI_TRANS_COUNT = 2; /* User wants to Interpolation/Extrapolation rate of increase of transistor count. */
	const int CHOICE_QUIT            = 3; /* User wants to quit. */

	/* Keep interpolating and extrapolating until the user quits. */
	for (int choice=-1; choice != 3;){
		/* Print out menu. */
		cout << endl;
		cout << "*******************************************************" << endl;
		cout << "Eponential Interpolation/Extrapolation" << endl;
		cout << "1. Interpolation/Extrapolation of transistor count" << endl;
		cout << "2. Interpolation/Extrapolation of rate of increase of transistor count" << endl;
		cout << "3. Quit Interpolation/Extrapolation" << endl;
		cout << "*******************************************************" << endl;
		cout << "Select an option: ";

		/* Get users choice. */
		cin >> choice;

		/* Clear the rest of the data in the stream. */
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (choice){
			case CHOICE_TRANS_COUNT:
				cout << "Interpolation/Extrapolation of transistor count" << endl;
				cout << "Please enter the year(e.g. 2005) : ";
				cin >> year;

				/* Clear the rest of the data in the stream. */
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << "transistor count at " << year << " = " << a*exp(c*(year-1970)) << endl;
				break;
			
			case CHOICE_ROI_TRANS_COUNT:
				cout << "2. Interpolation/Extrapolation of rate of increase of transistor count" << endl;
				cout << "Please enter the year(e.g. 2005) : ";
				cin >> year;

				/* Clear the rest of the data in the stream. */
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << "rate of increase at " << year << " = " << c*a*exp(c*(year-1970)) << " per year" << endl;
				break;
			
			case CHOICE_QUIT:
				cout << endl;
				break;
			
			/* Invalid choice. */
			default:
				cout << "ERROR: Choice is not valid." << endl;
		}
	}
}
