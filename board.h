#ifndef BOARD_H
#define BOARD_H

class Board {
private:
	const int SIZE = 3;
	char *cell = new char [SIZE * SIZE];
public:
	Board(); //Default Constructor
	Board(const Board& b); //Copy Contructor
	~Board(); //Destructor
	Board& operator= (const Board& b); //Assignment operator
	int getSize() const; //Returns size
	void print(); //Prints the board on screen
	bool changeSymbol(int p, char s); //This function sets the symbol on board
	int checkWinner(); //Checks for winner
	bool checkEmpty(int p)const; //Checks if a position has not be filled
};

#endif
