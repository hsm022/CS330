/*****************************************************************
 Sockets Daemon Program

  This code was modified from Nigel Horspools, "The Berkeley
  Unix Environment".

  A daemon process is started on some host.  A socket is acquired
  for use, and it's number is displayed on the screen.  For clients
  to connect to the server, they muse use this socket number.
*****************************************************************/

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


#include<iostream>
#include "board.h"
#include"player.h"
#include"playerhuman.h"
#include"playerrandom.h"

#include "board.cpp"
#include"player.cpp"
#include"playerhuman.cpp"
#include"playerrandom.cpp"

/* Use port number 0 so that we can dynamically assign an unused
 * port number. */
#define PORTNUM         0

/* Set up the location for the file to display when the daemon (okay,
 * server for you religious types) is contacted by the client. */
#define BBSD_FILE       "./test.bbs.file"
/*"/nfs/net/share/ftp/pub/class/330/test.file" */

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
  string str;


  
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

  /* Tell socket to wait for input.  Queue length is 1. */
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
    { 
      int backupstdput = dup(fileno(stdout));
      int backupstdin = dup(fileno(stdin)); 
      dup2(sfd,fileno(stdout));
      dup2(sfd,fileno(stdin)); 
    // char message[MAXLINE] = "TIC TAC TOE\nPlease select one of the options below:\nPress 1 for human vs human\nPress 2 for human vs computer\n Press 3 for computer vs computer";
    // send(sfd, message, strlen(message), 0);
    // char printthis[500] = "Testing if works";
    // strcpy(message,printthis);
    // send(sfd, message, strlen(message), 0);
    // fflush(stdout);
    // num_char = read(1,ch,MAXLINE);
    // cout << "testng" << endl;
   // write(sfd,ch,num_char);
      
      // while((num_char=read(1,ch,MAXLINE))> 0)
      //   if (write(sfd,ch,num_char) < num_char)
      //      OOPS("writing");



          int size;

          cout << "TIC TAC TOE" << endl;
          
          // This is to select the size of the matrix
          do {
            cout << "Please select the size of the Matrix between 3 and 6:" << endl;
            cin >> size;
              if (size <3 || size > 6)
              {
                cout << "Size has to be between 3 and 6" << endl;
                cin.clear();
                cin.ignore();
              }
          } while (size < 3 || size > 6);

          Board a(size); //Board class
          Player *p1; //Pointer to be used for human and computer player
          Player *p2; //Pointer to be used for human and computer player

          // Asking user to select the mode of the game
          int select;
          cout << "Please select one of the options below:" << endl;
          do {
          cout << "Press 1 for human vs human" << endl;
          cout << "Press 2 for human vs computer" << endl;
          cout << "Press 3 for computer vs computer" << endl;
          cin >> select;
            if(select != 1 && select != 2 && select != 3)
            {
              cin.clear();
              cin.ignore();
            }

          } while (select != 1 && select != 2 && select != 3);

          if (select == 1)  //Declaring human vs human instances
          {
            p1 = new PlayerHuman;
            p1->setSymbol('X');

            p2 = new PlayerHuman;
            p2->setSymbol('O');
          }

          else if (select == 2) //Declaring human vs computer instances
          {
            p1 = new PlayerRandom;
            p1->setSymbol('X');

            p2 = new PlayerHuman;
            p2->setSymbol('O');
          }

          else  //Declaring computer vs computer instances
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
      dup2(backupstdput,fileno(stdout));
      dup2(backupstdin,fileno(stdin)); 

        delete p1;
        delete p2;
        p1 = NULL;
        p2 = NULL;


      exit(0); 
    } 
    else if (fork_return > 0) /* parent process */ 
    { 

      //wait(&status);
      // while((num_char=read(sfd,ch,MAXLINE))> 0 && waitpid(fork_return, &status,WNOHANG)==0)
      //   if (write(1,ch,num_char) < num_char)
      //      OOPS("writing");    
    }

   else if(fork_return == -1)
    {
        printf("ERROR:\n");
        return 1;
    }
   close(sfd);
  }

 
  return 0;
} 
