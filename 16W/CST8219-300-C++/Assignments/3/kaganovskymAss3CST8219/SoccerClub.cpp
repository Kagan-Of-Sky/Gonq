#include <limits>
#include <iostream>
using namespace std;

#include "ClubMember.h"
#include "Supporter.h"
#include "Player.h"
#include "Link.h"
#include "SoccerClub.h"




SoccerClub::SoccerClub(){
	pClubMembers = nullptr;
}




SoccerClub::~SoccerClub(){
	if (nullptr != pClubMembers){ /* At least 1 club member. */
		Link *toDelete = pClubMembers;
		
		while (pClubMembers->pNext != nullptr){
			toDelete     = pClubMembers;
			pClubMembers = pClubMembers->pNext;

			delete toDelete;
		}

		delete pClubMembers;
	}
}




void SoccerClub::AddClubMember(){
	const char CMT_SUPPPORTER = 'S'; /* Club Member Type Supporter */
	const char CMT_PLAYER     = 'P'; /* Club Member Type Player */


	const int FNAME_BUF_SIZE = 50; /* The buffer size for the first name. */
	const int LNAME_BUF_SIZE = 50; /* The buffer size for the last name. */

	cout << "ADDING A CLUB MEMBER" << endl;

	/* Ignore all characters that are currently in the input stream. */
	cin.ignore(numeric_limits<streamsize>::max(), '\n');


	/* Read in the first name. */
	char *firstName = new char[FNAME_BUF_SIZE];
	cout << "Please enter the Club Member first name: ";
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


	/* Read in the last name. */
	char *lastName = new char[LNAME_BUF_SIZE];
	cout << "Please enter the Club Member last name: ";
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


	/* Read in the subscription. */
	double subscription;
	while (true){
		cout << "Please enter the Club Member subscription: ";
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
	
	/* Read in the type of club member */
	char clubMemberType = '\0';
	while (CMT_PLAYER != clubMemberType && CMT_SUPPPORTER != clubMemberType){
		cout << "Supporter (S) or Player (P)?" << endl;
		cin.get(clubMemberType);

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	/* Create the appropriate object. */
	ClubMember *newClubMember = nullptr;

	switch (clubMemberType){
		case CMT_SUPPPORTER:{
			cout << "Supporter" << endl;

			/* Get the number of fixtures. */
			int numFixtures = -1;
			while (numFixtures < 0){
				cout << "Please Enter the number of fixtures" << endl;

				cin >> numFixtures;
				if (!cin.good()){
					numFixtures = -1;
				}

				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			Date *fixtures = new Date[numFixtures];

			for (int i=0; i < numFixtures; ++i){
				/* Read in the day */
				cout << "enter the day of fixture #" << i << " ";
				unsigned int day;
				for (cin >> day; !cin.good(); cin >> day){
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					cout << "enter the day of fixture #" << i << " ";
				}
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				/* Read in the month */
				cout << "enter the month of fixture #" << i << " ";
				unsigned int month;
				for (cin >> month; !cin.good(); cin >> month){
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					cout << "enter the month of fixture #" << i << " ";
				}
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				/* Read in the year */
				cout << "enter the year of fixture #" << i << " ";
				unsigned int year;
				for (cin >> year; !cin.good(); cin >> year){
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					cout << "enter the year of fixture #" << i << " ";
				}
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				fixtures[i].day = day;
				fixtures[i].month = month;
				fixtures[i].year = year;
			}

			/* Create the Supporter */
			newClubMember = new Supporter(firstName, lastName, subscription, fixtures, numFixtures);

			break;
		}

		case CMT_PLAYER:
			/* Get the position. */
			int position = -1;
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

				if (!cin.good()){
					position = -1;
				}

				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			/* Create the new club member */
			newClubMember = new Player(firstName, lastName, subscription, position);

			break;
	}

	/* Create the new link and add it to the list. */
	Link *newLink = new Link(nullptr, pClubMembers, newClubMember);

	/* Update the current head of the linked list. */
	if (pClubMembers){
		pClubMembers->pPrev = newLink;
	}
	pClubMembers = newLink;
}




void SoccerClub::DeleteClubMember(){
	cout << "DELETE A CLUB MEMBER" << endl;
	
	/* Make sure that there is at least 1 link in the list. */
	if (!pClubMembers){
		cout << "No club members" << endl;
		return;
	}

	Link *toDelete;

	/* Remove the head element from the list. */
	toDelete = pClubMembers;
	pClubMembers = pClubMembers->pNext;
	if (pClubMembers){      /* Update previous pointer if needed. */
		pClubMembers->pPrev = nullptr;
	}

	/* Free the memory associated with this link. */
	delete toDelete;

	cout << "Club member deleted" << endl;
}




void SoccerClub::OutputClubMembersForward(){
	cout << "FORWARD PRINTING CLUB MEMBERS" << endl;

	/* Make sure that there is at least one person on the team. */
	if (!pClubMembers){
		cout << "No club members" << endl;
		return;
	}

	/* Print the data for each club member in the linked list. */
	Link *current = pClubMembers;
	for (int clubMemberNumber=0; current; current=current->pNext, ++clubMemberNumber){
		cout << "Club Member " << clubMemberNumber << endl;
		current->pClubMember->Output();
		cout << endl;
	}
}




void SoccerClub::OutputClubMembersReverse(){
	cout << "REVERSE PRINTING CLUB MEMBERS" << endl;

	/* Make sure that there is at least one player in the list. */
	if (!pClubMembers){
		cout << "No club members" << endl;
		return;
	}

	Link *current;
	int   number; /* Club member number */

	/* Follow the linked list to the end. */
	for (current=pClubMembers, number=0; current->pNext; current=current->pNext, ++number){
		// No body
	}

	/* Now that we are at the tail we can go backwards. */
	for (; current; current=current->pPrev, --number){
		cout << "Club Member " << number << endl;
		current->pClubMember->Output();
		cout << endl;
	}
}




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
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	/* Search for the player. */
	Player toFind(nullptr, nullptr, 0.0, position);

	for (Link *current=pClubMembers; current; current=current->pNext){
		Player *player = dynamic_cast<Player *>(current->pClubMember);
		if (player && *player == toFind){
			cout << "position found" << endl;
			current->pClubMember->Output();
			return;
		}
	}

	cout << "position not found" << endl;
}




ClubMember* SoccerClub::operator[](unsigned int index){
	/* Index out of range. */
	if (index < 0){
		return nullptr;
	}

	Link *current;
	for (current=pClubMembers; index && current; --index, current=current->pNext){
		/* No body. */
	}

	/* Found club member. */
	if (!index && current){
		return current->pClubMember;
	}

	/* Did not find club member. */
	return nullptr;
}




ostream& operator<<(ostream &stream,SoccerClub &sc){
	sc.OutputClubMembersForward();
	return stream;
}