/**************************************************************************************
File Name:          SoccerClub.cpp
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
Purpose:            This class maintains a doubly linked list of soccer club members,
                    and provides methods to access them.
**************************************************************************************/




#include <iostream>
#include <iomanip>
#include <string.h>

using namespace std;

#include "Player.h"
#include "Link.h"
#include "SoccerClub.h"




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
	int    position;

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
	
	/* Read in the players position. */
	position = -1;
	while (position < 0 || position > 7){
		cout << "Please enter the Player position: " << endl;
		cout << "Goalkeeper = 0" << endl;
		cout << "left-back = 1" << endl;
		cout << "right-back = 2" << endl;
		cout << "centre-back = 3" << endl;
		cout << "left-midfield = 4" << endl;
		cout << "right-midfield = 5" << endl;
		cout << "centre-midfield = 6" << endl;
		cout << "centre-forward = 7" << endl;
		
		cin >> position;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	/* Allocate memory for the Link and Player. */
	newPlayer = new Player(firstName, lastName, subscription, position);
	newLink   = new Link(nullptr, pPlayers, newPlayer);

	/* Update the current head of the linked list. */
	if (pPlayers){
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
	if (!pPlayers){
		cout << "No players" << endl;
		return;
	}

	/* Remove the head element from the list. */
	toDelete = pPlayers;
	pPlayers = pPlayers->pNext;
	if (pPlayers){      /* Update previous pointer if needed. */
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
	if (!current){
		cout << "No players" << endl;
		return;
	}

	/* Print the data for each player in the linked list. */
	for (playerNumber=0;    current;    current=current->pNext, ++playerNumber){
		cout << "Player " << playerNumber << endl;
		current->pPlayer->Print();
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
	if (!current){
		cout << "No players" << endl;
		return;
	}

	/* Follow the linked list to the end. */
	for (playerNumber=0;  current->pNext;  current=current->pNext, ++playerNumber){
		// No body
	}

	/* Now that we are at the tail we can go backwards. */
	for (; current; current=current->pPrev, --playerNumber){
		cout << "Player " << playerNumber << endl;
		current->pPlayer->Print();
	}
}




/**************************************************************************************
Function Name:  operator[]
Purpose:        Retrieve a player from a specific index.
In Parameters:  int - index of the player you want.
Out Parameters: A pointer to the player object.
Version:        1.0
Author:         Mark Kaganovsky
**************************************************************************************/
Player* SoccerClub::operator[](unsigned int index){
	Link *current;

	/* Index out of range. */
	if (index < 0){
		return nullptr;
	}

	for (current=pPlayers; index && current; --index, current=current->pNext){
		/* No body. */
	}

	/* Found Player. */
	if (!index && current){
		return current->pPlayer;
	}

	/* Did not find Player. */
	return nullptr;
}




/**************************************************************************************
Function Name:  FindPlayer
Purpose:        Find a player who plays a particular position.
In Parameters:  none
Out Parameters: none
Version:        1.0
Author:         Mark Kaganovsky
**************************************************************************************/
void SoccerClub::FindPlayer(){
	int position;

	/* Read in the players position. */
	while (true){
		cout << "Please enter the position you are searching for: ";
		
		cin >> position;

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

	/* Search for the player. */
	Player toFind(nullptr, nullptr, 0.0, position);
	Link *current;
	for (current=pPlayers; current && !(*(current->pPlayer) == toFind); current=current->pNext){
		// No body.
	}

	if (current){ /* Found Player. */
		cout << "position found" << endl;
		current->pPlayer->Print();
	}
	else{ /* Did not find player. */
		cout << "position not found" << endl;
	}
}




/**************************************************************************************
Function Name:  operator<<
Purpose:        Print out the soccer clubs members starting at the head of the list.

In Parameters:  ostream    &stream - The stream to print to.
                SoccerClub &sc     - The soccer club to print out.

Out Parameters: ostream& - A reference to the same ostream passed to this function, to
                           allow chaining.

Version:        1.1
Author:         Mark Kaganovsky
**************************************************************************************/
ostream& operator<<(ostream &stream, SoccerClub &sc){
	Link *current;
	int playerNumber;

	stream << "FORWARD PRINTING PLAYERS" << endl;
	current = sc.pPlayers;

	/* Make sure that there is at least one person on the team. */
	if (!current){
		stream << "No players" << endl;
		return stream;
	}

	/* Print the data for each player in the linked list. */
	for (playerNumber=0;    current;    current=current->pNext, ++playerNumber){
		stream << "Player " << playerNumber << endl;
		current->pPlayer->Print();
	}
	return stream;
}
