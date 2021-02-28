//Tic Tac Toe Game in C++

#include <stdio.h>	//printf
#include <string.h>	//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>

#include <iostream>
#include <stdlib.h>

#define SERVERPORT 31200
#define SERVERPORTSTR "31200"
#define SERVERIP "199.17.28.75"
#define SERVERNAME "ahscentos"
#define BUFL 100
#include <signal.h>

using namespace std;

//Array for the board
char board[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};

//Variable Declaration
int choice;
int row,column;
char turn = 'X';
bool draw = false;

//Function to show the current status of the gaming board

void display_board(){

    //Rander Game Board LAYOUT

    cout<<"Computer[X]\t Human[O]\n\n";
    cout<<"\t\t     |     |     \n";
    cout<<"\t\t  "<<board[0][0]<<"  | "<<board[0][1]<<"  |  "<<board[0][2]<<" \n";
    cout<<"\t\t_____|_____|_____\n";
    cout<<"\t\t     |     |     \n";
    cout<<"\t\t  "<<board[1][0]<<"  | "<<board[1][1]<<"  |  "<<board[1][2]<<" \n";
    cout<<"\t\t_____|_____|_____\n";
    cout<<"\t\t     |     |     \n";
    cout<<"\t\t  "<<board[2][0]<<"  | "<<board[2][1]<<"  |  "<<board[2][2]<<" \n";
    cout<<"\t\t     |     |     \n";
}

//Function to get the player input and update the board

void player_turn(){
    if(turn == 'X'){
        cout<<"\n\tComputer turn : ";
    }
    else if(turn == 'O'){
        cout<<"\n\tHuman turn : ";
    }
    //Taking input from user
    //updating the board according to choice and reassigning the turn Start

    cin>> choice;

    //switch case to get which row and column will be update

    switch(choice){
        case 1: row=0; column=0; break;
        case 2: row=0; column=1; break;
        case 3: row=0; column=2; break;
        case 4: row=1; column=0; break;
        case 5: row=1; column=1; break;
        case 6: row=1; column=2; break;
        case 7: row=2; column=0; break;
        case 8: row=2; column=1; break;
        case 9: row=2; column=2; break;
        default:
            cout<<"Invalid Move\n";
    }

    if(turn == 'X' && board[row][column] != 'X' && board[row][column] != 'O'){
        //updating the position for 'X' symbol if
        //it is not already occupied
        board[row][column] = 'X';
        turn = 'O';
    }else if(turn == 'O' && board[row][column] != 'X' && board[row][column] != 'O'){
        //updating the position for 'O' symbol if
        //it is not already occupied
        board[row][column] = 'O';
        turn = 'X';
    }else {
        //if input position already filled
        cout<<"Box already filled!n Please choose another!!\n\n";
        player_turn();
    }
    /* Ends */
    display_board();
}

//Function to get the game status e.g. GAME WON, GAME DRAW GAME IN CONTINUE MODE

bool gameover(){
    //checking the win for Simple Rows and Simple Column
    for(int i=0; i<3; i++)
    if(board[i][0] == board[i][1] && board[i][0] == board[i][2] || board[0][i] == board[1][i] && board[0][i] == board[2][i])
    return false;

    //checking the win for both diagonal

    if(board[0][0] == board[1][1] && board[0][0] == board[2][2] || board[0][2] == board[1][1] && board[0][2] == board[2][0])
    return false;

    //Checking the game is in continue mode or not
    for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
    if(board[i][j] != 'X' && board[i][j] != 'O')
    return true;

    //Checking the if game already draw
    draw = true;
    return false;
}

//Program Main Method

int main(int argc , char *argv[])
{
        
	int err;
	int cSocket;
	struct sockaddr_in sAddr;
	struct sockaddr_in cAddr;
	int cSocLen;
	char buf[BUFL];
	char message[BUFL];
	
	memset (&cAddr, 0, sizeof (struct sockaddr_in));
	cAddr.sin_family = AF_INET;
	cAddr.sin_port = htons (SERVERPORT);
	cAddr.sin_addr.s_addr = inet_addr(SERVERIP);
	
	cSocket = socket (AF_INET, SOCK_STREAM, 0);
	if (cSocket == -1)
	{
		perror ("socClient: socket creation failed");
		exit(1);
	}
	
	err = connect (cSocket, (struct sockaddr*)&cAddr, sizeof(struct sockaddr_in));
	if (err == -1)
	{
		perror ("socClient: connect failed");
		exit(2);
	}
	
	printf("Name: ");
	fgets(buf, BUFL, stdin);
	//strcpy(message, "Hello, I'm ");
	//strcat(message, buf);
	
	err = send (cSocket, buf, sizeof(buf), 0);
	//err = send (cSocket, message, sizeof(message), 0);
	
	//err = send (cSocket, "Connection made!\n", 17, 0);
	
	printf ("socClient: number of bytes sent to server: %d\n", err);
	
	exit(0);


    cout<<"\t\t\tT I C K -- T A C -- T O E -- G A M E\t\t\t";
    cout<<"\n\t\t\t\tFOR 2 PLAYERS\n\t\t\t";
    while(gameover()){
        display_board();
        player_turn();
        gameover();
    }
    if(turn == 'X' && draw == false){
        cout<<"\n\nCongratulations! Computer has won the game\n\n";
    }
    else if(turn == 'O' && draw == false){
        cout<<"\n\nCongratulations! Human has won the game\n\n";
    }
    else
    cout<<"\n\nGAME DRAW!!!\n\n";
 	
  return 0;

}
