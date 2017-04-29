#include <iostream>
using namespace std;

#include "ClubMember.h"
#include "Player.h"




Player::Player() : ClubMember(){
	p = -1;
}




Player::Player(char *fname, char* lname, double sub, int pos) : ClubMember(fname, lname, sub){
	p = pos;
}




Player::Player(Player &toCopy) : ClubMember(toCopy){
	p = toCopy.p;
}




Player::~Player(){
	p = -1;
}




bool Player::operator==(Player &toCompare){
	return p == toCompare.p;
}




void Player::Output(){
	cout << "Player" << endl;
	
	ClubMember::Output();

	/* Print out the player's position. */
	cout << "Position = ";
	switch (p){
		case 0:
			cout << "Goalkeeper";
			break;

		case 1:
			cout << "left-back";
			break;
		
		case 2:
			cout << "right-back";
			break;
		
		case 3:
			cout << "centre-back";
			break;
		
		case 4:
			cout << "left-midfield";
			break;
		
		case 5:
			cout << "right-midfield";
			break;
		
		case 6:
			cout << "centre-midfield";
			break;
		
		case 7:
			cout << "centre-forward";
			break;
		
		default: 
			cout << "UNKNOWN POSITION";
	}
	cout << " (" << p << ")" << endl;
}