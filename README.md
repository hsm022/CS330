# CS330 A TIC TAC TOE game through Sockets

**Name: Harpinder Singh Minhas**

**Student Number: 200390931**

**Topic: Sockets**

# Description: 
The project is based on the sockets topic. There are two files in the project that work with sockets. 

**server.cpp :**
The first one is server.cpp. This file uses both c and c++ code. The file creates a socket which can accept clients and displays the sockets port number on the screen. The server.cpp uses all the other files in the project except client.cpp to run and to let clients play the Tic Tac Toe game. The server.cpp can handle multiple clients at the same time. Once a client disconnects or the user finishes playing the game, the socket is closed.

**client.cpp :**
The second file is client.cpp. This file also creates a socket and sends a request to connect to the server.cpp's generated port. The client.cpp files asks the user to enter the name of a the host and the socket before making a connection. Once a connection is made, the inputs of the user are transferred from client to server through socket and the messages from server that come through to the socket to client are display on to the clients screen.

**Other files used by socket.cpp**

- **board.h** -  Header file for board.cpp

- **board.cpp** - This file creates a board (matrix) and provides functions to manipulate the cells in the board and to print the board.

- **player.h** - Header file for player.cpp

- **player.cpp** - This file provides an abstract class for the other two player classes.

- **playerrandom.h** - Header file for playerrandom.cpp

- **playerrandom.cpp** - This file creates a random position and acts as a computer player for the game.

- **playerhuman.h** - Header file for playerhuman.cpp

- **playerhuman.cpp** -  This file has functions that ask user for row and column and prints errors in case of wrong input. The file basically helps the human player play the game.

# Challenges

**Accepting Multiple clients:** 
One challenge was to build the server.cpp in such a way that it accepted multiple clients at the same time and had no issues. This was achieved by creating a loop and accepting multiple clients. Once a client successfully connects to the server, a child process is generated which lets the client play the Tic Tac Toe game. The parent process continues to loop around to check if more clients want to connect and creates a child process for each new client.

**Continue using cin and cout:**
There were many cout and cin statements in the program which the client needed to see but the server did not. This was achieved by using dup() and dup2() functions. All the cout and cin statements in the server.cpp's child process are displayed on the client's screen instead of server's screen. Once the client disconnects, the dup2() function is called again to configure the stdin from server's keyboard and stdout to server's screen.

# Instructions to reproduce the project

## Server

**On a regular linux machine**
- Make sure all the files (client.cpp can be excluded) are in same folder. The server.cpp needs all the other files of the project except client.cpp to work properly or to even compile.
- Create an executable file (.o file) by running g++ server.cpp -o server , depending on your complier you might see some warnings(not errors) but they can be ignored. 
- Run the file ./server
- The screen will display the socket number, provide this socket number to clients so they can connect to the server.


**On hercules**
- Use touch .newgcc
- Logout of hercules and logback in.
- Make sure all the files (client.cpp can be excluded) are in same folder. The server.cpp needs all the other files of the project except client.cpp to work properly or to even compile.
- Create an executable file (.o file) by running g++ -std=c++11 server.cpp -o server
- Run the file ./server
- The screen will display the socket number, provide this socket number to clients so they can connect to the server.

## Client

- Create an executable file (.o file) by running g++ client.cpp -o client
- Run the file ./client
- Enter the host name. (if the server is running on hercules use hercules.cs.uregina.ca)
- Enter the port number provided by the server.
- You will be provided with two options to play game. One to play with computer, another to just watch two computers play.
- Once a game is finished, the user can type y to play again or any other key to exit.

## Sample Run on youtube

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/j0edpAOKHL0/0.jpg)](https://www.youtube.com/watch?v=j0edpAOKHL0)

