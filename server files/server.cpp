/***************************************************************************
 Sockets Daemon Program
    The code is a modified version of code from CS330 lab 7 (sockets) class. 

  A daemon process is started on some host.  A socket is acquired
  for use, and it's number is displayed on the screen.  For clients
  to connect to the server, they must use this socket number.
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <cstdlib>
#include <ctime>


#include<iostream>
#include "board.h"
#include"player.h"
#include"playerhuman.h"
#include"playerrandom.h"

#include "board.cpp"
#include"player.cpp"
#include"playerhuman.cpp"
#include"playerrandom.cpp"

/* Use port number 0 so that we can dynamically assign an unused port number. */
#define PORTNUM         0


/* Display error message on stderr and then exit. */
#define OOPS(msg)       {perror(msg); exit(1);}

#define MAXLINE 512

int main()
{
  struct sockaddr_in saddr;       /* socket information */
  struct hostent *hp;     /* host information */
  char hostname[256];     /* host computer */
  socklen_t slen;         /* length socket address */
  int s;                  /* socket return value */
  int sfd;                /* socket descriptor returned from accept() */
  char ch[MAXLINE];       /* character for i/o */
  FILE *sf;               /* various file descriptors */
  int bbf;
  int num_char=MAXLINE;
  int status;

  srand(time(0));    // this is used to get random numbers further in the program

  
  /*
   * Build up our network address. Notice how it is made of machine name + port.
   */

  /* Clear the data structure (saddr) to 0's. */
  memset(&saddr,0,sizeof(saddr));

  /* Tell our socket to be of the internet family (AF_INET). */
  saddr.sin_family = AF_INET;

  /* Aquire the name of the current host system (the local machine). */
  gethostname(hostname,sizeof(hostname));

  /* Return misc. host information.  Store the results in the
   * hp (hostent) data structure.  */
  hp = gethostbyname(hostname);

  /* Copy the host address to the socket data structure. */
  memcpy(&saddr.sin_addr, hp->h_addr, hp->h_length);

  /* Convert the integer Port Number to the network-short standard
   * required for networking stuff. This accounts for byte order differences.*/
  saddr.sin_port = htons(PORTNUM);
  
  /*
   * Now that we have our data structure full of useful information,
   * open up the socket the way we want to use it.
   */
  s = socket(AF_INET, SOCK_STREAM, 0);
  if(s == -1)
    OOPS("socket");

  /* Register our address with the system. */
  if(bind(s,(struct sockaddr *)&saddr,sizeof(saddr)) != 0)
    OOPS("bind");

  /* Display the port that has been assigned to us. */
  slen = sizeof(saddr);
  getsockname(s,(struct sockaddr *)&saddr,&slen);
  printf("Socket assigned: %d\n",ntohs(saddr.sin_port));

  /* Tell socket to wait for input.  Queue length is 4. Upto 4 connections*/
  if(listen(s,4) != 0)
    OOPS("listen");

   
  /* Loop indefinately and wait for events. */
  for(;;)
  {


    /* Wait in the 'accept()' call for a client to make a connection. */
    sfd = accept(s,NULL,NULL);
    if(sfd == -1)
      OOPS("accept");
      
    pid_t fork_return = fork();

    if (fork_return == 0) /* child process */ 
    { Board a; //Board class
      Player *p1; //Pointer to be used for human and computer player
      Player *p2; //Pointer to be used for human and computer player
      int select;

      string message[10];
      message[0] = "Nice try human!!";
      message[1] = "You can't beat me human!!";
      message[2] = "Way to go human!!";
      message[3] = "Good Luck, you are gonna need it!!";
      message[4] = "Human VS Machine";
      message[5] = "First I win this game, then I take over your cities!!";
      message[6] = "In your dreams human!!";
      message[7] = "Ohh really!";
      message[8] = "You are doomed human!!";
      message[9] = "Poor move human!";


      int backupstdput = dup(fileno(stdout)); // store stdout in a variable to be used later on
      int backupstdin = dup(fileno(stdin)); // store stdout in a variable to be used later on
      dup2(sfd,fileno(stdout)); // output to client's computer
      dup2(sfd,fileno(stdin));  //input from client's computer

      // welcome messsage
      cout << "**********TIC TAC TOE**********" << endl;
      cout << "Please select one of the options below:" << endl;

      char again = 'y';

          while(again == 'y' || again == 'Y')
        {
            again = 'n';
            string player1;
            string player2;
            string winner1;
            string winner2;

            // only accept 1 or 2 as answer
            do { 
            cout << "Press 1 to challenge computer. (human vs computer)" << endl;
            cout << "Press 2 if you want to watch two computers play against each other.(computer vs computer)" << endl;
            cin >> select;
              if (select != 1 && select != 2)
              {
                cin.clear();
                cin.ignore();
              }
            } while (select != 1 && select != 2);
            
            cin.clear();
            cin.ignore();
            if (select == 1)  // if user wants to play against computer
            {
              p1 = new PlayerHuman;
              p1->setSymbol('X');
              player1 = "Human's Turn (X)";
              winner1 = "HUMAN WINS";

              p2 = new PlayerRandom;
              p2->setSymbol('O');
              player2 = "Computer's Turn (O)";
              winner2 = "COMPUTER WINS";
            }

            else // user wants to watch two computers play.
            {
              p1 = new PlayerRandom;
              p1->setSymbol('X');
              player1 = "First Computer's Turn (X)";
              winner1 = "First computer Wins (X)";

              p2 = new PlayerRandom;
              p2->setSymbol('O');
              player2 = "Second Computer's Turn (O)";
              winner2 = "Second computer Wins (O)";
             
             cout << "***Keep pressing Enter to let a computer take it's turn***" << endl;
            }
            
            do {

              if(select != 1)
              {char c = getchar();} // wait for user to press enter
              bool move = false;
              while (move == false) //check if move is valid and insert it in board and print
              {
                cout << endl << player1 << endl;
                move = a.changeSymbol(p1->nextMove(a), p1->getSymbol());
                a.print();
              }

              if (a.checkWinner() == 1 || a.checkWinner() == 2 || a.checkWinner() == 4) //check if someone won
              { cout << endl <<  "******************************" << endl;

                if (a.checkWinner() == 1)
                {
                  cout << winner1 << endl;
                }
                else if (a.checkWinner() == 2)
                {
                  cout << winner2 << endl;
                }
                else 
                {
                  cout << "Game Tie" << endl;
                }

                cout << "******************************" << endl << endl;
                break;
              }

              cout << "*****************************************************************" << endl; 
              
              if(select == 1) // print funny messages if human playing
              {int j = rand() % 10;
              cout << "Computer: "<< message[j] << endl; 
              sleep(2);}
              else
              {char c = getchar();  // wait for user to press enter
              }

              move = false;
              while (move == false) //check if move is valid and insert it in board and print
              {
                cout << endl << player2 << endl;
                move = a.changeSymbol(p2->nextMove(a), p2->getSymbol());
                a.print();
              }
              if (a.checkWinner() == 1 || a.checkWinner() == 2 || a.checkWinner() == 4) //check if someone won
              { 
                cout << endl <<"******************************" << endl;
                if (a.checkWinner() == 1)
                {
                  cout << winner1 << endl;
                }
                else if (a.checkWinner() == 2)
                {
                  cout << winner2 << endl;
                }
                else
                {
                  cout << "Game Tie" << endl;
                }
                cout << "******************************" << endl << endl;
                break;
              }

              cout << "*****************************************************************" << endl; 

              
              
            } while (a.checkWinner() == 3);

            a.cleanboard();
            delete p1;
            delete p2;
            p1 = NULL;
            p2 = NULL;

            cout << "*******************************************************************" << endl; 
            cout << "Perhaps another game? Press y for another game or another key to exit : ";
            cin >> again;

        }
      

        
      // restoring stdout and stdin
      dup2(backupstdput,fileno(stdout));
      dup2(backupstdin,fileno(stdin)); 
      exit(0); 
    } 
    else if (fork_return > 0) /* parent process */ 
    { 
      //loop through to check if new client wants to connect.   
    }

   else if(fork_return == -1)
    {
        printf("ERROR:\n");
        return 1;
    }
   close(sfd); //close socket
  }

 
  return 0;
} 
