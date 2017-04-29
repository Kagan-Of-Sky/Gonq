/**************************************************************************************
File Name:          Player.cpp
Version:            1.2
Student Name:       Mark Kaganovsky
Student Number:     040 789 903
Course:             C++ Programming CST8219
Lab Section:        302
Assignment Number:  2
Assignment Name:    Soccer Club with overloaded operators.
Due Date:           March 20 2016
Submission Date:    March 19 2016
Professor Name:     Andrew Tyler
Purpose:            This class represents a single player on the soccer club.
                    It contains the players first name, the players last name, and the
                    players subscription.
**************************************************************************************/




#define _CRT_SECURE_NO_WARNINGS /* Supress warnings about strcpy(). */




#include <iostream>
#include <string.h>

#include "Player.h"




using namespace std;




/**************************************************************************************
Function Name:  Player

Purpose:        Default constructor.
                Sets firstName to "Unknown First Name"
                Sets lastName to "Unknown Last Name"
                Sets subscription to 0.0

In Parameters:  none
Out Parameters: none
Version:        1.0
Author:         Mark Kaganovsky
**************************************************************************************/
Player::Player(){
	firstName    = "Unknown First Name";
	lastName     = "Unknown Last Name";
	subscription = 0.0;
	p            = 0;
}




/**************************************************************************************
Function Name:  Player
Purpose:        Overloaded constructor.

In Parameters:  char *firstName:     A null terminated c-string.
                char *lastName:      A null terminated c-string.
                double subscription: This players subscription.
                int position:        The position this player plays.

Out Parameters: none
Version:        1.2
Author:         Mark Kaganovsky
**************************************************************************************/
Player::Player(char *firstName, char *lastName, double subscription, int position){
	this->firstName    = firstName;
	this->lastName     = lastName;
	this->subscription = subscription;
	p = position;
}




/**************************************************************************************
Function Name:  Player

Purpose:        Deep copy constructor.

In Parameters:  Player &player - Reference to a Player object.

Out Parameters: nonw

Version:        1.1
Author:         Mark Kaganovsky
**************************************************************************************/
Player::Player(Player &player){
	/* Copy first name. */
	firstName = new char[strlen(player.firstName) + 1];
	strcpy(firstName, player.firstName);

	/* Copy last name. */
	lastName = new char[strlen(player.lastName) + 1];
	strcpy(lastName, player.lastName);

	/* Copy subscription and position. */
	subscription = player.subscription;
	p = player.p;
}



/**************************************************************************************
Function Name:  operator ==
Purpose:        Check if the player passed plays the same position.
In Parameters:  Player &player - A referance to a player object.

Out Parameters: 1 - The Player reference passed plays the same position as this Player.
                0 - They do not play the same position.

Version:        1.0
Author:         Mark Kaganovsky
**************************************************************************************/
bool Player::operator==(Player &player){
	return p == player.p;
}




/**************************************************************************************
Function Name:  Print

Purpose:        Print out the last name, first name, subscription and position for a
                single player.

In Parameters:  none
Out Parameters: none
Version:        1.0
Author:         Mark Kaganovsky
**************************************************************************************/
void Player::Print(){
	cout << "Last Name = " << lastName << endl;
	cout << "First Name = " << firstName << endl;
	cout << "Subscription = " << subscription << endl;

	cout << "Position = ";

	switch (p){
		case 0:{
			cout << "Goalkeeper";
			break;
		}
		case 1:{
			cout << "left-back";
			break;
		}
		case 2:{
			cout << "right-back";
			break;
		}
		case 3:{
			cout << "centre-back";
			break;
		}
		case 4:{
			cout << "left-midfield";
			break;
		}
		case 5:{
			cout << "right-midfield";
			break;
		}
		case 6:{
			cout << "centre-midfield";
			break;
		}
		case 7:{
			cout << "centre-forward";
			break;
		}
		default: {
			cout << "UNKNOWN POSITION";
		}
	}

	cout << " (" << p << ")" << endl;
}




/**************************************************************************************
Function Name:  ~Player
Purpose:        Destructor, frees the memory associated with this Player.
In Parameters:  none
Out Parameters: none
Version:        1.1
Author:         Mark Kaganovsky
**************************************************************************************/
Player::~Player(){
	delete [] firstName;
	delete [] lastName;
}
