/**************************************************************************************
File Name:          ass0.c
Version:            1.0
Student Name:       Mark Kaganovsky
Student Number:     040789903
Course:             CST8219 (C++ Programming) + CST8233 (Numerical Computing)
Lab Section:        302
Assignment Number:  0
Assignment Name:    Soccer Club
Due Date:           29 January 2016 @ Midnight
Submission Date:    29 January 2016
Professor Name:     Andrew Tyler
Purpose:            This program maintains a database of players on a soccer team, using
                    a linked list as the data structure. The user can add to this list
                    at the head, delete from the head, print the players starting at the
                    head, and print the players starting from the tail.
 **************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum{ RUNNING = 1 };
struct Player
{
	double  subscription;
	char* firstName;
	char* lastName;
};

struct Link
{
	struct Player* pPlayer;
	struct Link* pNext;          // Link to next object
	struct Link* pPrev;          // Link to previous object
};


void AddPlayer();
void DeletePlayer();
void PrintPlayersForward();
void PrintPlayersReverse();
void CleanUp();

struct Link*	g_pPlayers = 0;

int main()
{
	char response;

	while (RUNNING)
	{
		printf("\nPlease select an option:\n");
		printf("1. Add a Player\n");
		printf("2. Delete a Player\n");
		printf("3. Print out Players\n");
		printf("4. Print out Players in reverse order\n");
		printf("q. Quit\n");
		printf("CHOICE: ");
		fflush(stdin);
		scanf("%c", &response);

		switch (response)
		{
			case '1':AddPlayer(); break;
			case '2':DeletePlayer(); break;
			case '3':PrintPlayersForward(); break;
			case '4':PrintPlayersReverse(); break;
			case 'q':CleanUp(); return 0;
			default:printf("Please enter a valid option\n");
		}
		printf("\n");
	}
}


/**************************************************************************************
Function Name:  AddPlayer

Purpose:        Read a first name, last name, and subscription from stdin, creating
                a new Player and Link which will be added to the head of the linked
                pointed to by g_pPlayers.

In Parameters:  none
Out Parameters: none
Version:        1.0
Author:         Mark Kaganovsky
**************************************************************************************/
void AddPlayer(){
	struct Link   *newLink;
	struct Player *newPlayer;

	char *firstName;
	char *lastName;

	puts("ADDING AN PLAYER");

	/* Allocate all memory needed for the new player. */
	newLink   = (struct Link *)malloc(sizeof(struct Link));
	newPlayer = (struct Player *)malloc(sizeof(struct Player));
	firstName = (char *)malloc(50);
	lastName = (char *)malloc(50);

	/* Link the allocated memory together. */
	newPlayer->firstName = firstName;
	newPlayer->lastName  = lastName;
	newLink->pPlayer     = newPlayer;
	newLink->pPrev       = NULL;

	/* Add the new player at the start of the list. */
	newLink->pNext = g_pPlayers;
	if (g_pPlayers != NULL){ /* At least one element in the list. */
		g_pPlayers->pPrev = newLink;
	}
	g_pPlayers = newLink;

	/* Read in the player's first name. */
	fflush(stdin);
	printf("Please enter the Player first name: ");
	fgets(firstName, 50, stdin);
	if (firstName[strlen(firstName)-1] == '\n'){
		firstName[strlen(firstName)-1] = '\0';
	}
	
	/* Read in the player's last name. */
	fflush(stdin);
	printf("Please enter the Player last name: ");
	fgets(lastName, 50, stdin);
	if (lastName[strlen(lastName) - 1] == '\n'){
		lastName[strlen(lastName) - 1] = '\0';
	}

	/* Read in the player's subscription. */
	printf("Please enter the Player subscription: ");
	scanf("%lf", &(newPlayer->subscription));
	fflush(stdin);
}

