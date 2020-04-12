#ifndef PLAYERRANDOM_H
#define PLAYERRANDOM_H
#include "player.h"

//This class creates a random position and acts as a computer player for the game.
class PlayerRandom:public Player
{
public:
	PlayerRandom(); //Default Constructor
	PlayerRandom(const PlayerRandom& a); //Copy Contructor
	~PlayerRandom(); //Destructor
	PlayerRandom& operator = (const PlayerRandom& a); //Assignment operator
	int nextMove(const Board& b)const; //This function returns a position to be filled by board class
}
;
#endif
