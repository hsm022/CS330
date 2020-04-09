//Header files 
#include<iostream>
#include "board.h"
#include"player.h"
#include"playerhuman.h"
#include"playerrandom.h"

#include "board.cpp"
#include"player.cpp"
#include"playerhuman.cpp"
#include"playerrandom.cpp"



using namespace std;


int main()
{

	Board a; //Board class
	Player *p1; //Pointer to be used for human and computer player
	Player *p2; //Pointer to be used for human and computer player

	int select;

	cout << "TIC TAC TOE" << endl;
	cout << "Please select one of the options below:" << endl;
	do {
	cout << "Press 1 for human vs human" << endl;
	cout << "Press 2 for human vs computer" << endl;
	cout << "Press 3 for computer vs computer" << endl;
	cin >> select;
		if (select != 1 && select != 2 && select != 3)
		{
			cin.clear();
			cin.ignore();
		}
	} while (select != 1 && select != 2 && select != 3);

	if (select == 1)
	{
		p1 = new PlayerHuman;
		p1->setSymbol('X');

		p2 = new PlayerHuman;
		p2->setSymbol('O');
	}

	else if (select == 2)
	{
		p1 = new PlayerRandom;
		p1->setSymbol('X');

		p2 = new PlayerHuman;
		p2->setSymbol('O');
	}

	else 
	{
		p1 = new PlayerRandom;
		p1->setSymbol('X');

		p2 = new PlayerRandom;
		p2->setSymbol('O');
	}
	
	do {
		bool move = false;
		while (move == false)
		{
			cout << endl << "Player one move" << endl;
			move = a.changeSymbol(p1->nextMove(a), p1->getSymbol());
			a.print();
		}

		if (a.checkWinner() == 1 || a.checkWinner() == 2 || a.checkWinner() == 4)
		{
			if (a.checkWinner() == 1)
			{
				cout << "X wins" << endl << endl;
			}
			else if (a.checkWinner() == 2)
			{
				cout << "O wins" << endl << endl;
			}
			else 
			{
				cout << "Game Tie" << endl << endl;
			}
			break;
		}
		move = false;
		while (move == false)
		{
			cout << endl << "Player Two move" << endl;
			move = a.changeSymbol(p2->nextMove(a), p2->getSymbol());
			a.print();
		}
		if (a.checkWinner() == 1 || a.checkWinner() == 2 || a.checkWinner() == 4)
		{
			if (a.checkWinner() == 1)
			{
				cout << "X wins" << endl << endl;
			}
			else if (a.checkWinner() == 2)
			{
				cout << "O wins" << endl << endl;
			}
			else
			{
				cout << "Game Tie" << endl << endl;
			}
			break;
		}
	} while (a.checkWinner() == 3);
	
	//Freeing dynamic memory
	delete p1;
	delete p2;
	p1 = NULL;
	p2 = NULL;
	return 0;
	}
