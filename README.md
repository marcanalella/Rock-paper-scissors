# rock-paper-scissors
Made for resolution of the project of the Operating Systems course of the University of Enna Kore of the a.y. 2017/2018

## Overview
### Client
A client creates a socket and tries to connect to the server. When a connection is made with the server, the client sends the gesture to the server. When the server sends the result of the game, the client displays the information to the user (on stdout), closes its socket and terminates.

### Server
The server will create sockets with port number 4000 and waits for requests to play a game from client. Once a connection has been made with the client, the server receive from the player his hand gestures (one of rock, paper, scissors). After the client send his gesture, the server decides who wins and informs player who won that round and asks for their gestures for the next round. The game is repeated until the players wishes to stop playing. When no more games are to be played the server sends statistics and then the server closes both sockets, which ends the game and the process terminates.

## How to run
Compile the C source codes then, run the client/server excutable file.