/**************************************************************************************
Function Name:  DeletePlayer

Purpose:        Delete the player at the head of the linked list pointed to by g_pPlayers

In Parameters:  none
Out Parameters: none
Version:        1.0
Author:         Mark Kaganovsky
**************************************************************************************/
void DeletePlayer(){
	struct Link *toDelete;
	
	puts("DELETE A PLAYER");

	/* Make sure that there is at least 1 link in the list. */
	if (g_pPlayers == NULL){
		puts("No players on the team.");
		return;
	}

	/* Remove the head element from the list. */
	toDelete = g_pPlayers;
	g_pPlayers = g_pPlayers->pNext;
	if (g_pPlayers != NULL){
		g_pPlayers->pPrev = NULL;
	}

	/* Free the memory associated with this link. */
	free(toDelete->pPlayer->firstName);
	free(toDelete->pPlayer->lastName);
	free(toDelete->pPlayer);
	free(toDelete);

	puts("Player deleted");
}

/**************************************************************************************
Function Name:  PrintPlayersForward

Purpose:        Print out the players in the linked list pointed to by g_pPlayers,
                starting from the beginning of the list.

In Parameters:  none
Out Parameters: none
Version:        1.0
Author:         Mark Kaganovsky
**************************************************************************************/
void PrintPlayersForward(){
	struct Link *current;
	int playerNumber;

	puts("FORWARD PRINTING PLAYERS");
	current = g_pPlayers;

	/* Make sure that there is at least one person on the team. */
	if (current == NULL){
		puts("No players on the team.");
		return;
	}

	/* Print the data for each player in the linked list. */
	playerNumber = 1;
	while (current != NULL){
		printf("Player %d\n", playerNumber);
		printf("first name = %s;\n", current->pPlayer->firstName);
		printf("last name = %s;\n", current->pPlayer->lastName);
		printf("subscription = %.2f;\n", current->pPlayer->subscription);

		current = current->pNext;
		++playerNumber;
	}
}

/**************************************************************************************
Function Name:  PrintPlayersReverse

Purpose:        Print out the players in the linked list pointed to by g_pPlayers in
                reverse order.

In Parameters:  none
Out Parameters: none
Version:        1.0
Author:         Mark Kaganovsky
**************************************************************************************/
void PrintPlayersReverse(){
	struct Link *current;
	int playerNumber;

	current = g_pPlayers;
	
	puts("REVERSE PRINTING PLAYERS");

	/* Make sure that there is at least one player in the list. */
	if (current == NULL){
		puts("No players on the team.");
		return;
	}

	/* Follow the linked list to the end. */
	playerNumber = 1;
	while (current->pNext != NULL){
		current = current->pNext;
		++playerNumber;
	}

	/* Now that we are at the tail we can go backwards. */
	while (current != NULL){
		printf("Player %d\n", playerNumber);
		printf("first name = %s;\n", current->pPlayer->firstName);
		printf("last name = %s;\n", current->pPlayer->lastName);
		printf("subscription = %.2f;\n", current->pPlayer->subscription);

		current = current->pPrev;
		--playerNumber;
	}
}

/**************************************************************************************
Function Name:  CleanUp

Purpose:        Free all memory allocated to the linked list pointed to by g_pPlayers.

In Parameters:  none
Out Parameters: none
Version:        1.0
Author:         Mark Kaganovsky
**************************************************************************************/
void CleanUp(){
	struct Link *current;
	struct Link *toDelete;

	/* Handle special cases (no player or only one player). */
	if (g_pPlayers == NULL){ /* No players on the team. */
		return;
	}
	else if (g_pPlayers->pNext == NULL){ /* Only one player on the team. */
		free(g_pPlayers->pPlayer->firstName);
		free(g_pPlayers->pPlayer->lastName);
		free(g_pPlayers->pPlayer);
		free(g_pPlayers);
		return;
	}

	/* Average case below, more than one player on the team. */
	current = g_pPlayers;
	while (current != NULL){
		toDelete = current;
		current = current->pNext;
		free(toDelete->pPlayer->firstName);
		free(toDelete->pPlayer->lastName);
		free(toDelete->pPlayer);
		free(toDelete);
	}
}