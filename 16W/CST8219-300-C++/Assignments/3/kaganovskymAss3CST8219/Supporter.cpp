#include <iostream>
using namespace std;

#include "ClubMember.h"
#include "Supporter.h"




Supporter::Supporter() : ClubMember(){
	fixtures    = nullptr;
	numFixtures = 0;
}




Supporter::Supporter(char *fname, char* lname, double sub, Date *fixtures, unsigned int numFixtures) : ClubMember(fname, lname, sub){
	this->fixtures    = fixtures;
	this->numFixtures = numFixtures;
}




Supporter::Supporter(Supporter &toCopy) : ClubMember(toCopy){
	numFixtures = toCopy.numFixtures;

	fixtures = new Date[numFixtures];

	memcpy(fixtures, toCopy.fixtures, toCopy.numFixtures);
}




Supporter::~Supporter(){
	delete [] fixtures;
}




void Supporter::Output(){
	cout << "Supporter" << endl;

	ClubMember::Output();

	for (unsigned int i = 0; i < numFixtures; ++i){
		cout << "fixtures [" << i << "] = " << fixtures[i].day << "/" << fixtures[i].month << "/" << fixtures[i].year << endl;
	}
}