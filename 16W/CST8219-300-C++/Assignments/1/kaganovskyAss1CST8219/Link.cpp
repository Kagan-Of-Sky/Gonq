/**************************************************************************************
File Name:          Link.cpp
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
Purpose:            This class represents a single link in the SoccerClub's linked list.
                    It contains a pointer to the next link, the previous link, and a
                    pointer to a Player object.
**************************************************************************************/




#include "Player.h"
#include "Link.h"




/**************************************************************************************
Function Name:  Link

Purpose:        Constructor.

In Parameters:  Link *prev:     The Link before this one.
                Link *next:     The Link after this one.
                Player *player: The Player which this Link contains.

Out Parameters: none
Version:        1.0
Author:         Mark Kaganovsky
**************************************************************************************/
Link::Link(Link *prev, Link *next, Player *player){
	this->pPrev   = prev;
	this->pNext   = next;
	this->pPlayer = player;
}




/**************************************************************************************
Function Name:  ~Link

Purpose:        Destructor. Deletes the Player object that this Link points to.

In Parameters:  none
Out Parameters: none
Version:        1.0
Author:         Mark Kaganovsky
**************************************************************************************/
Link::~Link(){
	delete pPlayer;
}
