#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

#include <string.h>

#include "ClubMember.h"




ClubMember::ClubMember(){
	firstName    = "! UNINITIALIZED FIRST NAME !";
	lastName     = "! UNINITIALIZED LAST  NAME !";
	subscription = -1.0;
}




ClubMember::ClubMember(char *fname, char* lname, double sub){
	firstName    = fname;
	lastName     = lname;
	subscription = sub;
}




ClubMember::ClubMember(ClubMember &toCopy){
	/* Copy the first name. */
	firstName = new char[strlen(toCopy.firstName) + 1];
	strcpy(firstName, toCopy.firstName);

	/* Copy the last name. */
	lastName = new char[strlen(toCopy.lastName) + 1];
	strcpy(lastName, toCopy.lastName);

	/* Copy subscription. */
	subscription = toCopy.subscription;
}




ClubMember::~ClubMember(){
	delete [] firstName;
	delete [] lastName;
}




void ClubMember::Output(){
	cout << firstName << " " << lastName << endl;
	cout << "Subscription = " << subscription << endl;
}