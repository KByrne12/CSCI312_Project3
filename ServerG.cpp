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
	struct addrinfo info;
	struct addrinfo *serverResult;
	
	//server information
	
	memset(&info, 0, sizeof(struct addrinfo));
	info.ai_family = AF_INET;
	info.ai_socktype = SOCK_STREAM;
	info.ai_protocol = 0; // any protocol
	error = getaddrinfo(SERVERNAME, SERVERPORTSTR, &info, &serverResult);
	if (error == -1)
	{
		perror(gai_strerror(error));
		exit(10);
	}
	
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
	
	
	//change?
	execl("./TicTacToe","TicTacToe", NULL ,(char)* NULL);
	
	
	error = send(cSocket, "Connection complete.\n", BUFL, 0);
	
	printf("number of bytes sent: %d\n",error);
	
	
	exit (0);
}
