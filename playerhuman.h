#ifndef PLAYERHUMAN_H
#define PLAYERHUMAN_H
#include "player.h"

//This class asks user for row and column. This class acts as a human player for the game.
class PlayerHuman:public Player
{	public:
	PlayerHuman(); //Default Constructor
	PlayerHuman(const PlayerHuman& a); //Copy Contructor
	~PlayerHuman(); //Destructor
	PlayerHuman& operator = (const PlayerHuman& a); //Assignment operator
	// The following fuction asks the user to enter a row and column and returns a position to be filled by board class
	virtual int nextMove(const Board& b) const; 
};


#endif
