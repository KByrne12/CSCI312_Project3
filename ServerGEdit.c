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
	int sSocket = atoi(argv[1]);
	int cSocket = atoi(argv[2]);
	int err;
	char Buf[BUFL];
	char name[BUFL];
	char serverName[BUFL];
	
	err = recv (cSocket, Buf, BUFL, 0);
	if (err == -1)
	{
		printf ("socServer: read failed");
		exit (1);
	}
	
	strcpy(name, Buf);
	strcpy(serverName, "ServerG paired with ");
	strcat(serverName, name);
	
	
	
	printf ("%s\n", serverName);
	
	
	
}
