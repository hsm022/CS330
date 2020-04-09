#include "playerhuman.h"
#include "player.h"
#include "board.h"
#include <iostream>

using namespace std;

PlayerHuman::PlayerHuman(){} // Default Constructor
PlayerHuman::PlayerHuman(const PlayerHuman& a){} // Copy Constructor
PlayerHuman::~PlayerHuman(){} // Destructor
PlayerHuman& PlayerHuman:: operator = (const PlayerHuman& a) { return *this; } // Assignment operator

// This fuction asks the user to enter a row and column and returns a position to be filled by board class
int PlayerHuman::nextMove(const Board& b)const 
{
	
	int r, c, s; // Variables 
	cout << endl << "Enter Row: "; //Prompting user to enter row number
	cin >> r;  
	cout << endl << "Enter Column: ";//Prompting user to enter column number
	cin >> c;
	s = b.getSize(); //This is to check the size of the board (3x3 usually)

	while (r < 1 || r > s) //This is to make sure that the user enters a valid row number 
	{
		cout << "Please enter a row number between 1 and " << s << " :";
		cin >> r;
	}

	while (c < 1 || c > s)//This is to make sure that the user enters a valid column number 
	{
		cout << "Please enter a column number between 1 and " << s << " :";
		cin >> c;
	}

	int p =  (r - 1) * s + (c-1); //converts row and column to a position
	return p ;
}