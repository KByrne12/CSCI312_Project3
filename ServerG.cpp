#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "soc.h"


#define BUFL 100

int main()
{
	int sSocket;
	int cSocket;
	struct sockaddr_in sAddr;
	struct sockaddr_in cAddr;
	int cSocLen;
	int error;
	
	sSocket = socket(AF_INET , SOCK_STREAM , 0);
	if (cSocket == -1)
	{
		perror("Socket creation failed.\n");
		exit (11);
	}
	
	
	error = connect(cSocket, (struct sockaddr *)&cAddr, sizeof(struct sockaddr_in));
	if (error = -1)
	{
		perror ("Connection failed.\n");
		exit(12);
	}
	
	execl("./TicTacToe","TicTacToe", NULL ,(char)* NULL);
	
	
	error = send(cSocket, "Connection complete.\n", BUFL, 0);
	
	printf("number of bytes sent: %d\n",error);
	
	
	exit (0);
}
