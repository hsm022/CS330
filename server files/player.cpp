//Header files
#include "player.h"
#include <iostream>

using namespace std;

//Default Constructor
Player::Player() 
{
	symbol = 'X';
}

//Copy Contructor
Player::Player(const Player& b)
{
	symbol = b.symbol;
}

//Destructor
Player::~Player()
{

}

//Assignment operator
Player& Player::operator= (const Player& b)
{
	symbol = b.symbol;
	return *this;
}

//This function sets the symbol
void Player::setSymbol(char s)
{
	symbol = s;
}

//This function returns the symbol
char Player::getSymbol()
{
	return symbol;
}


