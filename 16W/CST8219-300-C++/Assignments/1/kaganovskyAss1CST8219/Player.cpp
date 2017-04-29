/**************************************************************************************
File Name:          Player.cpp
Version:            1.0
Student Name:       Mark Kaganovsky
Student Number:     040 789 903
Course:             C++ Programming CST8219
Lab Section:        302
Assignment Number:  1
Assignment Name:    Soccer Club
Due Date:           20 Feb 2016 @ Midnight
Submission Date:    20 Feb 2016
Professor Name:     Andrew Tyler
Purpose:            This class represents a single player on the soccer club.
                    It contains the players first name, the players last name, and the
                    players subscription.
**************************************************************************************/




#include "Player.h"




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
}




/**************************************************************************************
Function Name:  Player

Purpose:        Overloaded constructor.

In Parameters:  char *firstName:     A null terminated c-string.
                char *lastName:      A null terminated c-string.
                double subscription: This players subscrption.

Out Parameters: none
Version:        1.0
Author:         Mark Kaganovsky
**************************************************************************************/
Player::Player(char *firstName, char *lastName, double subscription){
	this->firstName    = firstName;
	this->lastName     = lastName;
	this->subscription = subscription;
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
