//Header files
#include "board.h"
#include <iostream>

using namespace std;

//Default Constructor
Board::Board()
{
	for (int i = 0; i < SIZE*SIZE; i++)
	{
		cell[i] = ' ';
	}
}

//Copy Contructor
Board::Board(const Board& b)
{
	for (int i = 0; i < SIZE*SIZE; i++)
	{
		cell[i] = b.cell[i];
	}
}

//Destructor
Board::~Board()
{
	delete[] cell;
	cell = NULL;
}

//Assignment operator
Board& Board::operator= (const Board& b)
{
	for (int i = 0; i < SIZE*SIZE; i++)
	{
		cell[i] = b.cell[i];
	}

	return *this;
}

//Returns size
int Board::getSize() const
{
	return SIZE;
}

//Checks if a position has not be filled
bool Board::checkEmpty(int p)const
{
	if (cell[p] == ' ')
	{
		return true;
	}
	else
		return false;
}

//This function sets the symbol on board
bool Board::changeSymbol(int p, char s)
{
	if (cell[p] == ' ')
	{
		cell[p] = s;
		return true;
	}

	else {cin.clear();
		cout << "invalid move, try again" << endl;
		return false;
	}
}

//Makes the board empty again
void Board::cleanboard()
{
	for (int i = 0; i < SIZE*SIZE; i++)
	{cell[i] = ' ';}
}

//Checks for winner
int Board::checkWinner()
{

	//CHECKS VERTICALLY FOR WINNERS
	for (int i = 0; i <= SIZE*SIZE - SIZE; i = i + SIZE)
	{
		
		bool win = true;
		for (int j = i; j < i + SIZE-1 && win; j++)
		{
			if (cell[j] != cell[j + 1] || cell[j] == ' ')
			{
				win = false;
				break;
			}
				
		}
		if (win)
		{
			if (cell[i] == 'X')
			{
				return 1;
			}
			else
			{
				return 2;
			}
		}
	}



	//check horizontal
	for (int i = 0; i < SIZE; i++)
	{
		bool win = true;
		for (int j = i; j < SIZE*SIZE - SIZE && win; j = j + SIZE)
		{
			if (cell[j] != cell[j + SIZE] || cell[j] == ' ')
			{
				win = false;
				break;
			}
		}
		if (win)
		{
			if (cell[i] == 'X')
			{
				return 1;
			}
			else
			{
				return 2;
			}
			
		}
	}

	//CHECKING DIAGONAL FROM TOP LEFT TO BOTTOM RIGHT
	bool win = true;
	for (int i = 0; i < SIZE*SIZE - 1; i = i + SIZE+1)
	{
			if (cell[i] != cell[i + SIZE+1] || cell[i] == ' ')
			{
				win = false;
				break;
			}

	}

	if (win)
	{
		if (cell[0] == 'X')
		{
			return 1;
		}
		else
		{
			return 2;
		}

	}

	//CHECKING DIAGONAL FROM BOTTOM LEFT TO TOP RIGHT
	win = true;
	for (int i = SIZE*SIZE-SIZE; i > SIZE; i = i - SIZE + 1)
	{
		
		if (cell[i] != cell[i - SIZE + 1] || cell[i] == ' ')
		{
			win = false;
			break;
		}

	}

	if (win)
	{
		
		if (cell[SIZE*SIZE - SIZE] == 'X')
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}

	//checking for empty cells
	for (int i =0; i < SIZE*SIZE; i++)
	{
		if (cell[i] == ' ')
		{
			return 3; //means game is still going on
		}
	}

	return 4; // game is a tie
}


//Prints the board on screen
void Board::print()
{
	int i = 0;
	for (int r = 0; r <= SIZE * 2; r++)
	{
		for (int c = 0; c <= SIZE * 4; c++)
		{
			if (r % 2 == 0)
			{
				if (c % 4 == 0)
				{
					cout << '+';
				}
				else
				{
					cout << '-';
				}
			}
			else
			{
				if (c % 4 == 0)
				{
					cout << '|';
				}
				else
				{
					if (c % 2 == 0 && c > 0)
					{
						cout << cell[i];
						i++;
					}
					else { cout << ' '; }

				}
			}
		}
		cout << endl;
	}

	int o = checkWinner();
}
