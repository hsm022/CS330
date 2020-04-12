#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"

//This is an abstract class for the other two player classes.
class Player
{
private:
	char symbol;
public:
	Player(); //Default Constructor
	Player(const Player& b); //Copy Contructor
	char getSymbol(); //This function returns the symbol
	void setSymbol(char s); //This function sets the symbol
	virtual ~Player(); //Destructor
	Player& operator= (const Player& b); //Assignment operator
	virtual int nextMove(const Board& b)const = 0; //Pure virtual function
};

#endif
