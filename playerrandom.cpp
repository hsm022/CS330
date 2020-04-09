//Header files
#include "playerrandom.h"
#include "player.h"
#include "board.h"
#include<cstdlib>
#include<ctime>

//Default Constructor
PlayerRandom::PlayerRandom()
{
	srand(time(0));
}

//Copy Contructor
PlayerRandom::PlayerRandom(const PlayerRandom& a)
{
	srand(time(0));
}

//Destructor
PlayerRandom::~PlayerRandom()
{}

//Assignment operator
PlayerRandom& PlayerRandom:: operator = (const PlayerRandom& a)
{
	return *this;
}

//This function returns a position to be filled by board class
int PlayerRandom::nextMove(const Board& b)const
{
    int r = rand() % (b.getSize() * b.getSize()); //creating a random number
	while (!b.checkEmpty(r)) //checking if the position is empty in the board
	{
		r = rand() % (b.getSize() * b.getSize()); //creating another random number
	}
	return r;
}

