//#include "soc.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define SERVERPORT 31200
#define SERVERPORTSTR "31200"
#define SERVERIP "199.17.28.75"
#define SERVERNAME "ahscentos"
#define BUFL 100


int main(int argc, char *argv[])
{
	int sSocket;
	int cSocket;
	struct sockaddr_in sAddr;
	struct sockaddr_in cAddr;
	int cSocLen;
	int error;	
	
	
	//server information	
	memset (&cAddr, 0 , sizeof(struct sockaddr_in));
	cAddr.sin_family = AF_INET;
	cAddr.sin_port = htons(SERVERPORT);
	cAddr.sin_Addr.s_addr = inet_addr(SERVERIP);
	
	
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
	
	
	//change to running client?
	execl("./clientnew","clientnew", NULL , NULL);
	
	
	error = send(cSocket, "Connection complete.\n", BUFL, 0);
	
	printf("Ending connection to ServerG.\n");
	
	
	exit (0);
}
