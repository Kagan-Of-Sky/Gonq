/**************************************************************************************
File Name:          SoccerClub.cpp
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
Purpose:            This class maintains a doubly linked list of soccer club members.
**************************************************************************************/




#include <iostream>
#include <iomanip>
#include <string.h>

#include "Player.h"
#include "Link.h"
#include "SoccerClub.h"




using namespace std;




/**************************************************************************************
Function Name:  SoccerClub

Purpose:        Default constructor, creates a new SoccerClub object with 0 players.

In Parameters:  none
Out Parameters: none
Version:        1.0
Author:         Mark Kaganovsky
**************************************************************************************/
SoccerClub::SoccerClub(){
	pPlayers = nullptr;
}




/**************************************************************************************
Function Name:  ~SoccerClub

Purpose:        Destructor, deletes all allocated memory for this SoccerClub object.

In Parameters:  none
Out Parameters: none
Version:        1.0
Author:         Mark Kaganovsky
**************************************************************************************/
SoccerClub::~SoccerClub(){
	if (pPlayers != nullptr){ /* At least 1 player. */
		Link *toDelete = pPlayers;
		
		while (pPlayers->pNext != nullptr){
			toDelete = pPlayers;
			pPlayers = pPlayers->pNext;
			delete toDelete;
		}
		delete pPlayers;
	}
}




/**************************************************************************************
Function Name:  AddPlayer

Purpose:        Adds a new player to the head of the SoccerClub's linked list.
                  1. Prompts user for first name
                  2. Prompts user for last name
                  3. Prompts user for subsription
                  4. Adds the new player to the head of the linked list.

In Parameters:  none
Out Parameters: none
Version:        1.3
Author:         Mark Kaganovsky
**************************************************************************************/
void SoccerClub::AddPlayer(){
	const int FNAME_BUF_SIZE = 50; /* The buffer size for the first name. */
	const int LNAME_BUF_SIZE = 50; /* The buffer size for the last name. */

	Player *newPlayer;
	Link   *newLink;

	char   *firstName;
	char   *lastName;
	double subscription;

	cout << "ADDING AN PLAYER" << endl;

	/* Allocate memory for the first and last name. */
	firstName = new char[FNAME_BUF_SIZE];
	lastName  = new char[LNAME_BUF_SIZE];

	/* Ignore all characters that are currently in the input stream. */
	cin.ignore(numeric_limits<streamsize>::max(), '\n');


	/* Read in the player's first name. */
	cout << "Please enter the Player first name: ";
	cin.getline(firstName, FNAME_BUF_SIZE, '\n');
	if (firstName[strlen(firstName) - 1] == '\n'){
		firstName[strlen(firstName) - 1] = '\0';
	}
	/* Check if the string entered was too long. */
	if (cin.fail()){
		cout << "ERROR: String too long, truncating..." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}


	/* Read in the player's last name. */
	cout << "Please enter the Player last name: ";
	cin.getline(lastName, LNAME_BUF_SIZE, '\n');
	if (lastName[strlen(lastName) - 1] == '\n'){
		lastName[strlen(lastName) - 1] = '\0';
	}
	/* Check if the string entered was too long. */
	if (cin.fail()){
		cout << "ERROR: String too long, truncating..." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}


	/* Read in the player's subscription. */
	while (true){
		cout << "Please enter the Player subscription: ";
		cin >> subscription;

		/* Check if valid input. */
		if (cin.good()){
			break;
		}
		else{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "ERROR: Invalid input." << endl;
			continue;
		}
	}
	/* Ignore whatever else is left in the stream. */
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	

	/* Allocate memory for the Link and Player. */
	newPlayer = new Player(firstName, lastName, subscription);
	newLink   = new Link(nullptr, pPlayers, newPlayer);

	/* Update the current head of the linked list. */
	if (pPlayers != nullptr){
		pPlayers->pPrev = newLink;
	}
	pPlayers = newLink;
}




/**************************************************************************************
Function Name:  DeletePlayer

Purpose:        Deletes the player at the head of the linked list.

In Parameters:  none
Out Parameters: none
Version:        1.1
Author:         Mark Kaganovsky
**************************************************************************************/
void SoccerClub::DeletePlayer(){
	Link *toDelete;

	cout << "DELETE A PLAYER" << endl;
	

	/* Make sure that there is at least 1 link in the list. */
	if (pPlayers == nullptr){
		cout << "No players" << endl;
		return;
	}

	/* Remove the head element from the list. */
	toDelete = pPlayers;
	pPlayers = pPlayers->pNext;
	if (pPlayers != nullptr){      /* Update previous pointer if needed. */
		pPlayers->pPrev = nullptr;
	}

	/* Free the memory associated with this link. */
	delete toDelete;

	cout << "Player deleted" << endl;
}




/**************************************************************************************
Function Name:  PrintPlayersForward

Purpose:        Prints out the players in the linked list starting from the head.

In Parameters:  none
Out Parameters: none
Version:        1.1
Author:         Mark Kaganovsky
**************************************************************************************/
void SoccerClub::PrintPlayersForward(){
	Link *current;
	int playerNumber;

	cout << "FORWARD PRINTING PLAYERS" << endl;
	current = pPlayers;

	/* Make sure that there is at least one person on the team. */
	if (current == nullptr){
		cout << "No players" << endl;
		return;
	}

	/* Print the data for each player in the linked list. */
	playerNumber = 1;
	while (current != nullptr){
		cout << "Player " << playerNumber << endl;
		cout << "first name = " << current->pPlayer->getFirstName() << ";" << endl;
		cout << "last name = " << current->pPlayer->getLastName() << ";" << endl;
		cout << "subscription = " << fixed << setprecision(2) << current->pPlayer->getSubscription() << ";" << endl;

		current = current->pNext;
		++playerNumber;
	}
}




/**************************************************************************************
Function Name:  PrintPlayersReverse

Purpose:        Prints out the players in the linked list starting from the tail.

In Parameters:  none
Out Parameters: none
Version:        1.1
Author:         Mark Kaganovsky
**************************************************************************************/
void SoccerClub::PrintPlayersReverse(){
	Link *current;
	int playerNumber;

	current = pPlayers;

	cout << "REVERSE PRINTING PLAYERS" << endl;

	/* Make sure that there is at least one player in the list. */
	if (current == nullptr){
		cout << "No players" << endl;
		return;
	}

	/* Follow the linked list to the end. */
	playerNumber = 1;
	while (current->pNext != nullptr){
		current = current->pNext;
		++playerNumber;
	}

	/* Now that we are at the tail we can go backwards. */
	while (current != nullptr){
		cout << "Player " << playerNumber << endl;
		cout << "first name = " << current->pPlayer->getFirstName() << ";" << endl;
		cout << "last name = " << current->pPlayer->getLastName() << ";" << endl;
		cout << "subscription = " << fixed << setprecision(2) << current->pPlayer->getSubscription() << ";" << endl;

		current = current->pPrev;
		--playerNumber;
	}
}
